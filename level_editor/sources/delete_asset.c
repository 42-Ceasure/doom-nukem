/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_asset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 09:10:03 by abechet           #+#    #+#             */
/*   Updated: 2019/06/25 09:10:17 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	delete_asset(t_win *win)
{
	t_lstasset	*tmp;
	t_lstasset	*current;
	t_lstasset	*previous;
	t_lstasset	*next;

	tmp = NULL;
	current = NULL;
	previous = NULL;
	next = NULL;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->x == win->x2 && tmp->y == win->y2)
		{
			win->tmpasset = NULL;
			current = tmp;
			next = current->next;
			if (win->lstasset->next && current->x != win->lstasset->x && current->y != win->lstasset->y)
			{
				previous = win->lstasset;
				if (previous->next)
				{
					while (previous->next->x != current->x || previous->next->y != current->y)
						previous = previous->next;
				}
			}
			if (win->lstasset->x == current->x && win->lstasset->y == current->y)
					win->lstasset = NULL;
			if (previous)
				previous->next = next;
			free(current);
			current = NULL;
			if (previous == NULL && next == NULL)
				win->lstasset = NULL;
			if (win->lstasset == NULL)
			{
				if (previous == NULL && next != NULL)
					win->lstasset = next;
			}
			tmp = NULL;
		}
		if (tmp)
			tmp = tmp->next;
	}
}
