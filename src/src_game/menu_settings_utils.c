/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_settings_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 19:44:59 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/23 20:28:12 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	change_value_settings_nxt(t_env *w, int direction)
{
	if (w->menu.k == 3)
	{
		if (direction == 1)
			w->fov_v_menu = vmin(w->fov_v_menu + 1, 500);
		else
			w->fov_v_menu = vmax(100, w->fov_v_menu - 1);
	}
	else if (w->menu.k == 4)
	{
		if (direction == 1)
			w->mousesp_menu = vmin(w->mousesp_menu + 1, 200);
		else
			w->mousesp_menu = vmax(1, w->mousesp_menu - 1);
	}
}

void	change_value_settings(t_env *w, int direction)
{
	if (w->menu.k == 0)
	{
		if (direction == 1)
			w->window_mode_menu = vmin(w->window_mode_menu + 1, 1);
		else
			w->window_mode_menu = vmax(0, w->window_mode_menu - 1);
	}
	else if (w->menu.k == 1)
	{
		if (direction == 1)
			w->window_res_menu = vmin(w->window_res_menu + 1, 2);
		else
			w->window_res_menu = vmax(0, w->window_res_menu - 1);
	}
	else if (w->menu.k == 2)
	{
		if (direction == 1)
			w->fov_h_menu = vmin(w->fov_h_menu + 1, 700);
		else
			w->fov_h_menu = vmax(300, w->fov_h_menu - 1);
	}
	else if (w->menu.k >= 3)
		change_value_settings_nxt(w, direction);
}

int		settings_changed(t_env *w)
{
	if (w->menu.k == 5)
	{
		if (w->window_mode != 1 || w->window_res != 0)
			return (1);
		if (w->m->player.field_of_vision_h != 512)
			return (1);
		if (w->m->player.field_of_vision_v != 288)
			return (1);
		if (w->m->player.mousesp != 100)
			return (1);
	}
	else
	{
		if (w->window_mode != w->window_mode_menu || w->window_res_menu)
			return (1);
		if (w->m->player.field_of_vision_h != w->fov_h_menu)
			return (1);
		if (w->m->player.field_of_vision_v != w->fov_v_menu)
			return (1);
		if (w->m->player.mousesp != w->mousesp_menu)
			return (1);
	}
	return (0);
}
