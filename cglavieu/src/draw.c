//

#include "doom-nukem.h"

Uint32		color(Uint32 color1)
{
	Uint8	a;
	Uint8	ro;
	Uint8	g;
	Uint8	b;

	a = (color1 & 0xFF000000) >> 24;
	ro = (color1 & 0x00FF0000) >> 16;
	g = (color1 & 0x0000FF00) >> 8;
	b = (color1 & 0x000000FF);
	return ((((((a << 8) + ro) << 8) + g) << 8) + b);
}

void	clean_render(t_env *w, Uint32 color)
{
	int x;

	x = 0;
	while (x < HEIGHT * WIDTH - 1)
	{
		w->pix[x] = color;
		x++;
	}

}

void	set_txtr_pix(t_env *w, int x, int y, Uint32 color)
{
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
		w->pix[y * WIDTH + x] = color;
}

void	set_wall(t_env *w, t_work work, int x)
{
	int		y;

	y = 0;
		while ((y < ((HEIGHT - work.height) / 2)) && (y < HEIGHT))
		{
			w->pix[y * WIDTH + x] = 0x121E7FCB;
			y++;
		}
		while (y < (((HEIGHT + work.height) / 2)) && (y < HEIGHT))
		{
			w->pix[y * WIDTH + x] = 0x12FFFFFF;
			y++;
		}
		while (y < HEIGHT)
		{
			w->pix[y * WIDTH + x] = 0x124E3D28;
			y++;
		}
}

void vline(int x, int y1, int y2, t_env *w, t_color color)
{
	Uint32 *pix = (Uint32 *)w->pix;
	int y;

	y1 = vMid(y1, 0, HEIGHT-1);
	y2 = vMid(y2, 0, HEIGHT-1);
	y = y1 + 1;
	if(y2 == y1)
		pix[y1*WIDTH+x] = color.middle;
	else if(y2 > y1)
	{
		pix[y1*WIDTH+x] = color.top;
		while (y<y2)
		{
			pix[y*WIDTH+x] = color.middle;
			y++;
		}
		pix[y2*WIDTH+x] = color.bottom;
	}
}

void draw(t_env *w, t_map m)
{

	t_work work;
	int x;
	int z;
	int ytop[WIDTH]={0};
    int ybottom[WIDTH];

	work.nearz = 1e-4f;
	work.farz = 5;
	work.nearside = 1e-5f;
	work.farside = 20.f;
	/* Acquire the x,y coordinates of the two endpoints (vertices) of this edge of the sector */
	work.v1.x = m.sector[m.player.sector].dot[0].x - m.player.coor.x;
	work.v1.y = m.sector[m.player.sector].dot[0].y - m.player.coor.y;
	work.v2.x = m.sector[m.player.sector].dot[1].x - m.player.coor.x;
	work.v2.y = m.sector[m.player.sector].dot[1].y - m.player.coor.y;
	/* Rotate them around the player's view */
	work.pcos = m.player.anglecos;
	work.psin = m.player.anglesin;
	work.t1.x = work.v1.x * work.psin - work.v1.y * work.pcos;
	work.t1.z = work.v1.x * work.pcos + work.v1.y * work.psin;
	work.t2.x = work.v2.x * work.psin - work.v2.y * work.pcos;
	work.t2.z = work.v2.x * work.pcos + work.v2.y * work.psin;
	/* Is the wall at least partially in front of the player? */
	if (work.t1.z <= 0 && work.t2.z <= 0)
	{
		/* If it's partially behind the player, clip it against player's view frustrum */
		if (work.t1.z <= 0 || work.t2.z <= 0)
		{
			work.inter1.x1 = work.t1.x;
			work.inter1.y1 = work.t1.z;
			work.inter1.x2 = work.t2.x;
			work.inter1.y2 = work.t2.z;
			work.inter1.x3 = -work.nearside;
			work.inter1.y3 = work.nearz;
			work.inter1.x4 = -work.farside;
			work.inter1.y4 = work.farz;
			work.inter2.x1 = work.t1.x;
			work.inter2.y1 = work.t1.z;
			work.inter2.x2 = work.t2.x;
			work.inter2.y2 = work.t2.z;
			work.inter2.x3 = work.nearside;
			work.inter2.y3 = work.nearz;
			work.inter2.x4 = work.farside;
			work.inter2.y4 = work.farz;
			// Find an intersection between the wall and the approximate edges of player's view
			work.i1 = intersect(work.inter1);
			work.i2 = intersect(work.inter2);
			if (work.t1.z < work.nearz)
			{
				if (work.i1.y > 0)
				{
					work.t1.x = work.i1.x;
					work.t1.z = work.i1.y;
				}

				else
				{
					work.t1.x = work.i2.x;
					work.t1.z = work.i2.y;
				}
			}
			if (work.t2.z < work.nearz)
			{
				if (work.i1.y > 0)
				{
					work.t2.x = work.i1.x;
					work.t2.z = work.i1.y;
				}
				else
				{
					work.t2.x = work.i2.x;
					work.t2.z = work.i2.y;
				}
			}
		}
		/* Do perspective transformation */
		work.xscale1 = HFOV / work.t1.z;
		work.yscale1 = VFOV / work.t1.z;
		work.xscale2 = HFOV / work.t2.z;
		work.yscale2 = VFOV / work.t2.z;
		work.x1 = (WIDTH / 2) - (int)(work.t1.x * work.xscale1);
		work.x2 = (WIDTH / 2) - (int)(work.t2.x * work.xscale2);
		// if (work.x1 >= work.x2 || work.x2 < || x1 > )

		work.yceil = m.sector[m.player.sector].ceiling - m.player.coor.z;
		work.yfloor = m.sector[m.player.sector].floor - m.player.coor.z;
		if (ft_strcmp(m.sector[m.player.sector].network[0], "x") != 0)
			work.neighbor = ft_atoi(m.sector[m.player.sector].network[0]);
		else
			work.neighbor = 0;
		work.nyceil = 0;
		work.nyfloor = 0;
		if (work.neighbor >= 0)
		{
			work.nyceil = m.sector[work.neighbor].ceiling - m.player.coor.z;
			work.nyfloor = m.sector[work.neighbor].floor - m.player.coor.z;
		}

		work.y1a = HEIGHT/2 - (int)(yaw(work.yceil, work.t1.z, m) * work.yscale1);
		work.y1b = HEIGHT/2 - (int)(yaw(work.yfloor, work.t1.z, m) * work.yscale1);
		work.y2a = HEIGHT/2 - (int)(yaw(work.yceil, work.t2.z, m) * work.yscale2);
		work.y2b = HEIGHT/2 - (int)(yaw(work.yfloor, work.t2.z, m) * work.yscale2);
		work.ny1a = HEIGHT/2 - (int)(yaw(work.nyceil, work.t1.z, m) * work.yscale1);
		work.ny1b = HEIGHT/2 - (int)(yaw(work.nyfloor, work.t1.z, m) * work.yscale1);
		work.ny2a = HEIGHT/2 - (int)(yaw(work.nyceil, work.t2.z, m) * work.yscale2);
		work.ny2b = HEIGHT/2 - (int)(yaw(work.nyfloor, work.t2.z, m) * work.yscale2);
		work.startx = vMax(work.x1, 0);
		work.endx = vMin(work.x2, 607);
		x = work.startx;
		while (x <= work.endx)
		{
			z = ((x - work.x1) * (work.t2.z - work.t1.z) / (work.x2 - work.x1) + work.t1.z) * 8;
			work.ya = (x - work.x1) * (work.y2a - work.y1a) / (work.x2 - work.x1) + work.y1a;
			work.cya = vMid(work.ya, ytop[x],ybottom[x]);
			work.yb = (x - work.x1) * (work.y2b - work.y1b) / (work.x2 - work.x1) + work.y1b;
			work.cyb = vMid(work.yb, ytop[x], ybottom[x]);

			work.color.top = 0x111111;
			work.color.middle = 0x222222;
			work.color.bottom = 0x111111;
			vline(x, ytop[x], work.cya-1, w, work.color);
			work.color.top = 0x0000FF;
			work.color.middle = 0x0000AA;
			work.color.bottom = 0x0000FF;
			vline(x, work.cyb+1, ybottom[x], w, work.color);

			if (work.neighbor >= 0)
			{
				work.nya = (x - work.x1) * (work.ny2a - work.ny1a) / (work.x2 - work.x1) + work.ny1a;
				work.cnya = vMid(work.nya, ytop[x], ybottom[x]);
				work.nyb = (x - work.x1) * (work.ny2b - work.ny1b) / (work.x2 - work.x1) + work.ny1b;
				work.cnyb = vMid(work.nyb, ytop[x], ybottom[x]);
				work.r1 = 0x010101 * (255 - z);
				work.r2 = 0x040007 * (31 - z / 8);
				work.color.top = 0x000000;
				work.color.middle = x==work.x1||x==work.x2 ? 0 : work.r1;
				work.color.bottom = 0x000000;
				vline(x, work.cya, work.cnya-1, w, work.color);
				ytop[x] = vMid(vMax(work.cya, work.cnya), ytop[x], HEIGHT-1);
				work.color.top = 0x0000FF;
				work.color.middle = 0x0000AA;
				work.color.bottom = 0x0000FF;
				vline(x, work.cyb+1, ybottom[x], w, work.color);
			}
			else
			{
				work.r = 0x010101 * (255 - z);
				work.color.top = 0x000000;
				work.color.middle = x==work.x1||x==work.x2 ? 0 : work.r;
				work.color.bottom = 0x000000;
				vline(x, work.cya, work.cyb, w, work.color);
			}
			x++;
		}
	}


//	printf("%f,%f,%f,%f,%f,%f,%f,%f\n", work.lol1.x, work.lol1.y, work.lel1.x, work.lel1.y, work.lol2.x, work.lol2.y, work.lel2.x, work.lel2.y);
}

































