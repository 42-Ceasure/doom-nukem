/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   undo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/14 10:36:07 by abechet           #+#    #+#             */
/*   Updated: 2019/06/14 10:36:23 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	undo_helper(t_win *win, t_lstlst *previous2)
{
	if (previous2->next == NULL)
	{
		win->sector = 0;
		win->link = 0;
		win->lstlst = NULL;
	}
	if (previous2->next)
	{
		while (previous2->next->next)
			previous2 = previous2->next;
		previous2->next = NULL;
		win->link -= 1;
		win->drawing = 0;
	}
}

void	undo_first_link(t_win *win, t_lst *tmp,
			t_lstlst *tmp2, t_lstlst *previous2)
{
	if (tmp)
	{
		if (tmp->next == NULL)
		{
			win->x1 = tmp->x;
			win->y1 = tmp->y;
			free(tmp);
			tmp = NULL;
			win->lst = NULL;
			undo_helper(win, previous2);
			tmp2->head = NULL;
			free(tmp2);
			tmp2 = NULL;
		}
	}
}

void	undo_classic(t_win *win, t_lst *tmp, t_lst *previous)
{
	if (tmp->next->next == NULL)
	{
		win->x1 = tmp->x;
		win->y1 = tmp->y;
	}
	while (previous->next->next)
	{
		previous = previous->next;
		win->x1 = previous->x;
		win->y1 = previous->y;
	}
	while (tmp->next)
		tmp = tmp->next;
	previous->next = NULL;
	free(tmp);
	tmp = NULL;
}

void	undo(t_win *win)
{
	t_lst		*tmp;
	t_lst		*previous;
	t_lstlst	*tmp2;
	t_lstlst	*previous2;

	tmp = NULL;
	if (win->lstlst)
	{
		tmp2 = win->lstlst;
		previous2 = win->lstlst;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp = tmp2->head;
		previous = tmp2->head;
	}
	if (tmp)
	{
		if (win->sector == tmp->sector)
		{
			if (tmp->next == NULL)
				undo_first_link(win, tmp, tmp2, previous2);
			else
				undo_classic(win, tmp, previous);
		}
	}
}
