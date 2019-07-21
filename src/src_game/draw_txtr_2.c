/*BIG42HEADER*/

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

void	draw_ceiling_line_t(int x, t_env *w, t_work *work, t_texture *text)
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
            mapx = rtx + w->m->player.coor.x;
			mapz = rtz + w->m->player.coor.y;
			test_sprite(w->m, mapx, mapz);
			txtx = (mapx * text->w / 6);
			txtz = (mapz * text->w / 6);
			tmpix = (txtz % text->h) * text->w + (txtx % text->w);
			if (tmpix >= 0 && text->pix[tmpix] != 0xFF00FF00)
				w->pix[y1 * WIDTH + x] = text->pix[tmpix];
			y1++;
		}
	}
}
