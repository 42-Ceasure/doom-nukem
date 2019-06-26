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
	if (win->asset == 1)
		win->asset_sprite = IMG_Load("resources/textures/gun1.png");
	if (win->asset == 2)
		win->asset_sprite = IMG_Load("resources/textures/shotgun.png");
	if (win->asset == 3)
		win->asset_sprite = IMG_Load("resources/textures/ennemy.png");
	if (win->asset == 4)
		win->asset_sprite = IMG_Load("resources/textures/lamp.png");
}

void		placing(t_win *win)
{
	if (win->asset == 0)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 1)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 2)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 3)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 4)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
}

t_lstasset	*lstassetnew(t_win *win, int sector)
{
	t_lstasset	*tmp;

	if (!(tmp = (t_lstasset *)malloc(sizeof(t_lstasset))))
		return (NULL);
	tmp->x = win->x2;
	tmp->y = win->y2;
	tmp->sector = sector;
	tmp->asset_type = win->asset;
	tmp->next = NULL;
	return (tmp);
}

void		place_asset(t_win *win)
{
	t_lstasset	*tmp;

	if (win->lstasset == NULL)
	{
		win->lstasset = lstassetnew(win, 0); // faux il faudra recuperer le
		//sector avec triangulate
	}
	else
	{
		tmp = win->lstasset;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lstassetnew(win, 0); // same here
	}
	win->place = 0;
}

void		asset_overing(t_win *win)
{
	t_lstasset	*tmp;

	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->x == win->x2 && tmp->y == win->y2)
		{
			if (tmp->asset_type == 0)
				win->asset_tmp = IMG_Load("resources/textures/feather.png");
			if (tmp->asset_type == 1)
				win->asset_tmp = IMG_Load("resources/textures/gun1.png");
			if (tmp->asset_type == 2)
				win->asset_tmp = IMG_Load("resources/textures/shotgun.png");
			if (tmp->asset_type == 3)
				win->asset_tmp = IMG_Load("resources/textures/ennemy.png");
			if (tmp->asset_type == 4)
				win->asset_tmp = IMG_Load("resources/textures/lamp.png");

			final_texture_to_screen(win->surface, win->asset_tmp, tmp->x - 25, tmp->y - 75, 64, 64);
			//SDL_BlitSurface(win->asset_sprite, NULL, win->surface, &win->dst9);
		}
		tmp = tmp->next;
	}
}




void		mode(t_win *win)
{
	if (win->mode == 2)
	{
		placing(win);
		final_texture_to_screen(win->surface, win->asset_sprite, win->dst9.x - 10, win->dst9.y - 75, 96, 96);
		//SDL_BlitSurface(win->asset_sprite, NULL, win->surface, &win->dst9);
		if (win->place == 1)
			place_asset(win);
	}
}
