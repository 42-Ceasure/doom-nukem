/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_resized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:15:26 by nvienot           #+#    #+#             */
/*   Updated: 2019/06/17 18:27:29 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

// testing implementation resizing from branch textures

int		final_texture_to_screen(t_env *w, t_texture texture, int x, int y, int width, int height)
{
	double 	step_x_tex;
	double 	step_y_tex;
	double	x_tex;
	double	y_tex;
	int 	maxx;
	int		maxy;
	Uint32	tmpix;

	x_tex = 0;
	y_tex = 0;
	if (texture.pix == NULL || w->pix == NULL || texture.h <= 0 || texture.w <= 0 || texture.len <= 0)
		return (0);
	if (width == 0 && height == 0)
	{
		width = texture.w;
		height = texture.h;
	}
	else if (width == 0 || height == 0)
	{
		if (width == 0)
			width = (int)(height * texture.w / texture.h);
		else if (height == 0)
			height = (int)(width * texture.h / texture.w);
	}
	step_x_tex = (double)texture.w / (double)width;
	step_y_tex = (double)texture.h / (double)height;
	maxx = width + x;
	maxy = height + y;
	while (y < maxy && (int)x_tex * (int)y_tex < texture.len)
	{
		x_tex = 0;
		while (x < maxx && (int)x_tex * (int)y_tex < texture.len)
		{
			if (y >= 0 && y < HEIGHT && (int)y_tex >= 0 && (int)y_tex < texture.h)
			{
				if (x >= 0 && x < WIDTH && (int)x_tex >= 0 && (int)x_tex < texture.w)
				{
					tmpix = (int)y_tex * texture.w + (int)x_tex;
					if (texture.pix[tmpix] != 0xFF00FF00)
						w->pix[y * WIDTH + x] = texture.pix[tmpix];
				}
			}
			x_tex += step_x_tex;
			x++;
		}
		x -= width;
		y_tex += step_y_tex;
		if (w->sequential_frame == 1 && (y % 2 == 0))
			img_update(w);
		y++;
	}
	return (1);
}


int		final_sprite_to_screen(t_env *w, t_sprite sprite, int x, int y, int width, int height)
{
	double 	step_x_tex;
	double 	step_y_tex;
	double	x_tex;
	double	y_tex;
	int 	maxx;
	int		maxy;
	Uint32	tmpix;

	x_tex = 0;
	y_tex = 0;
	if (sprite.pix == NULL || w->pix == NULL || sprite.h <= 0 || sprite.w <= 0 || sprite.len <= 0)
		return (0);
	if (width == 0 && height == 0)
	{
		width = sprite.w;
		height = sprite.h;
	}
	else if (width == 0 || height == 0)
	{
		if (width == 0)
			width = (int)(height * sprite.w / sprite.h);
		else if (height == 0)
			height = (int)(width * sprite.h / sprite.w);
	}
	step_x_tex = (double)sprite.w / (double)width;
	step_y_tex = (double)sprite.h / (double)height;
	maxx = width + x;
	maxy = height + y;
	while (y < maxy && (int)x_tex * (int)y_tex < sprite.len)
	{
		x_tex = 0;
		while (x < maxx && (int)x_tex * (int)y_tex < sprite.len)
		{
			if (y >= 0 && y < HEIGHT && (int)y_tex >= 0 && (int)y_tex < sprite.h)
			{
				if (x >= 0 && x < WIDTH && (int)x_tex >= 0 && (int)x_tex < sprite.w)
				{
					tmpix = (int)y_tex * sprite.w + (int)x_tex;
					if (sprite.pix[tmpix] != 0xFF00FF00)
						w->pix[y * WIDTH + x] = sprite.pix[tmpix];
				}
			}
			x_tex += step_x_tex;
			x++;
		}
		x -= width;
		y_tex += step_y_tex;
		if (w->sequential_frame == 1 && (y % 2 == 0))
			img_update(w);
		y++;
	}
	return (1);
}

int		final_char_to_screen(t_env *w, t_texture texture, int x, int y, int width, int height)
{
	double 	step_x_tex;
	double 	step_y_tex;
	double	x_tex;
	double	y_tex;
	int 	maxx;
	int		maxy;
	Uint32	tmpix;

	x_tex = 0;
	y_tex = 0;
	if (texture.pix == NULL || w->pix == NULL || texture.h <= 0 || texture.w <= 0 || texture.len <= 0)
		return (0);
	if (width == 0 && height == 0)
	{
		width = texture.w;
		height = texture.h;
	}
	else if (width == 0 || height == 0)
	{
		if (width == 0)
			width = (int)(height * texture.w / texture.h);
		else if (height == 0)
			height = (int)(width * texture.h / texture.w);
	}
	step_x_tex = (double)texture.w / (double)width;
	step_y_tex = (double)texture.h / (double)height;
	maxx = width + x;
	maxy = height + y;
	while (y < maxy && (int)x_tex * (int)y_tex < texture.len)
	{
		x_tex = 0;
		while (x < maxx && (int)x_tex * (int)y_tex < texture.len)
		{
			if (y >= 0 && y < HEIGHT && (int)y_tex >= 0 && (int)y_tex < texture.h)
			{
				if (x >= 0 && x < WIDTH && (int)x_tex >= 0 && (int)x_tex < texture.w)
				{
					tmpix = (int)y_tex * texture.w + (int)x_tex;
					if (texture.pix[tmpix] != texture.pix[0])
						w->pix[y * WIDTH + x] = w->txt.color;
				}
			}
			x_tex += step_x_tex;
			x++;
		}
		x -= width;
		y_tex += step_y_tex;
		if (w->sequential_frame == 1 && (y % 6 == 0))
			img_update(w);
		y++;
	}
	return (1);
}
