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

Uint32		c2colorw(t_color *r, Uint32 color1, Uint32 color2)
{
	Uint8	a;
	Uint8	ro;
	Uint8	g;
	Uint8	b;
	double	cren;

	cren = (r->y - (double)(int)r->y);
	cren *= 100;
	r->c_a1 = (color1 & 0xFF000000) >> 24;
	r->c_r1 = (color1 & 0x00FF0000) >> 16;
	r->c_g1 = (color1 & 0x0000FF00) >> 8;
	r->c_b1 = (color1 & 0x000000FF);
	r->c_a2 = (color2 & 0xFF000000) >> 24;
	r->c_r2 = (color2 & 0x00FF0000) >> 16;
	r->c_g2 = (color2 & 0x0000FF00) >> 8;
	r->c_b2 = (color2 & 0x000000FF);
	a = 0;
	ro = (r->c_r2 * cren / 100) + ((r->c_r1 * (100 - cren)) / 100);
	g = (r->c_g2 * cren / 100) + ((r->c_g1 * (100 - cren)) / 100);
	b = (r->c_b2 * cren / 100) + ((r->c_b1 * (100 - cren)) / 100);
	return ((((((a << 8) + ro) << 8) + g) << 8) + b);
}

Uint32		color2color(t_color *r, Uint32 color1, Uint32 color2)
{
	Uint8	a;
	Uint8	ro;
	Uint8	g;
	Uint8	b;

	r->c_a1 = (color1 & 0xFF000000) >> 24;
	r->c_r1 = (color1 & 0x00FF0000) >> 16;
	r->c_g1 = (color1 & 0x0000FF00) >> 8;
	r->c_b1 = (color1 & 0x000000FF);
	r->c_a2 = (color2 & 0xFF000000) >> 24;
	r->c_r2 = (color2 & 0x00FF0000) >> 16;
	r->c_g2 = (color2 & 0x0000FF00) >> 8;
	r->c_b2 = (color2 & 0x000000FF);
	a = 0;
	ro = r->c_r1 + (r->y - r->start) *
		(r->c_r2 - r->c_r1) / (r->stop - r->start);
	g = r->c_g1 + (r->y - r->start) *
		(r->c_g2 - r->c_g1) / (r->stop - r->start);
	b = r->c_b1 + (r->y - r->start) *
		(r->c_b2 - r->c_b1) / (r->stop - r->start);
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

void	set_txtr_dot(t_env *w, int x, int y, Uint32 color)
{
	int i;

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

void	set_wall_trippy(t_env *w, int x, int y1, int y2, Uint32 color)
{
	int		y;
	t_color colors;

	(void)color;
	y = 0;
	if (y1 < HEIGHT)
		colors.start = y1;
	else
		colors.start = HEIGHT - 4;
	if (y2 < HEIGHT)
		colors.stop = y2;
	else
		colors.stop = HEIGHT - 2;
	if (colors.stop <= colors.start)
		colors.start = colors.stop - 1;
	while (y < y1)
	{
		colors.y = y;
		w->pix[y * WIDTH + x] = 0x121E7FCB;
		y++;
	}
	while (y < y2)
	{
		colors.y = y;
		w->pix[y * WIDTH + x] = color2color(&colors, 0x1288421D, 0x12F9429E);
		y++;
	}
	while (y < HEIGHT)
	{
		colors.y = y;
		w->pix[y * WIDTH + x] = 0x124E3D28;
		y++;
	}
}

void	set_wall(t_env *w, int x, int y1, int y2, Uint32 color)
{
	int		y;
	t_color colors;

	y = 0;
	if (y1 < HEIGHT)
		colors.start = y1;
	else
		colors.start = HEIGHT - 4;
	if (y2 < HEIGHT)
		colors.stop = y2;
	else
		colors.stop = HEIGHT - 2;
	if (colors.stop <= colors.start)
		colors.start = colors.stop - 1;
	while (y < y1)
	{
		colors.y = y;
		w->pix[y * WIDTH + x] = 0x121E7FCB;
		y++;
	}
	while (y < y2)
	{
		colors.y = y;
		w->pix[y * WIDTH + x] = color;
		y++;
	}
	while (y < HEIGHT)
	{
		colors.y = y;
		w->pix[y * WIDTH + x] = 0x124E3D28;
		y++;
	}
}

void vertical_line_moche(int x, int y1, int y2, t_env *w, Uint32 color)
{
	int y;

	y1 = vmid(y1, 0, HEIGHT-1);
	y2 = vmid(y2, 0, HEIGHT-1);
	y = y1 + 1;
	if(y2 == y1)
		w->pix[y1 * WIDTH + x] = color;
	else if(y2 > y1)
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

void vertical_line(int x, int y1, int y2, t_env *w, t_color color)
{
	int y;

	y1 = vmid(y1, 0, HEIGHT-1);
	y2 = vmid(y2, 0, HEIGHT-1);
	y = y1 + 1;
	if(y2 == y1)
		w->pix[y1 * WIDTH + x] = color.middle;
	else if(y2 > y1)
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

void draw_mini_map(t_env *w, t_map *m)
{
	t_work work;
	int sector;
	int point;

	clean_render(w, 0x12CECECE);
	work.p1.x = (PL_X - PL_X) + (WIDTH / 2);
	work.p1.y = (PL_Y - PL_Y) + (HEIGHT / 2) - 1;
	work.p2.x = (PL_X - PL_X) + (WIDTH / 2);
	work.p2.y = (PL_Y - PL_Y) + (HEIGHT / 2) - 10;
	set_txtr_dot(w, work.p1.x, work.p1.y + 1, 0x12BF3030);
	vect_ab(work.p1, work.p2, w, 0x120F0F0F);
	sector = 0;
	while (sector < m->sector_count)
	{
		point = 0;
		while (point < m->sector[sector].wall_count)
		{
			work.v1.x = (m->sector[sector].dot[point].x - PL_X);
			work.v1.y = (m->sector[sector].dot[point].y - PL_Y);
			work.v2.x = (m->sector[sector].dot[point + 1].x - PL_X);
			work.v2.y = (m->sector[sector].dot[point + 1].y - PL_Y);
			work.t1.x = -(work.v1.x * PL_AS - work.v1.y * PL_AC) * 10 + (WIDTH / 2);
			work.t1.y = -(work.v1.x * PL_AC + work.v1.y * PL_AS) * 10 + (HEIGHT / 2);
			work.t2.x = -(work.v2.x * PL_AS - work.v2.y * PL_AC) * 10 + (WIDTH / 2);
			work.t2.y = -(work.v2.x * PL_AC + work.v2.y * PL_AS) * 10 + (HEIGHT / 2);
			vect_ab(work.t1, work.t2, w, 0x12FF0000);
			point++;
		}
		sector++;
	}
}

void draw(t_env *w, t_map *m)
{
	int point;
	int x;
	t_work work;
	t_reader read;
	int renderedsectors[m->sector_count];

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
		point = 0;
		while (point < m->sector[read.now.sectorno].wall_count)
		{
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
			if (work.t1.z <= 0 && work.t2.z <= 0) 
			{
				point++;
				continue;
			}
			if (work.t1.z <= 0 || work.t2.z <= 0)
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
				vertical_line_moche(x, work.ytop[x], work.cya - 1, w, 0x12677179);
				vertical_line(x, work.cyb + 1, work.ybot[x], w, work.color2);
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
					if (x == work.x1 || x == work.x2)
					{
						work.color.middle = 0;
						vertical_line(x, work.cya, work.cnya - 1, w, work.color);
					}
					else
					{
						work.color.middle = work.r1;
						vertical_line(x, work.cya, work.cnya - 1, w, work.color);
					}
					work.ytop[x] = vmid(vmax(work.cya, work.cnya), work.ytop[x], HEIGHT - 1);
					if (x == work.x1 || x == work.x2)
					{
							work.color.middle = 0;
						vertical_line(x, work.cnyb + 1, work.cyb, w, work.color);
						} 
					else
					{
						work.color.middle = work.r2;
						vertical_line(x, work.cnyb + 1, work.cyb, w, work.color);
					}
					work.ybot[x] = vmid(vmin(work.cyb, work.cnyb), 0, work.ybot[x]);
				}
				else
				{
					work.r = 0x12010101 * (255 - work.z);
					if (x == work.x1 || x == work.x2)
					{
						if (m->trippymod == 1)
							set_wall_trippy(w, x, work.cya, work.cyb, 0);	
						else
						{
							work.color.middle = 0;
							vertical_line(x, work.cya, work.cyb, w, work.color);
						}
					}
					else
					{
						if (m->trippymod == 1)
						{
							work.r = 0x129EFD38 * (255 - work.z);
							set_wall_trippy(w, x, work.cya, work.cyb, work.r);
						}
						else
						{
							work.color.middle = work.r;
							vertical_line(x, work.cya, work.cyb, w, work.color);
						}
					}
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
}
