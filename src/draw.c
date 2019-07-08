/*BIG42HEADER*/

#include "doom.h"

void	clean_render(t_env *w, Uint32 color)
{
	int x;

	x = 0;
	while (x < HEIGHT * WIDTH)
	{
		w->pix[x] = color;
		x++;
	}
}

void	ceiling_line(int x, t_work work, t_env *w, Uint32 color)
{
	int		y;
	int		y1;
	int		y2;

	y1 = work.starty;
	y2 = work.stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1 + 1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = color;
	else if (y2 > y1)
	{
		w->pix[y1 * WIDTH + x] = color;
		while (y < y2)
		{
			w->pix[y * WIDTH + x] = color;
			y++;
		}
		w->pix[y2 * WIDTH + x] = color;
	}
}

void	vertical_line(int x, t_work work, t_env *w, t_color color)
{
	int		y;
	int		y1;
	int		y2;

	y1 = work.starty;
	y2 = work.stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1 + 1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = color.middle;
	else if (y2 > y1)
	{
		w->pix[y1 * WIDTH + x] = color.top;
		while (y < y2)
		{
			w->pix[y * WIDTH + x] = color.middle;
			y++;
		}
		w->pix[y2 * WIDTH + x] = color.bottom;
	}
}

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
				if (w->textured == 1 && m->sector[work.nosector].texturing[5] == 0)
					ceiling_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[1]]);
				// else if (w->textured == 1 && w->m->sector[work.nosector].texturing[5] != 0)
				// 	skybox(x, box, w, d, w->texturing[w->m->sector[work.nosector].texturing[5]]);
				else if (w->textured != 1)
					ceiling_line(x, work, w, 0x12677179);



				work.starty = work.cyb + 1;
				work.stopy = work.ybot[x];
				if (w->textured == 1)
					ceiling_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[0]]);
				else
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
					if (w->textured == 1)
						vertical_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[3]]);
					else
						vertical_line(x, work, w, work.color);


					work.ytop[x] = vmid(vmax(work.cya, work.cnya), work.ytop[x], HEIGHT - 1);
					work.color.middle = (x == work.x1 || x == work.x2) ? 0 : work.r2;
					work.starty = work.cnyb + 1;
					work.stopy = work.cyb;
					if (work.stopy > work.starty && w->textured > 0)
						work.starty = work.ytop[x];
					// affiche trop -> toute la hauteur au lieu de juste bout de chaise
					// temporaire + ne faire que quand besoin non?
					if (w->textured == 1)
						vertical_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[4]]);
					else
						vertical_line(x, work, w, work.color);


					work.ybot[x] = vmid(vmin(work.cyb, work.cnyb), 0, work.ybot[x]);
				}
				else
				{
					work.r = 0x12010101 * (255 - work.z);

					work.color.middle = (x == work.x1 || x == work.x2) ? 0 : work.r;
					work.starty = work.cya;
					work.stopy = work.cyb;
					if (w->textured == 1)
						vertical_line_textured(x, w, work, w->texturing[m->sector[work.nosector].texturing[2]]);
					else
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












