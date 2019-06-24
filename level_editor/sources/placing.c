/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:48:05 by abechet           #+#    #+#             */
/*   Updated: 2019/06/20 14:48:15 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		pick_asset(t_win *win)
{
	win->asset += 1;
	if (win->asset > 4)
		win->asset = 0;
	if (win->asset == 0)
		win->asset_sprite = IMG_Load("resources/textures/feather.png");
	/*if (win->asset == 1)
		win->asset_sprite =
	if (win->asset == 2)
		win->asset_sprite =
	if (win->asset == 3)
		win->asset_sprite =
	if (win->asset == 4)
		win->asset_sprite =*/
}

void		placing(t_win *win)
{
	win->dst9.x = win->x2 - 25;
	win->dst9.y = win->y2 - 35;
}

void		mode(t_win *win)
{
	if (win->mode == 2)
	{
		placing(win);
		SDL_BlitSurface(win->asset_sprite, NULL, win->surface, &win->dst9);
	}
}
