/*BIG42HEADER*/

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

void	skybox(int x, t_env *w, t_work work, t_texture text)
{
	int		y = 0;
	int		y1;
	int		y2;
	double	width;
	double	height;

	int 		tmpix;

	y1 = work.starty;
	y2 = work.stopy;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = 0x12677179;
	else if (y2 > y1)
	{
		while (y <= y2)
		{
			if (y >= work.cya && y <= work.cyb) 
			{
				y = work.cyb;
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

void	ceiling_line_textured(int x, t_env *w, t_work work, t_texture text)
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
	y1 = work.starty;
	y2 = work.stopy;
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
		w->pix[y1 * WIDTH + x] = 0;
	else if (y2 > y1)
	{
		while (y <= y2)
		{
			if (y >= work.cya && y <= work.cyb) 
			{
				y = work.cyb;
				continue;
			}
			hei = y < work.cya ? work.yceil : work.yfloor;
			mapz = hei * HEIGHT * hfov / ((HEIGHT / 2 - y) - w->m->player.yaw * HEIGHT * vfov);
			mapx = mapz * (WIDTH / 2 - x) / (WIDTH * hfov);
			rtx = mapz * work.pcos + mapx * work.psin;
            rtz = mapz * work.psin - mapx * work.pcos;
            mapx = rtx + w->m->player.coor.x;
			mapz = rtz + w->m->player.coor.y;
			// attention appele 1 milliard de fois
			// test_sprite(w->m, mapx, mapz);
			test_sprite2(w->m, mapx, mapz);
			txtx = (mapx * text.w / 6);
			txtz = (mapz * text.w / 6);
			tmpix = (Uint32)(txtz % text.h) * text.w + ((Uint32)txtx % text.w);
			if (tmpix > 0 && text.pix[tmpix] != 0xFF00FF00)
				w->pix[y * WIDTH + x] = text.pix[tmpix];
			y++;
		}
	}
}

void	vertical_line_textured(int x, t_env *w, t_work work, t_texture text)
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
	y1 = work.starty;
	y2 = work.stopy;
	wall_height_from_bottom = work.yb - y1;
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = 0;
	else if (y2 > y1)
	{
		wall_height_scale = (work.yceil - work.yfloor) / TEXT_WALL_HEIGHT;
		wall_width_scale = TEXT_WALL_WIDTH / 2 / work.wall_width;
		if (fabs(work.t2.x - work.t1.x) > fabs(work.t2.z - work.t1.z))
        {	
			work.start_x_tex = (work.t1.x - work.tt1.x) * text.w / wall_width_scale / (work.tt2.x - work.tt1.x);
			work.end_x_tex = (work.t2.x - work.tt1.x) * text.w / wall_width_scale / (work.tt2.x - work.tt1.x);
		}
		else
        {
			work.start_x_tex = (work.t1.z - work.tt1.z) * text.w / wall_width_scale / (work.tt2.z - work.tt1.z);
			work.end_x_tex = (work.t2.z - work.tt1.z) * text.w / wall_width_scale / (work.tt2.z - work.tt1.z);
		}
		y_tex_start = (work.y2a - work.y1a) * ((work.x2 - work.x1) - (x - work.x1)) / (work.x2 - work.x1) - work.y2a;
		alpha = (x - work.x1) / (work.x2 - work.x1);
		x_tex = ((work.start_x_tex * ((work.x2 - x) * work.t2.z) + work.end_x_tex * ((x - work.x1) * work.t1.z)) / ((work.x2 - x) * work.t2.z + (x-work.x1) * work.t1.z));
		if ((work.y1a < 0 || work.y2a < 0) && y1 == 0)
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
