/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data13.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:59:43 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 17:18:58 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			number_of_ennemy(t_win *win)
{
	t_lstasset		*tmp;
	int				i;

	i = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int			number_of_sprite(t_win *win)
{
	t_lstasset		*tmp;
	int				i;

	i = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
