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

void	delete_sector2(t_win *win, t_lstlst *current, t_lstlst *previous)
{
	t_lst		*tmp;

	tmp = NULL;
	if (win->lstlst)
	{
		free(current);
		current = NULL;
		win->link -= 1;
		if (previous)
			previous->next = NULL;
		if (previous == NULL)
		{
			win->lstlst = NULL;
			win->lst = NULL;
			win->tmp = NULL;
			win->sector = 0;
			win->link = 0;
		}
		else
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
			tmp2->head = NULL;
			delete_sector2(win, tmp2, previous2);
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
		while (previous2)
		{
			if (previous2->sector == tmp2->sector - 1)
				break ;
			previous2 = previous2->next;
		}
	}
	if (tmp)
	{
		if (win->sector == tmp->sector && !tmp2->closed)
		{
			if (tmp->next == NULL)
				undo_first_link(win, tmp, tmp2, previous2);
			else
				undo_classic(win, tmp, previous);
		}
	}
}
