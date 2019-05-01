/*BIG42HEADER*/

#include "doom.h"

void	set_txtr_pix(t_env *w, int x, int y, Uint32 color)
{
	if (y >= 0 && HEIGHT && x >= 0 && x < WIDTH)
		w->pix[y * WIDTH + x] = color;
}

void	set_txtr_dot(t_env *w, int x, int y, Uint32 color)
{
	int		i;

	i = 0;
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
	{
		w->pix[y * WIDTH + x] = color;
		while (i < 3)
		{
			if (y - i >= 0)
				w->pix[(y - i) * WIDTH + x] = color;
			if (x - i >= 0)
				w->pix[y * WIDTH + (x - i)] = color;
			if (y + i < HEIGHT)
				w->pix[(y + i) * WIDTH + x] = color;
			if (x + i < WIDTH)
				w->pix[y * WIDTH + (x + i)] = color;
			i++;
		}
	}
}

void	init_mini_map(t_map *m, t_draw *d, int point, int sector)
{
	d->v1.x = (m->sector[sector].dot[point].x - PL_X);
	d->v1.y = (m->sector[sector].dot[point].y - PL_Y);
	d->v2.x = (m->sector[sector].dot[point + 1].x - PL_X);
	d->v2.y = (m->sector[sector].dot[point + 1].y - PL_Y);
	d->t1.x = -(d->v1.x * PL_AS - d->v1.y * PL_AC) * 10 + (d->winwidth / 2);
	d->t1.y = -(d->v1.x * PL_AC + d->v1.y * PL_AS) * 10 + (d->winheight / 2);
	d->t2.x = -(d->v2.x * PL_AS - d->v2.y * PL_AC) * 10 + (d->winwidth / 2);
	d->t2.y = -(d->v2.x * PL_AC + d->v2.y * PL_AS) * 10 + (d->winheight / 2);
}

void	draw_mini_map(t_env *w, t_map *m)
{
	t_draw	d;
	int		sector;
	int		point;

	clean_render(w, 0x12CECECE);
	d.p1.x = (PL_X - PL_X) + (WIDTH / 2);
	d.p1.y = (PL_Y - PL_Y) + (HEIGHT / 2) - 1;
	d.p2.x = (PL_X - PL_X) + (WIDTH / 2);
	d.p2.y = (PL_Y - PL_Y) + (HEIGHT / 2) - 10;
	set_txtr_dot(w, d.p1.x, d.p1.y + 1, 0x12BF3030);
	vect_ab(d.p1, d.p2, w, 0x120F0F0F);
	sector = 0;
	while (sector < m->sector_count)
	{
		point = 0;
		while (point < m->sector[sector].wall_count)
		{
			init_mini_map(m, &d, point, sector);
			if (m->sector[sector].network[point] < 0)
				vect_ab(d.t1, d.t2, w, 0x12FF0000);
			point++;
		}
		sector++;
	}
}
