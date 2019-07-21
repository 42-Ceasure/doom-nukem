/*BIG42HEADER*/

#include "doom.h"

void	draw_textured_line(t_draw *d, t_env *w, t_work *work, t_texture *text)
{
	while (d->y1 <= d->y2)
	{
		d->y_tex = (d->y_tex_pos / d->wall_height_from_bottom * d->wall_height_scale) * text->h;
		if (d->y_tex < 0)
			d->y_tex = 0;
		if (d->x_tex < 0)
			d->x_tex = 0;
		if (text->h >= 0 && text->w >= 0 && text->pix[((d->y_tex % text->h) * text->w) + (d->x_tex % text->w)] != 0xFF00FF00)
		{
			d->color = text->pix[((d->y_tex % text->h) * text->w) + (d->x_tex % text->w)];
			d->color = dark_side(d->color, work);
			w->pix[d->y1 * WIDTH + d->x] = d->color;
		}
		d->y_tex_pos++;
		d->y1++;
	}
}

void	check_start_end_tex(t_draw *d, t_work *work, t_texture *text)
{
	if (vabs(work->t2.x - work->t1.x) > vabs(work->t2.z - work->t1.z))
	{	
		work->start_x_tex = (work->t1.x - work->tt1.x) * text->w / d->wall_width_scale / (work->tt2.x - work->tt1.x);
		work->end_x_tex = (work->t2.x - work->tt1.x) * text->w / d->wall_width_scale / (work->tt2.x - work->tt1.x);
	}
	else
	{
		work->start_x_tex = (work->t1.z - work->tt1.z) * text->w / d->wall_width_scale / (work->tt2.z - work->tt1.z);
		work->end_x_tex = (work->t2.z - work->tt1.z) * text->w / d->wall_width_scale / (work->tt2.z - work->tt1.z);
	}
}

void	draw_high_line_t(int x, t_env *w, t_work *work, t_texture *text)
{
	t_draw	d;
	
	d.x = x;
	d.y_tex_pos = 0;
	d.y1 = vmid(work->starty, 0, HEIGHT - 1);
	d.y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (d.y2 > d.y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == d.y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
		{
			d.wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
			d.wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			d.wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			check_start_end_tex(&d, work, text);
			d.y_tex_start = (work->starty - work->ya);
			d.x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			d.wall_height_from_bottom += d.y_tex_start;
			d.y_tex_pos += d.y_tex_start;
			draw_textured_line(&d, w, work, text);
		}
		else
		{
			d.wall_height_from_bottom = work->yb - work->starty;
			d.wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			d.wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			check_start_end_tex(&d, work, text);
			d.y_tex_start = (work->y2a - work->y1a) * ((work->x2 - work->x1) - (x - work->x1)) / (work->x2 - work->x1) - work->y2a;
			d.x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			if ((work->y1a < 0 || work->y2a < 0) && d.y1 == 0)
			{
				d.wall_height_from_bottom += d.y_tex_start;
				d.y_tex_pos += d.y_tex_start;
				draw_textured_line(&d, w, work, text);
			}
			else
				draw_textured_line(&d, w, work, text);
		}
	}
}

void	draw_wall_line_t(int x, t_env *w, t_work *work, t_texture *text)
{
	t_draw	d;	
	
	d.x = x;
	d.y_tex_pos = 0;
	d.y1 = vmid(work->starty, 0, HEIGHT - 1);
	d.y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (d.y2 > d.y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == d.y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
		{
			d.wall_height_from_bottom = (work->yb - work->ya) - (work->starty - work->ya);
			d.wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			d.wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			check_start_end_tex(&d, work, text);
			d.y_tex_start = (work->starty - work->ya);
			d.x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			d.wall_height_from_bottom += d.y_tex_start;
			d.y_tex_pos += d.y_tex_start;
			draw_textured_line(&d, w, work, text);
		}
		else
		{
			d.wall_height_from_bottom = work->yb - work->starty;
			d.wall_height_scale = (work->yceil - work->yfloor) / TEXT_WALL_HEIGHT;
			d.wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			check_start_end_tex(&d, work, text);
			d.y_tex_start = (work->y2a - work->y1a) * ((work->x2 - work->x1) - (x - work->x1)) / (work->x2 - work->x1) - work->y2a;
			d.x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			if ((work->y1a < 0 || work->y2a < 0) && d.y1 == 0)
			{
				d.wall_height_from_bottom += d.y_tex_start;
				d.y_tex_pos += d.y_tex_start;
				draw_textured_line(&d, w, work, text);
			}
			else
			{
				d.wall_height_from_bottom = work->yb - work->ya;
				draw_textured_line(&d, w, work, text);
			}
		}
	}	
}

void	draw_low_line_t(int x, t_env *w, t_work *work, t_texture *text)
{
	t_draw	d;
	
	d.x = x;
	d.y_tex_pos = 0;
	d.y1 = vmid(work->starty - 1, 0, HEIGHT - 1);
	d.y2 = vmid(work->stopy, 0, HEIGHT - 1);
	if (d.y2 > d.y1)
	{
		if (vmid(work->ytop[x], 0, HEIGHT - 1) == d.y1 && vmid(work->ytop[x], 0, HEIGHT - 1) > 0)
		{
			d.wall_height_from_bottom = (work->yb - work->ya) - (work->starty - 1 - work->ya);
			d.wall_height_scale = (work->nyfloor - work->yfloor) / TEXT_WALL_HEIGHT;
			d.wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			check_start_end_tex(&d, work, text);
			d.y_tex_start = (work->starty - 1) - (work->nyb);
			d.x_tex = ((work->start_x_tex * ((work->x2 - x) * work->t2.z) + work->end_x_tex * ((x - work->x1) * work->t1.z)) / ((work->x2 - x) * work->t2.z + (x-work->x1) * work->t1.z));
			d.wall_height_from_bottom += d.y_tex_start;
			d.y_tex_pos += d.y_tex_start;
			draw_textured_line(&d, w, work, text);
		}
		else
		{
			d.wall_height_from_bottom = work->yb - d.y1;
			d.wall_height_scale = (work->nyfloor - work->yfloor) / TEXT_WALL_HEIGHT;
			d.wall_width_scale = TEXT_WALL_WIDTH / 2 / work->wall_width;
			check_start_end_tex(&d, work, text);
			d.y_tex_start = (work->ny2b - work->ny1b) * ((work->x2 -work->x1) - (x -work->x1)) / (work->x2 -work->x1) - work->ny2b;
			d.x_tex = ((work->start_x_tex * ((work->x2 - x) *work->t2.z) +work->end_x_tex * ((x -work->x1) *work->t1.z)) / ((work->x2 - x) *work->t2.z + (x-work->x1) *work->t1.z));
			if (((work->y1a < 0 || work->y2a < 0) && d.y1 == 0) || vmid(work->cnyb, 0, HEIGHT - 1) == 0)
			{
				d.wall_height_from_bottom += d.y_tex_start;
				d.y_tex_pos += d.y_tex_start;
				draw_textured_line(&d, w, work, text);
			}
			else
				draw_textured_line(&d, w, work, text);
		}
	}
}
