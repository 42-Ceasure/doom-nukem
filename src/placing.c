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

#include "doom.h"

void		pick_asset(t_env *w, t_win *win)
{
	win->asset += 1;
	if (win->asset > 8)
		win->asset = 0;
	if (win->asset == 0)
		win->asset_sprite = w->m->fire;
	if (win->asset == 1)
		win->asset_sprite = w->m->fire;
	if (win->asset == 2)
		win->asset_sprite = w->m->fire;
	if (win->asset == 3)
		win->asset_sprite = w->m->fire;
	if (win->asset == 4)
		win->asset_sprite = w->m->fire;
	if (win->asset == 5)
		win->asset_sprite = w->m->fire;
	if (win->asset == 6)
		win->asset_sprite = w->m->fire;
	if (win->asset == 7)
		win->asset_sprite = w->m->fire;
	if (win->asset == 8)
		win->asset_sprite = w->m->fire;
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
	if (win->asset == 5)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 6)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 7)
	{
		win->dst9.x = win->x2 - 25;
		win->dst9.y = win->y2 - 35;
	}
	if (win->asset == 8)
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
		win->lstasset = lstassetnew(win, 0);
	}
	else
	{
		tmp = win->lstasset;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lstassetnew(win, 0);
	}
	win->place = 0;
}

void		asset_overing(t_env *w, t_win *win)
{
	t_lstasset	*tmp;

	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->x == win->x2 && tmp->y == win->y2)
		{
			if (tmp->asset_type == 0)
			{
				win->asset_tmp = w->m->fire;
				set_params(win);
			}
			if (tmp->asset_type == 1)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 2)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 3)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 4)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 5)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 6)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 7)
				win->asset_tmp = w->m->fire;
			if (tmp->asset_type == 8)
				win->asset_tmp = w->m->fire;

			final_texture_to_screen(w, win->asset_tmp, tmp->x - 25, tmp->y - 75, 64, 64);
		}
		tmp = tmp->next;
	}
}

int			check_first_player_start(t_win *win)
{
	t_lstasset	*tmp;
	int			ret;

	ret = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			ret = -1;
		tmp = tmp->next;
	}
	return (ret);
}

void		mode(t_env *w, t_win *win)
{
	int		ret;

	ret = 0;
	if (win->mode == 2)
	{
		placing(win);
		if (win->check_textures == 0)
			final_texture_to_screen(w, win->asset_sprite, win->dst9.x - 10, win->dst9.y - 75, 96, 96);
		if (win->place == 1)
		{
			if (win->asset == 0)
				ret = check_first_player_start(win);
			if (ret == 0)
				place_asset(win);
			else
				win->place = 0;
		}
	}
	if (win->mode == 4)
		texture_mode(w, win);
}
