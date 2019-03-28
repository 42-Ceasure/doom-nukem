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

void	set_wall(t_env *w, t_work work, int x)
{
	int		y;

	y = 0;
		while ((y < ((HEIGHT - work.height) / 2)) && (y < HEIGHT))
		{
			w->pix[y * WIDTH + x] = color(0x121E7FCB);
			y++;
		}
		while (y < (((HEIGHT + work.height) / 2)) && (y < HEIGHT))
		{
			w->pix[y * WIDTH + x] = color(0x12FFFFFF);
			y++;
		}
		while (y < HEIGHT)
		{
			w->pix[y * WIDTH + x] = color(0x124E3D28);
			y++;
		}
}

void	get_intersection(t_work *work)
{
	double b1;
	
	b1 = (*work->playerx - *work->x1) * work->m_wall + (*work->playery - *work->y1);
	work->x = b1 / (work->m_ray - work->m_wall);
	work->y = *work->y1 + (work->x - *work->x1) * work->m_wall;
}

draw_column_for(t_sector *s, t_work *work)
{
	get_intersection(work);
	if (s->)
}

int draw(t_env *w, t_map *m)
{
	t_work work;
	int i;
	int s;
	int ma;
	int mb;

	i = 0;
	s = 0;
	ma = 0;
	mb = 1;
//casting_out_raysthrough_the_level
	work.playerx = &m->player.coor.x;
	work.playery = &m->player.coor.y;
	work.playera = m->player.angle + 0.523599;
	work.x1 = &m->sector[s].dot[ma].x;
	work.y1 = &m->sector[s].dot[ma].y;
	work.x2 = &m->sector[s].dot[mb].x;
	work.y2 = &m->sector[s].dot[mb].y;
	work.m_wall = (*(work.y2) - *(work.y1)) / (*(work.x2) - *(work.x1));
	work.m_ray = tan(work.playera);
//calculating_intersections
	get_intersection(&work);
//getting_the_distance
	work.x_diff = (*work.playerx - work.x);
	work.y_diff = (*work.playery - work.y);
	if (fabs(work.x_diff) > fabs(work.y_diff))
		work.distance = work.x_diff / cos(work.playera);
	else
		work.distance = work.y_diff / sin(work.playera);
//correcting_the_distance
	work.distance = work.distance * cos(work.playera - m->player.angle);
//calculating_the_height__of_a_wall_slice
	if (work.distance == 0)
		work.distance = 1;
	work.height = (m->sector[s].ceiling) / work.distance;
//handling_sectors
	draw_column_for(m->sector[s], &work);
	work.playera = work.playera - work.angle_ray;
	return (0);
}