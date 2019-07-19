/*BIG42HEADER*/

#include "doom.h"

int		testcolor(int color, t_work *work)
{
	int R = (color >> 16) & 0xff;
	int G = (color >> 8) & 0xff;
	int B = (color) & 0xff;

	R -= work->z / 2;
	G -= work->z / 2;
	B -= work->z / 2;

	if (R > 255)
		R = 255;
	if (G > 255)
		G = 255;
	if (B > 255)
		B = 255;
	if (R < 0)
		R = 0;
	if (G < 0)
		G = 0;
	if (B < 0)
		B = 0;

	return(0 << 24 | (R & 0xff) << 16 | (G & 0xff) << 8 | (B & 0xff));
}

void	skybox(int x, t_env *w, t_work *work, t_texture text)
{
	int			y1;
	int			y2;
	double		y_tex;
	double		x_tex;
	int 		tmpix;

	y1 = work->starty;
	y2 = work->stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	if (y2 >= y1)
	{
		while (y1 <= y2)
		{
			x_tex = (x * (text.w / 4)) / WIDTH + ((w->m->player.angle * (180 / PI)) * text.w) / 360;
			y_tex = (((y1 + w->m->yaw / 0.004 + 500) * text.h) / HEIGHT / ((1576.f / (double)HEIGHT)));
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

	y1 = work->starty;
	y2 = work->stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	vfov = (1.0 * .5f);
	hfov = 1.0 * 0.9f * HEIGHT / WIDTH;
	if (w->m->player.aiming == 1)
	{
		hfov *= 2;
		vfov *= 2;
	}
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
			mapz = hei * HEIGHT * hfov / ((HEIGHT / 2 - y1) - w->m->player.yaw * HEIGHT * vfov);
			mapx = mapz * (WIDTH / 2 - x) / (WIDTH * hfov);
			rtx = mapz * work->pcos + mapx * work->psin;
            rtz = mapz * work->psin - mapx * work->pcos;
            mapx = rtx + w->m->player.coor.x;
			mapz = rtz + w->m->player.coor.y;
			test_sprite(w->m, mapx, mapz);
			txtx = (mapx * text.w / 6);
			txtz = (mapz * text.w / 6);
			tmpix = (txtz % text.h) * text.w + (txtx % text.w);
			if (tmpix >= 0 && text.pix[tmpix] != 0xFF00FF00)
				w->pix[y1 * WIDTH + x] = text.pix[tmpix];
			y1++;
		}
	}
}

void	draw_vertical_line_t(int x, t_env *w, t_work *work, t_texture text)
{
	int		y1;
	int		y2;
	double	wall_height_from_bottom;
	double 	wall_height_scale;
	double 	wall_width_scale;
	double	y_tex_start;
	int 	x_tex;
	int		y_tex;
	double	y_tex_pos;
	int		color;
	
	y_tex_pos = 0;
	y1 = work->starty;
	y2 = work->stopy;
	wall_height_from_bottom = work->yb - y1;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	if (y2 > y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
		{
			wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
			// printf("YA %d YB %d YSTART %d Y1 %d\n", work->ya, work->yb, work->starty ,y1);
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
			y_tex_pos += y_tex_start;
			while (y1 <= y2)
			{
				y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
				if (y_tex < 0)
					y_tex = 0;
				if (x_tex < 0)
					x_tex = 0;
				if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
				{
					color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
					color = testcolor(color, work);
					w->pix[y1 * WIDTH + x] = color;
				}
				y_tex_pos++;
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
				y_tex_pos += y_tex_start;
				while (y1 <= y2)
				{
					y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = testcolor(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					y_tex_pos++;
					y1++;
				}
			}
			else
			{
				while (y1 <= y2)
				{
					y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = testcolor(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					y_tex_pos++;
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
	double	y_tex_pos;
	int 	color;
	
	
	y_tex_pos = 0;
	y1 = work->starty;
	y2 = work->stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	if (vmid(work->ytop[x], 0, HEIGHT - 1) == y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
	{
		wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
		// printf("YA %d YB %d YSTART %d Y1 %d\n", work->ya, work->yb, work->starty ,y1);
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
		y_tex_pos += y_tex_start;
		while (y1 <= y2)
		{
			y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
			if (y_tex < 0)
				y_tex = 0;
			if (x_tex < 0)
				x_tex = 0;
			if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
			{
				color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
				color = testcolor(color, work);
				w->pix[y1 * WIDTH + x] = color;
			}
			y_tex_pos++;
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
				y_tex_pos += y_tex_start;
				while (y1 <= y2)
				{
					y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = testcolor(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					y_tex_pos++;
					y1++;
				}
			}
			else
			{
				wall_height_from_bottom = work->yb - work->ya;
				while (y1 <= y2)
				{
					y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = testcolor(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					y_tex_pos++;
					y1++;
				}
			}
		}
	}	
}

void	draw_extruded_line_t(int x, t_env *w, t_work *work, t_texture text)
{
	int		y1;
	int		y2;
	int		wall_height_from_bottom;
	int 	x_tex;
	int		y_tex;
	double 	wall_height_scale;
	double 	wall_width_scale;
	double	y_tex_start;
	double	y_tex_pos;
	int		color;
	
	y_tex_pos = 0;
	y1 = work->starty - 1;
	y2 = work->stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	
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
			y_tex_pos += y_tex_start;
			while (y1 <= y2)
			{
				y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
				if (y_tex < 0)
					y_tex = 0;
				if (x_tex < 0)
					x_tex = 0;
				if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
				{
					color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
					color = testcolor(color, work);
					w->pix[y1 * WIDTH + x] = color;
				}
				y_tex_pos++;
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
		// 	y_tex_pos += y_tex_start;
		// 	while (y1 <= y2)
		// 	{
		// 		y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
		// 		if (y_tex < 0)
		// 			y_tex = 0;
		// 		if (x_tex < 0)
		// 			x_tex = 0;
		// 		if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
		// 		{
		// 			color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
		// 			color = testcolor(color, work);
		// 			w->pix[y1 * WIDTH + x] = color;
		// 		}
		// 		y_tex_pos++;
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
				y_tex_pos += y_tex_start;
				while (y1 <= y2)
				{
					y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = testcolor(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					y_tex_pos++;
					y1++;
				}
			}
			else
			{
				while (y1 <= y2)
				{
					y_tex = (y_tex_pos / wall_height_from_bottom * wall_height_scale) * text.h;
					if (y_tex < 0)
						y_tex = 0;
					if (x_tex < 0)
						x_tex = 0;
					if (text.h >= 0 && text.w >= 0 && text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)] != 0xFF00FF00)
					{
						color = text.pix[((y_tex % text.h) * text.w) + (x_tex % text.w)];
						color = testcolor(color, work);
						w->pix[y1 * WIDTH + x] = color;
					}
					y_tex_pos++;
					y1++;
				}
			}
		}
	}
}
