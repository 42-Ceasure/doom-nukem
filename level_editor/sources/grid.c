/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:50:55 by abechet           #+#    #+#             */
/*   Updated: 2019/06/05 10:51:08 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	put_pixel_to_surface(SDL_Surface *srfc, int x, int y, Uint32 color)
{
	Uint32		*pixels;

	pixels = srfc->pixels;
	if (x >= 0 && y >= 0 && x < srfc->w && y < srfc->h)
		pixels[y * srfc->w + x] = color;
}

void	init_grid(t_win *win)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < win->map_height)
	{
		x = 0;
		while (x < win->map_width)
		{
			win->map[y][x] = 0;
			x++;
		}
		y++;
	}
}

void	draw_grid(t_win *win)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	i = 0;
	j = 0;
	x = 0;
	y = 0;
	color = 255255255;
	while (j < win->map_height * 10)
	{
		i = 0;
		x = 0;
		while (i < win->map_width * 10)
		{
			if (win->map[y][x] == 1)
				color = 055;
			else
				color = 255255255;
			put_pixel_to_surface(win->surface, i, j, color);
			i += 10;
			x++;
		}
		j += 10;
		y++;
	}
}
