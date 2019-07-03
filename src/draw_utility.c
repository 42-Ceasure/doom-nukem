/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 19:04:35 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/03 23:36:19 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	skybox2(t_env *w, t_texture text)
{
	int		y1;
	int		y2;
	int		x = 0;
	double	width;
	double	height;

	int 		tmpix;

	y2 = HEIGHT;
	while (x < WIDTH)
	{
		y1 = 0;
		while (y1 <= y2)
		{
			width = (x * (text.w / 4)) / WIDTH + ((w->m->player.angle * (180 / PI)) * text.w) / 360;
			height = (((y1 + w->m->yaw / 0.004 + text.h) * text.h) / HEIGHT / 2);
			// Better? : 
			// width = x + (w->m->player.angle * (180 / PI)/ 2 * text.w) / 360;
			// height = (((y + text.h) + w->m->yaw / 0.004) * text.h) / HEIGHT / 2;
			tmpix = (int)((int)height % text.h) * text.w + ((int)width % text.w);
			if (tmpix > 0 && tmpix < text.h * text.w)
				w->pix[y1 * WIDTH + x] = text.pix[tmpix];
			else
				w->pix[y1 * WIDTH + x] = 0;
			y1++;
		}
		x++;
	}
}

void	skybox(int x, int *box, t_env *w, t_draw *d, t_texture text)
{
	int		y = 0;
	int		y1;
	int		y2;
	double	width;
	double	height;

	int 		tmpix;

	y1 = box[0];
	y2 = box[1];
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = 0x12677179;
	else if (y2 > y1)
	{
		while (y <= y2)
		{
			if (y >= d->cya && y <= d->cyb) 
			{
				y = d->cyb;
				continue;
			}
			width = (x * (text.w / 4)) / WIDTH + ((w->m->player.angle * (180 / PI)) * text.w) / 360;
			height = (((y + w->m->yaw / 0.004 + text.h) * text.h) / HEIGHT / 2);
			// Better? : 
			// width = x + (w->m->player.angle * (180 / PI)/ 2 * text.w) / 360;
			// height = (((y + text.h) + w->m->yaw / 0.004) * text.h) / HEIGHT / 2;
			tmpix = (int)((int)height % text.h) * text.w + ((int)width % text.w);
			if (tmpix > 0 && tmpix < text.h * text.w)
				w->pix[y * WIDTH + x] = text.pix[tmpix];
			else
				w->pix[y * WIDTH + x] = 0;
			y++;
		}
	}
}

void	ceiling_line(int x, int *box, t_env *w, Uint32 color)
{
	int		y;
	int		y1;
	int		y2;

	y1 = box[0];
	y2 = box[1];
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

void	vertical_line(int x, int *box, t_env *w, t_color color)
{
	int		y;
	int		y1;
	int		y2;

	y1 = box[0];
	y2 = box[1];
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

void	ceiling_line_textured(int x, int *box, t_env *w, t_draw *d, t_texture text)
{
	int		y = 0;
	int		y1;
	int		y2;
	double	hei;
	double	mapx;
	double	mapz;
	double	rtx;
	double	rtz;
	unsigned	txtx;
	unsigned	txtz;
	double 		vfov;
	double 		hfov;

	Uint32 		tmpix;
	y1 = box[0];
	y2 = box[1];
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1;
	vfov = (1.0 * .5f);
	hfov = 1.0 * 0.9f * HEIGHT / WIDTH;
	if (w->m->player.aiming == 1)
	{
		hfov *= 2;
		vfov *= 2;
	}
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = 0x12677179;
	else if (y2 > y1)
	{
		while (y <= y2)
		{
			if (y >= d->cya && y <= d->cyb) 
			{
				y = d->cyb;
				continue;
			}
			hei = y < d->cya ? d->yceil : d->yfloor;
			if (w->m->player.aiming == 0)
			{
				mapz = hei * HEIGHT * hfov / ((HEIGHT / 2 - y) - w->m->player.yaw * HEIGHT * vfov);
				mapx = mapz * (WIDTH / 2 - x) / (WIDTH * hfov);
			}
			else
			{
				mapz = hei * (HEIGHT) * hfov / (((HEIGHT) / 2 - y) - w->m->player.yaw * (HEIGHT) * vfov);
				mapx = mapz * ((WIDTH) / 2 - x) / (WIDTH) * hfov;
			}
			rtx = mapz * d->pcos + mapx * d->psin;
            rtz = mapz * d->psin - mapx * d->pcos;
            mapx = rtx + w->m->player.coor.x;
			mapz = rtz + w->m->player.coor.y;
			// attention appele 1 milliard de fois
			test_sprite(w->m, mapx, mapz);
			txtx = (mapx * text.w / 6);
			txtz = (mapz * text.w / 6);
			tmpix = (Uint32)(txtz % text.h) * text.w + ((Uint32)txtx % text.w);
			if (tmpix > 0 && text.pix[tmpix] != 0xFF00FF00)
				w->pix[y * WIDTH + x] = text.pix[tmpix];
			y++;
		}
	}
}

void	vertical_line_textured(int x, int *box, t_env *w, t_draw *d, t_texture text)
{
	int		y;
	int		y1;
	int		y2;
	double	wall_height_from_bottom;
	double 	wall_height_scale;
	double 	wall_width_scale;
	double	y_tex_start;
	int 	x_tex;
	int		y_tex;
	double	y_tex_pos;
	double	alpha;
	
	y_tex_pos = 0;
	y1 = box[0];
	y2 = box[1];
	wall_height_from_bottom = d->yb - y1;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = d->color.middle;
	else if (y2 > y1)
	{
		wall_height_scale = (d->yceil - d->yfloor) / TEXT_WALL_HEIGHT;
		wall_width_scale = TEXT_WALL_WIDTH / 2 / d->wall_width;
		if (fabs(d->t2.x - d->t1.x) > fabs(d->t2.z - d->t1.z))
        {	
			d->start_x_tex = (d->t1.x - d->tt1.x) * text.w / wall_width_scale / (d->tt2.x - d->tt1.x);
			d->end_x_tex = (d->t2.x - d->tt1.x) * text.w / wall_width_scale / (d->tt2.x - d->tt1.x);
		}
		else
        {
			d->start_x_tex = (d->t1.z - d->tt1.z) * text.w / wall_width_scale / (d->tt2.z - d->tt1.z);
			d->end_x_tex = (d->t2.z - d->tt1.z) * text.w / wall_width_scale / (d->tt2.z - d->tt1.z);
		}
		y_tex_start = (d->y2a - d->y1a) * ((d->x2 - d->x1) - (x - d->x1)) / (d->x2 - d->x1) - d->y2a;
		alpha = (x - d->x1) / (d->x2 - d->x1);
		x_tex = ((d->start_x_tex * ((d->x2 - x) * d->t2.z) + d->end_x_tex * ((x - d->x1) * d->t1.z)) / ((d->x2 - x) * d->t2.z + (x-d->x1) * d->t1.z));
		if ((d->y1a < 0 || d->y2a < 0) && y1 == 0)
		{
			wall_height_from_bottom += y_tex_start;
			y_tex_pos += y_tex_start;
			while (y <= y2)
			{
				y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
				if (y_tex < 0)
					y_tex = 0;
				if (x_tex < 0)
					x_tex = 0;
				if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					w->pix[y * WIDTH + x] = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
				y_tex_pos++;
				y++;
			}
		}
		else
		{
			while (y <= y2)
			{
				y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
				if (y_tex < 0)
					y_tex = 0;
				if (x_tex < 0)
					x_tex = 0;
				if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					w->pix[y * WIDTH + x] = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
				y_tex_pos++;
				y++;
			}
		}
	}
}

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

int		init_draw(t_env *w, t_draw *d, t_reader *read, t_map *m)
{
	d->winwidth = WIDTH;
	d->winheight = HEIGHT;
	read->head = read->queue;
	read->tail = read->queue;
	read->head->sectorno = m->player.sector;
	read->head->sx1 = 0;
	read->head->sx2 = WIDTH - 1;
	if (++read->head == read->queue + m->maxrenderedsector)
		read->head = read->queue;
	d->nearz = 0.0000000001;
	d->farz = 5;
	d->nearside = 0.0000000001;
	d->farside = 20.f;
	d->color.top = 0x12111111;
	d->color.middle = 0x12222222;
	d->color.bottom = 0x12111111;
	d->color2.top = 0x120000FF;
	d->color2.middle = 0x120000AA;
	d->color2.bottom = 0x120000FF;
	return (0);
}

void	init_verification(t_draw *d)
{
	// structure intersect ??
	// vector product
	// --> evitr les flots ?
	d->i1.x1 = d->t1.x;
	d->i1.y1 = d->t1.z;
	d->i1.x2 = d->t2.x;
	d->i1.y2 = d->t2.z;
	d->i1.x3 = -d->nearside;
	d->i1.y3 = d->nearz;
	d->i1.x4 = -d->farside;
	d->i1.y4 = d->farz;
	d->i2.x1 = d->t1.x;
	d->i2.y1 = d->t1.z;
	d->i2.x2 = d->t2.x;
	d->i2.y2 = d->t2.z;
	d->i2.x3 = d->nearside;
	d->i2.y3 = d->nearz;
	d->i2.x4 = d->farside;
	d->i2.y4 = d->farz;
	d->ip1 = intersect(d->i1);
	d->ip2 = intersect(d->i2);
}
