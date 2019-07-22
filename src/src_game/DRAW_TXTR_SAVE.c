/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DRAW_TXTR_SAVE.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 00:53:56 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/22 19:25:16 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "doom.h"

int		dark_side(int color, t_work *work)
{
	int R;
	int G;
	int B;

	R = vmid((((color >> 16) & 0xff) - (work->z / 2)), 0, 255);
	G = vmid((((color >> 8) & 0xff) - (work->z / 2)), 0, 255);
	B = vmid((((color) & 0xff) - (work->z / 2)), 0, 255);
	return(0 << 24 | (R & 0xff) << 16 | (G & 0xff) << 8 | (B & 0xff));
}

void	skybox(int x, t_env *w, t_work *work, t_texture text)
{
	int			y1;
	int			y2;
	double		y_tex;
	double		x_tex;
	int 		tmpix;

	y1 = vmid(work->starty, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (y2 >= y1)
	{
		while (y1 <= y2)
		{
			x_tex = (x * (text.w / 4)) / WIDTH + ((w->m->player.angle 
				* (180 / PI)) * text.w) / 360;
			y_tex = (((y1 + w->m->yaw / 0.004 + 500) * text.h) 
				/ HEIGHT / ((1576.f / (double)HEIGHT)));
			tmpix = (int)((int)y_tex % text.h) * text.w + ((int)x_tex % text.w);
			if (tmpix >= 0 && tmpix < text.h * text.w)
				w->pix[y1 * WIDTH + x] = text.pix[tmpix];
			else
				w->pix[y1 * WIDTH + x] = 0;
			y1++;
		}
	}
}

void	draw_ceiling_line_t(int x, t_env *w, t_work *work, t_texture text)
{
	int			y1;
	int			y2;
	double		hei;
	double		mapx;
	double		mapz;
	double		rtx;
	double		rtz;
	unsigned	txtx;
	unsigned	txtz;
	double 		vfov;
	double 		hfov;
	int 		tmpix;

	y1 = vmid(work->starty, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	vfov = w->m->player.field_of_vision_v / (double)HEIGHT;
	hfov = w->m->player.field_of_vision_h / (double)WIDTH;
	if (y2 >= y1)
	{
		while (y1 <= y2)
		{
			if (y1 >= work->cya && y1 <= work->cyb && y2 != y1) 
			{
				y1 = work->cyb;
				continue;
			}
			hei = y1 < work->cya ? work->yceil : work->yfloor;
			mapz = hei * HEIGHT * vfov / ((HEIGHT / 2 - y1) - w->m->player.yaw * HEIGHT * vfov);
			mapx = mapz * (WIDTH / 2 - x) / (WIDTH * hfov);
			rtx = mapz * work->pcos + mapx * work->psin;
            rtz = mapz * work->psin - mapx * work->pcos;
            mapx = (rtx) + w->m->player.coor.x;
			mapz = rtz + w->m->player.coor.y;
			test_sprite(w->m, mapx, mapz);
			txtx = (mapx * text.w / 6);
			txtz = (mapz * text.w / 6);
			tmpix = (txtz % text.h) * text.w + (txtx % text.w);
			if (tmpix >= 0 && text.pix[tmpix] != TRANSPARENT)
				w->pix[y1 * WIDTH + x] = text.pix[tmpix];
			y1++;
		}
	}
}

void	draw_high_line_t(int x, t_env *w, t_work *work, t_texture text)
{
	t_draw	d;
	int		y1;
	int		y2;
	double	wall_height_from_bottom;
	double 	wall_height_scale;
	double 	wall_width_scale;
	double	y_tex_start;
	int 	x_tex;
	int		y_tex;
	double	d.y_tex_pos;
	int		color;
	
	d.y_tex_pos = 0;
	y1 = vmid(work->starty, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	wall_height_from_bottom = work->yb - work->starty;
	if (y2 > y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
		{
			wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
			wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
			{	
				work->start_x_tex = (work->t1.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
				work->end_x_tex = (work->t2.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
			}
			else
			{
				work->start_x_tex = (work->t1.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
				work->end_x_tex = (work->t2.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
			}
			y_tex_start = (work->starty - work->ya);
			x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			wall_height_from_bottom += y_tex_start;
			d.y_tex_pos += y_tex_start;
			while (y1 <= y2)
			{
				y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
				if (y_tex < 0)
					y_tex = 0;
				if (x_tex < 0)
					x_tex = 0;
				if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
				{
					color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
					color = dark_side(color, work);
					w->pix[y1 * WIDTH + x] = color;
				}
				d.y_tex_pos++;
				y1++;
			}
		}
		else
		{		
			wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
			{	
				work->start_x_tex = (work->t1.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
				work->end_x_tex = (work->t2.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
			}
			else
			{
				work->start_x_tex = (work->t1.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
				work->end_x_tex = (work->t2.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
			}
			y_tex_start = (work->y2a - work->y1a) * ((work->x2 - work->x1) - (x - work->x1)) / (work->x2 - work->x1) - work->y2a;
			x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			if ((work->y1a < 0 || work->y2a < 0) && y1 == 0)
			{
				wall_height_from_bottom += y_tex_start;
				d.y_tex_pos += y_tex_start;
				while (y1 <= y2)
				{
					y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = dark_side(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					d.y_tex_pos++;
					y1++;
				}
			}
			else
			{
				while (y1 <= y2)
				{
					y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = dark_side(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					d.y_tex_pos++;
					y1++;
				}
			}
		}
	}
}

void	draw_wall_line_t(int x, t_env *w, t_work *work, t_texture text)
{
	int		y1;
	int		y2;
	double	wall_height_from_bottom;
	double 	wall_height_scale;
	double 	wall_width_scale;
	double	y_tex_start;
	int 	x_tex;
	int		y_tex;
	double	d.y_tex_pos;
	int 	color;
	
	
	d.y_tex_pos = 0;
	y1 = vmid(work->starty, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (vmid(work->ytop[x], 0, HEIGHT - 1) == y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
	{
		wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
		wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
		wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
		if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
		{	
			work->start_x_tex = (work->t1.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
			work->end_x_tex = (work->t2.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
		}
		else
		{
			work->start_x_tex = (work->t1.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
			work->end_x_tex = (work->t2.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
		}
		y_tex_start = (work->starty - work->ya);
		x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
		wall_height_from_bottom += y_tex_start;
		d.y_tex_pos += y_tex_start;
		while (y1 <= y2)
		{
			y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
			if (y_tex < 0)
				y_tex = 0;
			if (x_tex < 0)
				x_tex = 0;
			if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
			{
				color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
				color = dark_side(color, work);
				w->pix[y1 * WIDTH + x] = color;
			}
			d.y_tex_pos++;
			y1++;
		}
	}
	else
	{
		wall_height_from_bottom = work->yb - work->starty;
		if (y2 > y1)
		{
			wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
			{	
				work->start_x_tex = (work->t1.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
				work->end_x_tex = (work->t2.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
			}
			else
			{
				work->start_x_tex = (work->t1.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
				work->end_x_tex = (work->t2.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
			}
			y_tex_start = (work->y2a - work->y1a) * ((work->x2 - work->x1) - (x - work->x1)) / (work->x2 - work->x1) - work->y2a;
			x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			if ((work->y1a < 0 || work->y2a < 0) && y1 == 0)
			{
				wall_height_from_bottom += y_tex_start;
				d.y_tex_pos += y_tex_start;
				while (y1 <= y2)
				{
					y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = dark_side(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					d.y_tex_pos++;
					y1++;
				}
			}
			else
			{
				wall_height_from_bottom = work->yb - work->ya;
				while (y1 <= y2)
				{
					y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = dark_side(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					d.y_tex_pos++;
					y1++;
				}
			}
		}
	}	
}

void	draw_low_line_t(int x, t_env *w, t_work *work, t_texture text)
{
	int		y1;
	int		y2;
	int		wall_height_from_bottom;
	int 	x_tex;
	int		y_tex;
	double 	wall_height_scale;
	double 	wall_width_scale;
	double	y_tex_start;
	double	d.y_tex_pos;
	int		color;
	
	d.y_tex_pos = 0;
	y1 = vmid(work->starty - 1, 0, HEIGHT - 1);
	y2 = vmid(work->stopy, 0, HEIGHT - 1);
	
	if (y2 > y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
		{
			wall_height_from_bottom = (work->yb - work->ya) - (work->starty - 1 - work->ya);
			wall_height_scale = (work->nyfloor - work->yfloor) / TEXT_WALL_HEIGHT;
			wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
			{	
				work->start_x_tex = (work->t1.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
				work->end_x_tex = (work->t2.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
			}
			else
			{
				work->start_x_tex = (work->t1.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
				work->end_x_tex = (work->t2.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
			}
			y_tex_start = (work->starty - 1) - (work->nyb);
			x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			wall_height_from_bottom += y_tex_start;
			d.y_tex_pos += y_tex_start;
			while (y1 <= y2)
			{
				y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
				if (y_tex < 0)
					y_tex = 0;
				if (x_tex < 0)
					x_tex = 0;
				if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
				{
					color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
					color = dark_side(color, work);
					w->pix[y1 * WIDTH + x] = color;
				}
				d.y_tex_pos++;
				y1++;
			}
		}
		// else if ((work->cnyb < work->cya))
		// {
		// 	wall_height_from_bottom = work->yb - vmid(work->cnyb + 1, 0, HEIGHT - 1);
		// 	wall_height_scale = (work->nyfloor - work->yfloor) / TEXT_WALL_HEIGHT;
		// 	wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
		// 	if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
		// 	{	
		// 		work->start_x_tex = (work->t1.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
		// 		work->end_x_tex = (work->t2.x - work->tt1.x) * text.w / wall_width_scale / (work->tt2.x - work->tt1.x);
		// 	}
		// 	else
		// 	{
		// 		work->start_x_tex = (work->t1.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
		// 		work->end_x_tex = (work->t2.z - work->tt1.z) * text.w / wall_width_scale / (work->tt2.z - work->tt1.z);
		// 	}
		// 	y_tex_start = (work->starty - 1) - (work->ya);
		// 	x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
		// 	wall_height_from_bottom += y_tex_start;
		// 	d.y_tex_pos += y_tex_start;
		// 	while (y1 <= y2)
		// 	{
		// 		y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
		// 		if (y_tex < 0)
		// 			y_tex = 0;
		// 		if (x_tex < 0)
		// 			x_tex = 0;
		// 		if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
		// 		{
		// 			color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
		// 			color = dark_side(color, work);
		// 			w->pix[y1 * WIDTH + x] = color;
		// 		}
		// 		d.y_tex_pos++;
		// 		y1++;
		// 	}
		// }
		else
		{
			wall_height_from_bottom = work->yb - y1;
			if (work->cnyb < work->cya)
				wall_height_scale = (work->nyfloor - work->yfloor) / TEXT_WALL_HEIGHT;
			else
				wall_height_scale = (work->nyfloor - work->yfloor) / TEXT_WALL_HEIGHT;
			wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			if (vabs(work->t2.x -work->t1.x) > vabs(work->t2.z -work->t1.z))
			{	
				work->start_x_tex = (work->t1.x -work->tt1.x) * text.w / wall_width_scale / (work->tt2.x -work->tt1.x);
				work->end_x_tex = (work->t2.x -work->tt1.x) * text.w / wall_width_scale / (work->tt2.x -work->tt1.x);
			}
			else
			{
				work->start_x_tex = (work->t1.z -work->tt1.z) * text.w / wall_width_scale / (work->tt2.z -work->tt1.z);
				work->end_x_tex = (work->t2.z -work->tt1.z) * text.w / wall_width_scale / (work->tt2.z -work->tt1.z);
			}
			y_tex_start = (work->ny2b - work->ny1b) * ((work->x2 -work->x1) - (x -work->x1)) / (work->x2 -work->x1) - work->ny2b;
			x_tex = ((work->start_x_tex * ((work->x2 - x) *work->t2.z) +work->end_x_tex * ((x -work->x1) *work->t1.z)) / ((work->x2 - x) *work->t2.z + (x-work->x1) *work->t1.z));
			if (((work->y1a < 0 || work->y2a < 0) && y1 == 0) || vmid(work->cnyb, 0, HEIGHT - 1) == 0)
			{
				wall_height_from_bottom += y_tex_start;
				d.y_tex_pos += y_tex_start;
				while (y1 <= y2)
				{
					y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = dark_side(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					d.y_tex_pos++;
					y1++;
				}
			}
			else
			{
				while (y1 <= y2)
				{
					y_tex = (d.y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != TRANSPARENT)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = dark_side(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					d.y_tex_pos++;
					y1++;
				}
			}
		}
	}
}
