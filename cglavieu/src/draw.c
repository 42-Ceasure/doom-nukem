//

#include "doom-nukem.h"

void	set_wall(t_env *w, t_work work, int x)
{
	int		y;

	y = HEIGHT / 2;
	while (y < (HEIGHT / 2) + (work.height / 2))
	{
		w->pix[y * WIDTH + x] = 0xFFFFFF;
		y++;
	}
	y = HEIGHT / 2;
	while (y > (HEIGHT / 2) - (work.height / 2))
	{
		w->pix[y * WIDTH + x] = 0xFFFFFF;
		y--;
	}
}

int draw(t_env *w, t_map *m)
{
	t_work work;
	int i;

	i = 0;
	work.fov = (WIDTH/2) / ((m->player.field_of_vision / 2) * M_PI / 180); 
	work.angle_ray = (double)(m->player.field_of_vision * M_PI / 180) / WIDTH;

	work.x1 = &m->sector[0].dot[0].x;
	work.y1 = &m->sector[0].dot[0].y;
	work.x2 = &m->sector[0].dot[1].x;
	work.y2 = &m->sector[0].dot[1].y;

	work.playerx = &m->player.coor.x;
	work.playery = &m->player.coor.y;
	work.playera = (m->player.angle + 30) * M_PI / 180;

	while (i < WIDTH)
	{
		printf("%f\n", *(work.playerx));
		work.m_wall = (*(work.y2) - *(work.y1)) / (*(work.x2) - *(work.x1));
		work.m_ray = tan(work.playera);

		work.b1 = (*(work.playerx) - *(work.x1)) * work.m_wall + (*(work.playery) - *(work.y1));
		work.x = work.b1 / (work.m_ray - work.m_wall);
		work.y = *(work.y1) + (work.x - *(work.x1)) * work.m_wall;

		work.x_diff = (*work.playerx - work.x);
		work.y_diff = (*work.playery - work.y);

		if (fabs(work.x_diff) > fabs(work.y_diff))
			work.distance = work.x_diff / cos(work.playera);
		else
			work.distance = work.y_diff / sin(work.playera);
		if (work.distance == 0)
			work.distance = 1;
		work.height = m->sector->ceiling / work.distance;
		work.playera = work.playera - work.angle_ray;
		set_wall(w, work, i);
		i++;
	}
	return (0);
}