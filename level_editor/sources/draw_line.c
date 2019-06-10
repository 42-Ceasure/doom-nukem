/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:35:36 by abechet           #+#    #+#             */
/*   Updated: 2019/06/05 16:35:54 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	ft_draw_line_2_1(t_win *win, int x1, int y1, int x2, int y2)
{
	int y;

	if (y1 <= y2 && (y2 - y1)
		>= abs(x2 - x1))
	{
		y = y1;
		while (y <= y2 && (y2 - y1) != 0)
		{
			put_pixel_to_surface(win->surface, x1 + ((x2 - x1)
				* (y - y1)) / (y2 - y1), y, 255255255);
			y++;
		}
	}
}

static void	ft_draw_line_2(t_win *win, int x1, int y1, int x2, int y2)
{
	int y;

	if (y2 <= y1 && (y1 - y2)
		>= abs(x1 - x2))
	{
		y = y2;
		while (y <= y1 && (y1 - y2) != 0)
		{
			put_pixel_to_surface(win->surface, x2 + ((x1 - x2)
				* (y - y2)) / (y1 - y2), y , 255255255);
			y++;
		}
	}
	ft_draw_line_2_1(win, win->x1, win->y1, win->x2, win->y2);
}

static void	ft_draw_line_1_1(t_win *win, int x1, int y1, int x2, int y2)
{
	int x;

	if (x2 <= x1 && (x1 - x2) >= abs(y1 - y2))
	{
		x = x2;
		while (x < x1 && (x1 - x2) != 0)
		{
			if ((x1 - x2) > 0)
				put_pixel_to_surface(win->surface, x, y2 + ((y1 - y2) * (x - x2)) / (x1 - x2), 255255255);
			x++;
		}
	}
	ft_draw_line_2(win, win->x1, win->y1, win->x2, win->y2);
}

void		ft_draw_line(t_win *win, int x1, int y1, int x2, int y2)
{
	int x;

	if (x1 <= x2 && (x2 - x1) >= abs(y2 - y1))
	{
		x = x1;
		while (x <= x2 && (x2 - x1) != 0)
		{
			put_pixel_to_surface(win->surface, x, y1 + ((y2 - y1) * (x - x1)) / (x2 - x1), 255255255);
			x++;
		}
	}
	ft_draw_line_1_1(win, win->x1, win->y1, win->x2, win->y2);
}
