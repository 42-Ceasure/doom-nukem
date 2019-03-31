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
	t_intersect i1;
	t_intersect i2;
	t_coor ip1;
	t_coor ip2;

	work.v1.x = m.sector[0].dot[0].x;
	work.v1.y = m.sector[0].dot[0].y;
	work.v2.x = m.sector[0].dot[1].x;
	work.v2.y = m.sector[0].dot[1].y;
	work.player = m.player;
	work.player.coor.x = m.player.coor.x;
	work.player.coor.y = m.player.coor.y;

	work.tv1.x = work.v1.x - work.player.coor.x;
	work.tv1.y = work.v1.y - work.player.coor.y;
	work.tv2.x = work.v2.x - work.player.coor.x;
	work.tv2.y = work.v2.y - work.player.coor.y;
	work.tv1.z = work.tv1.x * cos(work.player.angle) + work.tv1.y * sin(work.player.angle);
	work.tv2.z = work.tv2.x * cos(work.player.angle) + work.tv2.y * sin(work.player.angle);
	work.tv1.x = work.tv1.x * sin(work.player.angle) - work.tv1.y * cos(work.player.angle);
	work.tv2.x = work.tv2.x * sin(work.player.angle) - work.tv2.y * cos(work.player.angle);

	set_txtr_pix(w, work.player.coor.x, work.player.coor.y, 0x12FFFFFF);
	vect_ab(work.v1, work.v2, w, 0x121E7FCB);
	work.player.move_speed.x = cos(work.player.angle) * 5 + work.player.coor.x;
	work.player.move_speed.y = sin(work.player.angle) * 5 + work.player.coor.y;
	vect_ab(work.player.coor, work.player.move_speed, w, 0x124E3D28);

	work.lol1.x = WIDTH / 2;
	work.lol1.y = HEIGHT / 2 - 1;
	work.lol2.x = WIDTH / 2;
	work.lol2.y = HEIGHT / 2 - 5;
	work.lel1.x = WIDTH / 2 - work.tv1.x;
	work.lel1.y = HEIGHT / 2 - work.tv1.z;
	work.lel2.x = WIDTH / 2 - work.tv2.x;
	work.lel2.y = HEIGHT / 2 - work.tv2.z;
	set_txtr_pix(w, WIDTH / 2, HEIGHT / 2, 0x12FFFFFF);
	vect_ab(work.lol1, work.lol2, w, 0x124E3D28);
	vect_ab(work.lel1, work.lel2, w, 0x121E7FCB);


	if (work.tv1.z > 0 || work.tv2.z > 0)
	{
		i1.x1 = work.tv1.x;
		i1.y1 = work.tv1.z;
		i1.x2 = work.tv2.x;
		i1.y2 = work.tv2.z;
		i1.x3 = -0.0000001;
		i1.y3 = 0.0000001;
		i1.x4 = -20;
		i1.y4 = 5;
		i2.x1 = work.tv1.x;
		i2.y1 = work.tv1.z;
		i2.x2 = work.tv2.x;
		i2.y2 = work.tv2.z;
		i2.x3 = 0.0000001;
		i2.y3 = 0.0000001;
		i2.x4 = 20;
		i2.y4 = 5;
		ip1 = intersect(i1);
		ip2 = intersect(i2);
		if (work.tv1.z <= 0)
		{
			if (ip1.y > 0)
			{
				work.tv1.x = ip1.x;
				work.tv1.z = ip1.y;
			}
			else
			{
				work.tv1.x = ip2.x;
				work.tv1.z = ip2.y;
			}
		}
		if (work.tv2.z <= 0)
		{
			if (ip1.y > 0)
			{
				work.tv2.x = ip1.x;
				work.tv2.z = ip1.y;
			}
			else
			{
				work.tv2.x = ip2.x;
				work.tv2.z = ip2.y;
			}
		}
		work.p1.x = -work.tv1.x * 16 / work.tv1.z;
		work.p1.y = -50 / work.tv1.z; 
		work.p1.z = 50 / work.tv1.z;
		work.p2.x = -work.tv2.x * 16 / work.tv2.z;
		work.p2.y =	-50 / work.tv2.z;
		work.p2.z = 50 / work.tv2.z;

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


//	printf("%f,%f,%f,%f,%f,%f,%f,%f\n", work.lol1.x, work.lol1.y, work.lel1.x, work.lel1.y, work.lol2.x, work.lol2.y, work.lel2.x, work.lel2.y);
}

































