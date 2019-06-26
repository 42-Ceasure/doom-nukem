/*BIG42HEADER*/

#include "doom.h"

void	set_network(t_draw *d, t_env *w, int x)
{
	int		box[2];

	d->nya = (x - d->x1) * (d->ny2a - d->ny1a) / (d->x2 - d->x1) + d->ny1a;
	d->nyb = (x - d->x1) * (d->ny2b - d->ny1b) / (d->x2 - d->x1) + d->ny1b;
	d->cnya = vmid(d->nya, d->ytop[x], d->ybot[x]);
	d->cnyb = vmid(d->nyb, d->ytop[x], d->ybot[x]);
	d->r1 = 0x12010101 * (255 - d->z);
	d->r2 = 0x12040007 * (31 - d->z / 8);
	if (d->z > 255)
		d->z = 255;
	d->color.top = 0;
	d->color.bottom = 0;
	d->color.middle = (x == d->x1 || x == d->x2) ? 0 : d->r1;
	box[0] = d->cya;
	box[1] = d->cnya - 1;
	vertical_line(x, box, w, d->color);
	d->ytop[x] = vmid(vmax(d->cya, d->cnya), d->ytop[x], HEIGHT - 1);
	d->color.middle = (x == d->x1 || x == d->x2) ? 0 : d->r2;
	box[0] = d->cnyb + 1;
	box[1] = d->cyb;
	vertical_line(x, box, w, d->color);
	d->ybot[x] = vmid(vmin(d->cyb, d->cnyb), 0, d->ybot[x]);
}

void	calculate(t_draw *d, int x)
{
	d->z = ((x - d->x1) * (d->t2.z - d->t1.z)
			/ (d->x2 - d->x1) + d->t1.z) * 2;
	if (d->z > 255)
		d->z = 255;
	d->ya = (x - d->x1) * (d->y2a - d->y1a) / (d->x2 - d->x1) + d->y1a;
	d->yb = (x - d->x1) * (d->y2b - d->y1b) / (d->x2 - d->x1) + d->y1b;
	d->cya = vmid(d->ya, d->ytop[x], d->ybot[x]);
	d->cyb = vmid(d->yb, d->ytop[x], d->ybot[x]);
}

void	draw_wall(t_draw *d, t_env *w, int x)
{
	int		box[2];

	while (++x <= d->endx)
	{
		calculate(d, x);
		box[0] = d->ytop[x];
		box[1] = d->cya - 1;
		ceiling_line(x, box, w, 0x12677179);
		box[0] = d->cyb + 1;
		box[1] = d->ybot[x];
		vertical_line(x, box, w, d->color2);
		if (d->network >= 0)
			set_network(d, w, x);
		else
		{
			d->r = 0x12010101 * (255 - d->z);
			d->color.middle = (x == d->x1 || x == d->x2) ? 0 : d->r;
			box[0] = d->cya;
			box[1] = d->cyb;
			vertical_line(x, box, w, d->color);
		}
		if ((w->sequential_draw == 1 && (x % 3 == 0))
			|| (w->sequential_frame == 1 && (x % 8 == 0)))
			img_update(w);
	}
}

void	wall_to_wall(t_draw *d, t_reader *read, t_map *m, t_env *w)
{
	d->point = 0;
	while (d->point < m->sector[read->now.sectorno].wall_count)
	{
		check_invisible(d, *read, m);
		if ((d->t1.z <= 0 && d->t2.z <= 0)
			|| ceiling_and_floor(d, m, *read, d->point++) == 0)
		{
			d->point = (d->t1.z <= 0 && d->t2.z <= 0) ? d->point + 1 : d->point;
			continue;
		}
		draw_wall(d, w, moving_head(d, *read, m));
		if (d->network >= 0 && d->endx >= d->startx && (read->head
				+ m->maxrenderedsector + 1 - read->tail) % m->maxrenderedsector)
		{
			read->head->sectorno = d->network;
			read->head->sx1 = d->startx;
			read->head->sx2 = d->endx;
			if (++read->head == read->queue + m->maxrenderedsector)
				read->head = read->queue;
		}
	}
}

void	draw(t_env *w, t_map *m)
{
	int			x;
	t_draw		d;
	t_reader	read;
	int			renderedsectors[m->sector_count];

	x = -1;
	while (x++ < WIDTH)
	{
		d.ytop[x] = 0;
		d.ybot[x] = HEIGHT - 1;
		if (x < m->sector_count)
			renderedsectors[x] = 0;
	}
	w->i = init_draw(w, &d, &read, m);
	while (read.head != read.tail)
	{
		read.now = *read.tail;
		if (++read.tail == read.queue + m->maxrenderedsector)
			read.tail = read.queue;
		if (renderedsectors[read.now.sectorno]++ & (m->maxrenderedsector + 1))
			continue;
		wall_to_wall(&d, &read, m, w);
		++renderedsectors[read.now.sectorno];
	}
	count_sprite(w, m);
}
