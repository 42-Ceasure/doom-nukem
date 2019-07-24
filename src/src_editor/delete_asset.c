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

#include "doom.h"

void	delete_asset_helper2(t_win *win, t_lstasset *current,
			t_lstasset *next, t_lstasset *previous)
{
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
}

void	delete_asset_helper(t_win *win, t_lstasset *tmp, int j, int i)
{
	t_lstasset	*current;
	t_lstasset	*previous;
	t_lstasset	*next;

	current = NULL;
	previous = NULL;
	next = NULL;
	win->tmpasset = NULL;
	current = tmp;
	next = current->next;
	if (j > 0)
	{
		previous = win->lstasset;
		while (i < j - 1)
		{
			previous = previous->next;
			i++;
		}
	}
	if (j == 0)
		win->lstasset = NULL;
	delete_asset_helper2(win, current, next, previous);
	tmp = NULL;
}

void	delete_asset(t_win *win)
{
	t_lstasset	*tmp;
	int			i;
	int			j;

	tmp = NULL;
	i = 0;
	j = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->x == win->x2 && tmp->y == win->y2)
			delete_asset_helper(win, tmp, j, i);
		if (tmp)
		{
			tmp = tmp->next;
			j++;
		}
	}
}
