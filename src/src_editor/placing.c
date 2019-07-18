/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:48:05 by abechet           #+#    #+#             */
/*   Updated: 2019/07/14 15:03:23 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		place_asset(t_win *win)
{
	t_lstasset	*tmp;

	if (win->lstasset == NULL)
		win->lstasset = lstassetnew(win, 0);
	else
	{
		tmp = win->lstasset;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lstassetnew(win, 0);
	}
	win->place = 0;
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

int			check_max_number_ennemy(t_win *win)
{
	t_lstasset	*tmp;
	int			ret;

	ret = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 3)
			ret++;
		tmp = tmp->next;
	}
	if (ret == 30)
		printf("Too many ennemies\n");
	return (ret);
}

int			check_max_number_sprite(t_win *win)
{
	t_lstasset	*tmp;
	int			ret;

	ret = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		ret++;
		tmp = tmp->next;
	}
	if (ret == 60)
		printf("Too many items\n");
	return (ret);
}

void		mode(t_env *w, t_win *win)
{
	int		ret;
	int		ret2;
	int		ret3;

	ret = 0;
	ret2 = 0;
	ret3 = 0;
	if (win->mode == 2)
	{
		placing(win);
		if (win->check_textures == 0)
			final_sprite_to_screen(w, win->asset_sprite,
				win->dst9.x - 10, win->dst9.y - 75, 0, 96);
		if (win->place == 1)
		{
			if (win->asset == 0)
				ret = check_first_player_start(win);
			ret2 = check_max_number_ennemy(win);
			ret3 = check_max_number_sprite(win);
			if (ret == 0 && ret2 < 30 && ret3 < 60)
				place_asset(win);
			else
				win->place = 0;
		}
	}
}
