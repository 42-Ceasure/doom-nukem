/*BIG42HEADER*/

#include "doom.h"

// void	moving_head(t_draw *d, t_reader read, t_map *m)
// {
// 	d->y1a = d->winheight / 2 - (int)(yaw(d->yceil, d->t1.z, m) * d->yscale1);
// 	d->y2a = d->winheight / 2 - (int)(yaw(d->yceil, d->t2.z, m) * d->yscale2);
// 	d->y1b = d->winheight / 2 - (int)(yaw(d->yfloor, d->t1.z, m) * d->yscale1);
// 	d->y2b = d->winheight / 2 - (int)(yaw(d->yfloor, d->t2.z, m) * d->yscale2);
// 	d->ny1a = d->winheight / 2 - (int)(yaw(d->nyceil, d->t1.z, m) * d->yscale1);
// 	d->ny2a = d->winheight / 2 - (int)(yaw(d->nyceil, d->t2.z, m) * d->yscale2);
// 	d->ny1b = d->winheight / 2 - (int)(yaw(d->nyfloor, d->t1.z, m) * d->yscale1);
// 	d->ny2b = d->winheight / 2 - (int)(yaw(d->nyfloor, d->t2.z, m) * d->yscale2);
// 	d->startx = vmax(d->x1, read.now.sx1);
// 	d->endx = vmin(d->x2, read.now.sx2);
// }

// void	set_network(t_draw *d, t_env *w, int x)
// {
// 	int		box[2];

// 	d->nya = (x - d->x1) * (d->ny2a - d->ny1a) / (d->x2 - d->x1) + d->ny1a;
// 	d->nyb = (x - d->x1) * (d->ny2b - d->ny1b) / (d->x2 - d->x1) + d->ny1b;
// 	d->cnya = vmid(d->nya, d->ytop[x], d->ybot[x]);
// 	d->cnyb = vmid(d->nyb, d->ytop[x], d->ybot[x]);
// 	d->r1 = 0x010101 * (255 - d->z);
// 	d->r2 = 0x040007 * (31 - d->z / 8);
// 	if (d->z > 255)
// 		d->z = 255;
// 	d->color.top = 0;
// 	d->color.bottom = 0;
// 	d->color.middle = (x == d->x1 || x == d->x2) ? 0 : d->r1;
// 	box[0] = d->cya;
// 	box[1] = d->cnya - 1;
// 	if (w->textured == 1)
// 		vertical_line_textured(x, box, w, d, w->texturing[w->m->sector[d->nosector].texturing[3]]);
// 	else
// 		vertical_line(x, box, w, d->color);
// 	// CHECK ON Y TOP POUR PB DE SAUT





// 	d->color.middle = (x == d->x1 || x == d->x2) ? 0 : d->r2;
// 	d->ytop[x] = vmid(vmax(d->cya, d->cnya), d->ytop[x], HEIGHT - 1);
// 	box[0] = d->cnyb + 1;
// 	box[1] = d->cyb;
// 	if (box[1] > box[0] && w->textured > 0)
// 		box[0] = d->ytop[x];
// 	// affiche trop -> toute la hauteur au lieu de juste bout de chaise
// 	// temporaire + ne faire que quand besoin non?
// 	if (w->textured == 1)
// 		vertical_line_textured(x, box, w, d, w->texturing[w->m->sector[d->nosector].texturing[4]]);
// 	else
// 		vertical_line(x, box, w, d->color);
// 	d->ybot[x] = vmid(vmin(d->cyb, d->cnyb), 0, d->ybot[x]);
// }

// void	calculate(t_draw *d, int x)
// {
// 	d->z = ((x - d->x1) * (d->t2.z - d->t1.z)
// 			/ (d->x2 - d->x1) + d->t1.z) * 2;
// 	if (d->z > 255)
// 		d->z = 255;
// 	d->ya = (x - d->x1) * (d->y2a - d->y1a) / (d->x2 - d->x1) + d->y1a;
// 	d->yb = (x - d->x1) * (d->y2b - d->y1b) / (d->x2 - d->x1) + d->y1b;
// 	d->cya = vmid(d->ya, d->ytop[x], d->ybot[x]);
// 	d->cyb = vmid(d->yb, d->ytop[x], d->ybot[x]);
// }

// void	draw_wall(t_draw *d, t_env *w, int x)
// {
// 	int		box[2];
// 	while (x <= d->endx)
// 	{
// 		calculate(d, x);
// 		box[0] = d->ytop[x];
// 		box[1] = d->cya - 1;
// 		if (w->textured == 1 && w->m->sector[d->nosector].texturing[5] == 0)
// 			ceiling_line_textured(x, box, w, d, w->texturing[w->m->sector[d->nosector].texturing[1]]);
// 		// else if (w->textured == 1 && w->m->sector[d->nosector].texturing[5] != 0)
// 			// skybox(x, box, w, d, w->texturing[w->m->sector[d->nosector].texturing[5]]);
// 		else if (w->textured != 1)
// 			ceiling_line(x, box, w, 0x12677179);
// 		box[0] = d->cyb + 1;
// 		box[1] = d->ybot[x];
// 		if (w->textured == 1)
// 			ceiling_line_textured(x, box, w, d, w->texturing[w->m->sector[d->nosector].texturing[0]]);
// 		else
// 			vertical_line(x, box, w, d->color2);
// 		if (d->network >= 0)
// 			set_network(d, w, x);
// 		else
// 		{
// 			d->r = 0x010101 * (255 - +d->z);
// 			d->color.middle = (x == d->x1 || x == d->x2) ? 0 : d->r;
// 			box[0] = d->cya;
// 			box[1] = d->cyb;
// 			if (w->textured == 1)
// 				vertical_line_textured(x, box, w, d, w->texturing[w->m->sector[d->nosector].texturing[2]]);
// 			else
// 				vertical_line(x, box, w, d->color);				
// 		}
// 		if ((w->sequential_draw == 1 && (x % 3 == 0))
// 			|| (w->sequential_frame == 1 && (x % 8 == 0)))
// 			img_update(w);
// 		x++;
// 	}
// }

// int		ceiling_and_floor(t_draw *d, t_map *m, t_reader read, int point)
// {
// 	d->xscale1 = m->player.field_of_vision_h / d->t1.z;
// 	d->yscale1 = (m->player.field_of_vision_v) / d->t1.z;
// 	d->xscale2 = m->player.field_of_vision_h / d->t2.z;
// 	d->yscale2 = (m->player.field_of_vision_v) / d->t2.z;
// 	d->x1 = d->winwidth / 2 - (int)(d->t1.x * d->xscale1);
// 	d->x2 = d->winwidth / 2 - (int)(d->t2.x * d->xscale2);
// 	if (d->x1 >= d->x2 || d->x2 < read.now.sx1 || d->x1 > read.now.sx2)
// 		return (-1);
// 	d->yceil = m->sector[read.now.sectorno].ceiling - m->player.coor.z;
// 	d->yfloor = m->sector[read.now.sectorno].floor - m->player.coor.z;
// 	d->network = m->sector[read.now.sectorno].network[point];
// 	d->nyceil = 0;
// 	d->nyfloor = 0;
// 	if (d->network >= 0)
// 	{
// 		d->nyceil = m->sector[d->network].ceiling - m->player.coor.z;
// 		d->nyfloor = m->sector[d->network].floor - m->player.coor.z;
// 	}
// 	return (0);
// }

// int		check_invisible(t_draw *d, t_reader read, t_map *m)
// {
// 	d->v1.x = m->sector[read.now.sectorno].dot[d->point + 0].x - PL_X;
// 	d->v1.y = m->sector[read.now.sectorno].dot[d->point + 0].y - PL_Y;
// 	d->v2.x = m->sector[read.now.sectorno].dot[d->point + 1].x - PL_X;
// 	d->v2.y = m->sector[read.now.sectorno].dot[d->point + 1].y - PL_Y;
// 	d->pcos = PL_AC;
// 	d->psin = PL_AS;
// 	d->t1.x = d->v1.x * d->psin - d->v1.y * d->pcos;
// 	d->t1.z = d->v1.x * d->pcos + d->v1.y * d->psin;
// 	d->t2.x = d->v2.x * d->psin - d->v2.y * d->pcos;
// 	d->t2.z = d->v2.x * d->pcos + d->v2.y * d->psin;
// 	d->tt1.x = d->t1.x;
// 	d->tt1.z = d->t1.z;
// 	d->tt2.x = d->t2.x;
// 	d->tt2.z = d->t2.z;
// 	if (d->t1.z <= 0 && d->t2.z <= 0)
// 		return (-1);
// 	if (d->t1.z <= 0 || d->t2.z <= 0)
// 	{
// 		init_verification(d);
// 		if (d->t1.z < d->nearz)
// 		{
// 			if (d->ip1.y > 0)
// 			{
// 				d->t1.x = d->ip1.x;
// 				d->t1.z = d->ip1.y;
// 			}
// 			else
// 			{
// 				d->t1.x = d->ip2.x;
// 				d->t1.z = d->ip2.y;
// 			}
// 		}
// 		if (d->t2.z < d->nearz)
// 		{
// 			if (d->ip1.y > 0)
// 			{
// 				d->t2.x = d->ip1.x;
// 				d->t2.z = d->ip1.y;
// 			}
// 			else
// 			{
// 				d->t2.x = d->ip2.x;
// 				d->t2.z = d->ip2.y;
// 			}
// 		}
// 	}
// 	return (0);
// }

// void	wall_to_wall(t_draw *d, t_reader *read, t_map *m, t_env *w)
// {
// 	d->nosector = read->now.sectorno;
// 	d->point = 0;
// 	while (d->point < m->sector[read->now.sectorno].wall_count)
// 	{
// 		d->wall_width = pythagore((m->sector[read->now.sectorno].dot[d->point + 1].x \
// 			- m->sector[read->now.sectorno].dot[d->point].x), (m->sector[read->now.sectorno].dot[d->point + 1].y \
// 				- m->sector[read->now.sectorno].dot[d->point].y));
// 		if (check_invisible(d, *read, m) == -1)
// 		{
// 			d->point++;
// 			continue;
// 		}
// 		if (ceiling_and_floor(d, m, *read, d->point) == -1)
// 		{
// 			d->point++;
// 			continue;	
// 		}
// 		moving_head(d, *read, m);
// 		draw_wall(d, w, d->startx);
// 		if (d->network >= 0 && d->endx >= d->startx && (read->head
// 				+ m->maxrenderedsector + 1 - read->tail) % m->maxrenderedsector)
// 		{
// 			read->head->sectorno = d->network;
// 			read->head->sx1 = d->startx;
// 			read->head->sx2 = d->endx;
// 			if (++read->head == read->queue + m->maxrenderedsector)
// 				read->head = read->queue;
// 		}
// 		d->point++;
// 	}
// }

void draw(t_env *w, t_map *m)
{
	int point;
	int x;
	t_work work;
	t_reader read;
	int renderedsectors[m->sector_count];

	clear_sprite(m);
	read.head = read.queue;
	read.tail = read.queue;
	x = 0;
	while (x < WIDTH)
	{
		work.ytop[x] = 0;
		work.ybot[x] = HEIGHT - 1;
		if (x < m->sector_count)
			renderedsectors[x] = 0;
		x++;
	}
	read.head->sectorno = m->player.sector;
	read.head->sx1 = 0;
	read.head->sx2 = WIDTH - 1;
	if (++read.head == read.queue + m->maxrenderedsector)
		read.head = read.queue;
	work.nearz = 0.0000000001;
	work.farz = 5;
	work.nearside = 0.0000000001;
	work.farside = 20.f;
	work.color.top = 0x12111111;
	work.color.middle = 0x12222222;
	work.color.bottom = 0x12111111;
	work.color2.top = 0x120000FF;
	work.color2.middle = 0x120000AA;
	work.color2.bottom = 0x120000FF;
	x = 0;
	w->i = 0;
	while (read.head != read.tail)
	{
		read.now = *read.tail;
		if (++read.tail == read.queue + m->maxrenderedsector)
			read.tail = read.queue;
		if (renderedsectors[read.now.sectorno] & (m->maxrenderedsector + 1))
			continue;
		++renderedsectors[read.now.sectorno];
		work.nosector = read.now.sectorno;
		point = 0;
		while (point < m->sector[read.now.sectorno].wall_count)
		{
			work.wall_width = pythagore((m->sector[read.now.sectorno].dot[point + 1].x \
			- m->sector[read.now.sectorno].dot[point].x), (m->sector[read.now.sectorno].dot[point + 1].y \
				- m->sector[read.now.sectorno].dot[point].y));

			work.v1.x = m->sector[read.now.sectorno].dot[point + 0].x - PL_X;
			work.v1.y = m->sector[read.now.sectorno].dot[point + 0].y - PL_Y;
			work.v2.x = m->sector[read.now.sectorno].dot[point + 1].x - PL_X;
			work.v2.y = m->sector[read.now.sectorno].dot[point + 1].y - PL_Y;

			work.pcos = PL_AC;
			work.psin = PL_AS;
			work.t1.x = work.v1.x * work.psin - work.v1.y * work.pcos;
			work.t1.z = work.v1.x * work.pcos + work.v1.y * work.psin;
			work.t2.x = work.v2.x * work.psin - work.v2.y * work.pcos;
			work.t2.z = work.v2.x * work.pcos + work.v2.y * work.psin;

			work.tt1.x = work.t1.x;
			work.tt1.z = work.t1.z;
			work.tt2.x = work.t2.x;
			work.tt2.z = work.t2.z;

			if (work.t1.z < 0 && work.t2.z < 0) 
			{
				point++;
				continue;
			}
			if (work.t1.z < 0 || work.t2.z < 0)
			{
				work.i1.x1 = work.t1.x;
				work.i1.y1 = work.t1.z;
				work.i1.x2 = work.t2.x;
				work.i1.y2 = work.t2.z;
				work.i1.x3 = -work.nearside;
				work.i1.y3 = work.nearz;
				work.i1.x4 = -work.farside;
				work.i1.y4 = work.farz;
				work.i2.x1 = work.t1.x;
				work.i2.y1 = work.t1.z;
				work.i2.x2 = work.t2.x;
				work.i2.y2 = work.t2.z;
				work.i2.x3 = work.nearside;
				work.i2.y3 = work.nearz;
				work.i2.x4 = work.farside;
				work.i2.y4 = work.farz;
				work.ip1 = intersect(work.i1);
				work.ip2 = intersect(work.i2);
				if (work.t1.z < work.nearz)
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
				if (work.t2.z < work.nearz)
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
			}
			work.xscale1 = m->player.field_of_vision_h / work.t1.z;
			work.yscale1 = (m->player.field_of_vision_v) / work.t1.z;
			work.xscale2 = m->player.field_of_vision_h / work.t2.z;
			work.yscale2 = (m->player.field_of_vision_v) / work.t2.z;
			work.x1 = WIDTH / 2 - (int)(work.t1.x * work.xscale1);
			work.x2 = WIDTH / 2 - (int)(work.t2.x * work.xscale2);

			if (work.x1 >= work.x2 || work.x2 < read.now.sx1 || work.x1 > read.now.sx2)
			{
				point++;
				continue;
			}
			work.yceil = m->sector[read.now.sectorno].ceiling - m->player.coor.z;
			work.yfloor = m->sector[read.now.sectorno].floor - m->player.coor.z;
			work.network = m->sector[read.now.sectorno].network[point];
			work.nyceil = 0;
			work.nyfloor = 0;
			if (work.network >= 0)
			{
				work.nyceil = m->sector[work.network].ceiling - m->player.coor.z;
				work.nyfloor = m->sector[work.network].floor - m->player.coor.z;
			}
			work.y1a = HEIGHT / 2 - (int)(yaw(work.yceil, work.t1.z, m) * work.yscale1);
			work.y2a = HEIGHT / 2 - (int)(yaw(work.yceil, work.t2.z, m) * work.yscale2);
			work.y1b = HEIGHT / 2 - (int)(yaw(work.yfloor, work.t1.z, m) * work.yscale1);
			work.y2b = HEIGHT / 2 - (int)(yaw(work.yfloor, work.t2.z, m) * work.yscale2);
			work.ny1a = HEIGHT / 2 - (int)(yaw(work.nyceil, work.t1.z, m) * work.yscale1);
			work.ny2a = HEIGHT / 2 - (int)(yaw(work.nyceil, work.t2.z, m) * work.yscale2);
			work.ny1b = HEIGHT / 2 - (int)(yaw(work.nyfloor, work.t1.z, m) * work.yscale1);
			work.ny2b = HEIGHT / 2 - (int)(yaw(work.nyfloor, work.t2.z, m) * work.yscale2);

			work.startx = vmax(work.x1, read.now.sx1);
			work.endx = vmin(work.x2, read.now.sx2);
			x = work.startx;
			while (x <= work.endx)
			{
				work.z = ((x - work.x1) * (work.t2.z - work.t1.z) / (work.x2 - work.x1) + work.t1.z) * 2;
				if (work.z > 255)
					work.z = 255;
				work.ya = (x - work.x1) * (work.y2a - work.y1a) / (work.x2 - work.x1) + work.y1a;
				work.yb = (x - work.x1) * (work.y2b - work.y1b) / (work.x2 - work.x1) + work.y1b;
				work.cya = vmid(work.ya, work.ytop[x], work.ybot[x]);
				work.cyb = vmid(work.yb, work.ytop[x], work.ybot[x]);



				work.starty = work.ytop[x];
				work.stopy = work.cya - 1;
				// if (w->textured == 1 && m->sector[work.nosector].texturing[5] == 0)
				// 	ceiling_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[1]]);
				// // else if (w->textured == 1 && w->m->sector[work.nosector].texturing[5] != 0)
				// 	// skybox(x, box, w, d, w->texturing[w->m->sector[work.nosector].texturing[5]]);
				// else if (w->textured != 1)
					ceiling_line(x, work, w, 0x12677179);



				work.starty = work.cyb + 1;
				work.stopy = work.ybot[x];
				// if (w->textured == 1)
				// 	ceiling_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[0]]);
				// else
					vertical_line(x, work, w, work.color2);



				if (work.network >= 0)
				{
					work.nya = (x - work.x1) * (work.ny2a - work.ny1a) / (work.x2 - work.x1) + work.ny1a;
					work.nyb = (x - work.x1) * (work.ny2b - work.ny1b) / (work.x2 - work.x1) + work.ny1b;
					work.cnya = vmid(work.nya, work.ytop[x], work.ybot[x]);
					work.cnyb = vmid(work.nyb, work.ytop[x], work.ybot[x]);
					work.r1 = 0x12010101 * (255 - work.z);
					work.r2 = 0x12040007 * (31 - work.z / 8);
					if (work.z > 255)
						work.z = 255;
					work.color.top = 0;
					work.color.bottom = 0;


					work.color.middle = (x == work.x1 || x == work.x2) ? 0 : work.r1;
					work.starty = work.cya;
					work.stopy = work.cnya - 1;
					// if (w->textured == 1)
					// 	vertical_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[3]]);
					// else
						vertical_line(x, work, w, work.color);


					work.ytop[x] = vmid(vmax(work.cya, work.cnya), work.ytop[x], HEIGHT - 1);
					work.color.middle = (x == work.x1 || x == work.x2) ? 0 : work.r2;
					work.starty = work.cnyb + 1;
					work.stopy = work.cyb;
					if (work.stopy > work.starty && w->textured > 0)
						work.starty = work.ytop[x];
					// affiche trop -> toute la hauteur au lieu de juste bout de chaise
					// temporaire + ne faire que quand besoin non?
					// if (w->textured == 1)
					// 	vertical_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[4]]);
					// else
						vertical_line(x, work, w, work.color);


					work.ybot[x] = vmid(vmin(work.cyb, work.cnyb), 0, work.ybot[x]);
				}
				else
				{
					work.r = 0x12010101 * (255 - work.z);

					work.color.middle = (x == work.x1 || x == work.x2) ? 0 : work.r;
					work.starty = work.cya;
					work.stopy = work.cyb;
					// if (w->textured == 1)
					// 	vertical_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[2]]);
					// else
						vertical_line(x, work, w, work.color);
				}
				x++;
				if (w->sequential_draw == 1)
					img_update(w);
			}
			if (work.network >= 0 && work.endx >= work.startx && (read.head + m->maxrenderedsector + 1 - read.tail) % m->maxrenderedsector)
			{
				read.head->sectorno = work.network;
				read.head->sx1 = work.startx;
				read.head->sx2 = work.endx;
				if (++read.head == read.queue + m->maxrenderedsector)
					read.head = read.queue;
			}
			point++;
		}
		++renderedsectors[read.now.sectorno];
	}
	count_sprite(w, m);
}












