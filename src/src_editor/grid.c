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

#include "doom.h"

void	draw_grid(t_env *w, t_win *win)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	(void)win;
	i = 0;
	j = 0;
	x = 0;
	y = 0;
	color = 255255255;
	while (j < WIN_Y * 10)
	{
		i = 0;
		x = 0;
		while (i < WIN_X * 10)
		{
			set_txtr_pix(w, i, j, color);
			i += 10;
			x++;
		}
		j += 10;
		y++;
	}
}
