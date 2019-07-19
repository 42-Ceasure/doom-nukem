/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screen_resized.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 18:15:26 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/02 17:42:14 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	get_scalling(t_img *img, t_texture texture)
{
	if (img->w == 0 && img->w == 0)
	{
		img->w = texture.w;
		img->w = texture.h;
	}
	else if (img->w == 0 || img->w == 0)
	{
		if (img->w == 0)
			img->w = (int)(img->w * texture.w / texture.h);
		else if (img->w == 0)
			img->w = (int)(img->w * texture.h / texture.w);
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
	double 			step_x_tex;
	double 			step_y_tex;
	double			x_tex;
	double			y_tex;
	int 			maxx;
	int				maxy;
	int 			x_tmp;
	unsigned int	tmpix;

	x_tex = 0;
	y_tex = 0;
	if (texture.pix == NULL || w->pix == NULL || texture.h <= 0 || texture.w <= 0 || texture.len <= 0)
		return (0);
	get_scalling(&img, texture);
	step_x_tex = (double)texture.w / (double)img.w;
	step_y_tex = (double)texture.h / (double)img.h;
	maxx = img.w + img.x;
	maxy = img.h + img.y;
	x_tmp = img.x;

	if (maxx > WIDTH)
		maxx = WIDTH;
	if (maxy > HEIGHT)
		maxy = HEIGHT;
	if (maxx < 0 || maxy < 0)
		return(0);
	if (img.x > WIDTH || img.y > HEIGHT)
		return(0);
	if (img.x < 0)
		x_tex = (0 - img.x) * step_x_tex;
	if (img.y < 0)
	{
		y_tex = (0 - img.y) * step_y_tex;
		img.y = 0;
	}
	while (img.y < maxy && (int)x_tex * (int)y_tex < texture.len)
	{
		x_tex = 0;
		while (img.x < maxx && (int)x_tex * (int)y_tex < texture.len)
		{
			if (img.y >= 0 && img.y < HEIGHT && (int)y_tex >= 0 && (int)y_tex < texture.h)
			{
				if (img.x >= 0 && img.x < WIDTH && (int)x_tex >= 0 && (int)x_tex < texture.w)
				{
					tmpix = (int)y_tex * texture.w + (int)x_tex;
					if (texture.pix[tmpix] != 0xFF00FF00)
						w->pix[img.y * WIDTH + img.x] = texture.pix[tmpix];
				}
			}
			x_tex += step_x_tex;
			img.x++;
		}
		img.x = x_tmp;
		y_tex += step_y_tex;
		if (w->sequential_frame == 1 && (img.y % 2 == 0))
			img_update(w);
		img.y++;
	}
	return (1);
}

int		final_texture_to_screen(t_env *w, t_texture texture, int x, int y, int width, int height)
{
	double 	step_x_tex;
	double 	step_y_tex;
	double	x_tex;
	double	y_tex;
	int 	maxx;
	int		maxy;
	int 	x_tmp;
	unsigned int	tmpix;

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
	//testing
	x_tmp = x;
	if (maxx > WIDTH)
		maxx = WIDTH;
	if (maxy > HEIGHT)
		maxy = HEIGHT;
	if (maxx < 0 || maxy < 0)
		return(0);
	if (x > WIDTH || y > HEIGHT)
		return(0);
	if (x < 0)
		x_tex = (0 - x) * step_x_tex;
	// {
		// x = 0;
	// }
	if (y < 0)
	{
		y_tex = (0 - y) * step_y_tex;
		y = 0;
	}
	//end testing
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
		x = x_tmp;
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
	int 	x_tmp;
	unsigned int	tmpix;

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
	//testing
	if (maxx > WIDTH)
		maxx = WIDTH;
	if (maxy > HEIGHT)
		maxy = HEIGHT;
	if (maxx < 0 || maxy < 0)
		return(0);
	if (x > WIDTH || y > HEIGHT)
		return(0);
	x_tmp = x;
	if (x < 0)
		x_tex = (0 - x) * step_x_tex;
	if (y < 0)
	{
		y_tex = (0 - y) * step_y_tex;
		y = 0;
	}
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
		x = x_tmp;
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
	int 	x_tmp;
	unsigned int	tmpix;

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
	//testing
	x_tmp = x;
	if (maxx > WIDTH)
		maxx = WIDTH;
	if (maxy > HEIGHT)
		maxy = HEIGHT;
	if (maxx < 0 || maxy < 0)
		return(0);
	if (x > WIDTH || y > HEIGHT)
		return(0);
	if (x < 0)
		x_tex = (0 - x) * step_x_tex;
	// {
		// x = 0;
	// }
	if (y < 0)
	{
		y_tex = (0 - y) * step_y_tex;
		y = 0;
	}
	//end testing
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
		x = x_tmp;
		y_tex += step_y_tex;
		if (w->sequential_frame == 1 && (y % 6 == 0))
			img_update(w);
		y++;
	}
	return (1);
}

int		get_tmpix_scaled(t_sprite sprite, int width, int height, int x, int y)
{
	double 	step_x_tex;
	double 	step_y_tex;

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
	return ((int)(step_x_tex * x) + ((int)(step_y_tex * y) * sprite.w));
}
