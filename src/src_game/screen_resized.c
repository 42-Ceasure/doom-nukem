/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_resized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:15:26 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/22 16:24:36 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int	test_limits_to_screen(t_img *img, t_scalling *s, t_env *w)
{
	if (img->y < 0 || img->y >= HEIGHT)
		return (0);
	if (img->x < 0 || img->x >= WIDTH)
		return (0);
	if ((int)s->y_tex < 0 || (int)s->y_tex >= s->text_h)
		return (0);
	if ((int)s->x_tex < 0 || (int)s->x_tex >= s->text_w)
		return (0);
	return (1);
}

int	init_and_check_to_screen(t_scalling *s, t_env *w, t_img *img)
{
	s->x_tex = 0;
	s->y_tex = 0;
	s->step_x_tex = (double)s->text_w / (double)img->w;
	s->step_y_tex = (double)s->text_h / (double)img->h;
	s->maxx = img->w + img->x;
	s->maxy = img->h + img->y;
	if (s->maxx < 0 || s->maxy < 0 || img->x > WIDTH || img->y > HEIGHT)
		return (0);
	s->maxx = vmin(s->maxx, WIDTH);
	s->maxy = vmin(s->maxy, HEIGHT);
	if (img->x < 0)
	{
		s->x_tex = (0 - img->x) * s->step_x_tex;
		img->x = 0;
	}
	if (img->y < 0)
	{
		s->y_tex = (0 - img->y) * s->step_y_tex;
		img->y = 0;
	}
	s->x_tmp = img->x;
	s->x_tex_tmp = s->x_tex;
	return (1);
}

void	get_scalling(t_img *img, t_scalling *s, int text_w, int text_h)
{
	if (s != NULL)
	{
		s->text_w = text_w;
		s->text_h = text_h;
	}
	if (img->w == 0 && img->h == 0)
	{
		img->w = text_w;
		img->h = text_h;
	}
	else if (img->w == 0 || img->h == 0)
	{
		if (img->w == 0)
			img->w = (int)(img->h * text_w / text_h);
		else
			img->h = (int)(img->w * text_h / text_w);
	}
}

t_img	fill_t_img(int x, int y, int w, int h)
{
	t_img img;

	img.x = x;
	img.y = y;
	img.w = w;
	img.h = h;
	return (img);
}

int		img_to_screen(t_env *w, t_texture texture, t_img img)
{
	t_scalling	s;

	get_scalling(&img, &s, texture.w, texture.h);
	if (init_and_check_to_screen(&s, w, &img) == 0)
		return (0);
	while (img.y < s.maxy && (int)s.x_tex * (int)s.y_tex < texture.len)
	{
		img.x = s.x_tmp;
		s.x_tex = s.x_tex_tmp;
		while (img.x < s.maxx && (int)s.x_tex * (int)s.y_tex < texture.len)
		{
			if (test_limits_to_screen(&img, &s, w) == 1)
			{
				s.tmpix = (int)s.y_tex * texture.w + (int)s.x_tex;
				if (texture.pix[s.tmpix] != TRANSPARENT)
					w->pix[img.y * WIDTH + img.x] = texture.pix[s.tmpix];
			}
			s.x_tex += s.step_x_tex;
			img.x++;
		}
		s.y_tex += s.step_y_tex;
		if (w->sequential_frame == 1 && (img.y % 2 == 0))
			img_update(w);
		img.y++;
	}
	return (1);
}

int		sprt_to_screen(t_env *w, t_sprite sprite, t_img img)
{
	t_scalling	s;

	get_scalling(&img, &s, sprite.w, sprite.h);
	if (init_and_check_to_screen(&s, w, &img) == 0)
		return (0);
	while (img.y < s.maxy && (int)s.x_tex * (int)s.y_tex < sprite.len)
	{
		img.x = s.x_tmp;
		s.x_tex = s.x_tex_tmp;
		while (img.x < s.maxx && (int)s.x_tex * (int)s.y_tex < sprite.len)
		{
			if (test_limits_to_screen(&img, &s, w) == 1)
			{
				s.tmpix = (int)s.y_tex * sprite.w + (int)s.x_tex;
				if (sprite.pix[s.tmpix] != TRANSPARENT)
					w->pix[img.y * WIDTH + img.x] = sprite.pix[s.tmpix];
			}
			s.x_tex += s.step_x_tex;
			img.x++;
		}
		s.y_tex += s.step_y_tex;
		if (w->sequential_frame == 1 && (img.y % 2 == 0))
			img_update(w);
		img.y++;
	}
	return (1);
}

int		char_to_screen(t_env *w, t_texture texture, t_img img)
{
	t_scalling	s;

	get_scalling(&img, &s, texture.w, texture.h);
	if (init_and_check_to_screen(&s, w, &img) == 0)
		return (0);
	while (img.y < s.maxy && (int)s.x_tex * (int)s.y_tex < texture.len)
	{
		img.x = s.x_tmp;
		s.x_tex = s.x_tex_tmp;
		while (img.x < s.maxx && (int)s.x_tex * (int)s.y_tex < texture.len)
		{
			if (test_limits_to_screen(&img, &s, w) == 1)
			{
				s.tmpix = (int)s.y_tex * texture.w + (int)s.x_tex;
				if (texture.pix[s.tmpix] != texture.pix[0])
					w->pix[img.y * WIDTH + img.x] = w->txt.color;
			}
			s.x_tex += s.step_x_tex;
			img.x++;
		}
		s.y_tex += s.step_y_tex;
		if (w->sequential_frame == 1 && (img.y % 2 == 0))
			img_update(w);
		img.y++;
	}
	return (1);
}

int		get_tmpix_scaled(t_sprite sprite, t_img img)
{
	double 	step_x_tex;
	double 	step_y_tex;

	get_scalling(&img, NULL, sprite.w, sprite.h);
	step_x_tex = (double)sprite.w / (double)img.w;
	step_y_tex = (double)sprite.h / (double)img.h;
	return ((int)(step_x_tex * img.x) + ((int)(step_y_tex * img.y) * sprite.w));
}
