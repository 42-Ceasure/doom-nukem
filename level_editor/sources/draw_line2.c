/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:28:48 by abechet           #+#    #+#             */
/*   Updated: 2019/06/07 10:29:01 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void line(t_win *win, int x0, int y0, int x1, int y1)
{
  int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
  int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1;
  int err = (dx>dy ? dx : -dy)/2, e2;

  for(;;)
  {
    put_pixel_to_surface(win->surface, x0, y0, win->color);
    if (x0==x1 && y0==y1) break;
    e2 = err;
    if (e2 >-dx) { err -= dy; x0 += sx; }
    if (e2 < dy) { err += dx; y0 += sy; }
  }
}

double vmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
double vmax(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double vmid(double a, double min, double max)
{
	return (vmin(vmax(a, min), max));
}

int		final_texture_to_screen(SDL_Surface *surface, SDL_Surface *texture, int x, int y, int width, int height)
{
	double 	step_x_tex;
	double 	step_y_tex;
	double	x_tex;
	double	y_tex;
	int 	maxx;
	int		maxy;
	int		tmpix;

	Uint32		*pixels;
	Uint32		*pixels2;

	pixels = surface->pixels;
	pixels2 = texture->pixels;


	if (WIN_X <= 0 || WIN_Y <= 0)
		return (0);
	step_x_tex = 0;
	step_y_tex = 0;
	if (width == 0 && height == 0)
	{
		width = texture->w;
		height = texture->h;
	}
	else if (width == 0 || height == 0)
	{
		if (width == 0)
			width = (int)(height * texture->w / texture->h);
		else if (height == 0)
			height = (int)(width * texture->h / texture->w);
	}
	step_x_tex = (double)texture->w / (double)width;
	step_y_tex = (double)texture->h / (double)height;
	maxx = vmid((width + x), 0, WIN_X);
	maxy = vmid((height + y), 0, WIN_Y);
	y_tex = 0;
	x_tex = 0;
	if (step_x_tex <= 0 || step_y_tex <= 0)
		return (0);
	while (y < maxy)
	{
		x_tex = 0;
		while (x < maxx)
		{
			if (y >= 0 && y < WIN_Y && (int)y_tex >= 0 && (int)y_tex < texture->h)
			{
				if (x >= 0 && x < WIN_X && (int)x_tex >= 0 && (int)x_tex < texture->w)
				{
					// SDL_LockSurface(surface);
					tmpix = (int)y_tex * texture->w + (int)x_tex;
					if (pixels2[tmpix] != 0)
						pixels[y * WIN_X + x] = pixels2[tmpix];
					// SDL_UnlockSurface(surface);

				}
			}
			x_tex += step_x_tex;
			x++;
		}
		x -= width;
		y_tex += step_y_tex;
		y++;
	}
	return (1);
}
