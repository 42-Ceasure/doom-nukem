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

void draw_mini_map(t_env *w, t_map m)
{
	t_work work;
	int sector;
	int point1;
	int point2;

	sector = 0;
	while (sector < m.sector_count)
	{
		point1 = 0;
		point2 = 1;
		while (point1 < m.sector[sector].wall_count)
		{
			if (point1 == m.sector[sector].wall_count - 1)
				point2 = 0;
			work.v1.x = m.sector[sector].dot[point1].x * 2;
			work.v1.y = m.sector[sector].dot[point1].y * 2;
			work.v2.x = m.sector[sector].dot[point2].x * 2;
			work.v2.y = m.sector[sector].dot[point2].y * 2;
			set_txtr_pix(w, (m.player.coor.x * 2), (m.player.coor.y * 2), 0x12FFFFFF);
			vect_ab(work.v1, work.v2, w, 0x121E7FCB);
			point1++;
			point2++;
		}
		sector++;
	}
}

void draw(t_env *w, t_map m)
{
	int point1;
	int point2;
	int sector;
	t_work work;

	sector = 0;	
	work.pcos = m.player.anglecos;
	work.psin = m.player.anglesin;
	while (sector < m.sector_count)
	{
		point1 = 0;
		point2 = 1;
		while (point1 < m.sector[sector].wall_count)
		{
			if (point1 == m.sector[sector].wall_count - 1)
				point2 = 0;
			// get wall points
			work.v1.x = m.sector[sector].dot[point1].x - m.player.coor.x;
			work.v1.y = m.sector[sector].dot[point1].y - m.player.coor.y;
			work.v2.x = m.sector[sector].dot[point2].x - m.player.coor.x;
			work.v2.y = m.sector[sector].dot[point2].y - m.player.coor.y;
			// rotate around player view
			work.t1.x = work.v1.x * work.psin - work.v1.y * work.pcos;
			work.t1.z = work.v1.x * work.pcos + work.v1.y * work.psin;
			work.t2.x = work.v2.x * work.psin - work.v2.y * work.pcos;
			work.t2.z = work.v2.x * work.pcos + work.v2.y * work.psin;
			//is the wall front of player ?
			if (work.t1.z >= 0 || work.t2.z >= 0)
			{
				work.i1.x1 = work.t1.x;
				work.i1.y1 = work.t1.z;
				work.i1.x2 = work.t2.x;
				work.i1.y2 = work.t2.z;
				work.i1.x3 = -0.0000001;
				work.i1.y3 = 0.0000001;
				work.i1.x4 = -45;
				work.i1.y4 = 5;
				work.i2.x1 = work.t1.x;
				work.i2.y1 = work.t1.z;
				work.i2.x2 = work.t2.x;
				work.i2.y2 = work.t2.z;
				work.i2.x3 = 0.0000001;
				work.i2.y3 = 0.0000001;
				work.i2.x4 = 45;
				work.i2.y4 = 5;
				work.ip1 = intersect(work.i1);
				work.ip2 = intersect(work.i2);
				if (work.t1.z <= 0)
				{
					if (work.ip1.y > 0)
					{
						work.t1.x = work.ip1.x;
						work.t1.z = work.ip1.y;
					}
					else
					{
						work.t1.x = work.ip2.x;
						work.t1.z = work.ip2.y;
					}
				}
				if (work.t2.z <= 0)
				{
					if (work.ip1.y > 0)
					{
						work.t2.x = work.ip1.x;
						work.t2.z = work.ip1.y;
					}
					else
					{
						work.t2.x = work.ip2.x;
						work.t2.z = work.ip2.y;
					}
				}
				work.p1.x = -work.t1.x * (HEIGHT / 2) / work.t1.z;
				work.p1.y = -(HEIGHT / 2) / work.t1.z; 
				work.p1.z = (HEIGHT / 2) / work.t1.z;
				work.p2.x = -work.t2.x * (HEIGHT / 2) / work.t2.z;
				work.p2.y =	-(HEIGHT / 2) / work.t2.z;
				work.p2.z = (HEIGHT / 2) / work.t2.z;

				work.lol1.x = WIDTH / 2 + work.p1.x;
				work.lol1.y = HEIGHT / 2 + work.p1.y;
				work.lol2.x = WIDTH / 2 + work.p2.x;
				work.lol2.y = HEIGHT / 2 + work.p2.y;
				work.lel1.x = WIDTH / 2 + work.p1.x;
				work.lel1.y = HEIGHT / 2 + work.p1.z;
				work.lel2.x = WIDTH / 2 + work.p2.x;
				work.lel2.y = HEIGHT / 2 + work.p2.z;
				vect_ab(work.lol1, work.lol2, w, 0x121E7FCB);
				vect_ab(work.lel1, work.lel2, w, 0x121E7FCB);
				vect_ab(work.lol1, work.lel1, w, 0x121E7FCB);
				vect_ab(work.lol2, work.lel2, w, 0x121E7FCB);
			}
			point1++;
			point2++;
		}
		sector++;
	}
//	printf("%f,%f,%f,%f,%f,%f,%f,%f\n", work.lol1.x, work.lol1.y, work.lel1.x, work.lel1.y, work.lol2.x, work.lol2.y, work.lel2.x, work.lel2.y);
}



//	printf("%f,%f,%f,%f,%f,%f,%f,%f\n", work.lol1.x, work.lol1.y, work.lel1.x, work.lel1.y, work.lol2.x, work.lol2.y, work.lel2.x, work.lel2.y);


































