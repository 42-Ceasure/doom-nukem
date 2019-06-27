/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_mode.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 11:36:02 by abechet           #+#    #+#             */
/*   Updated: 2019/06/17 11:36:13 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	overing(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	if (win->lstlst)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->x == win->x2 && tmp->y == win->y2 && tmp2->closed == 1)
					win->overed_sector = tmp2->sector;
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		//printf("%d \n", win->overed_sector);
	}
}

void	free_list(t_lst *lst)
{
	t_lst	*tmp;
	t_lst	*current;

	tmp = lst;
	current = lst;
	while (current)
	{
		current = current->next;
		free(tmp);
		tmp = NULL;
		tmp = current;
	}
}

void	delete_sector(t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*current;
	t_lstlst	*previous;
	t_lstlst	*next;

	tmp = NULL;
	current = NULL;
	previous = NULL;
	next = NULL;
	if (win->lstlst && win->overed_sector != -1)
	{
		current = win->lstlst;
		while (current->sector != win->overed_sector)
			current = current->next;
		next = current->next;
		if (win->overed_sector > 0)
		{
			previous = win->lstlst;
			while (previous->sector < win->overed_sector - 1)
				previous = previous->next;
		}
		tmp = current->head;
		if (tmp)
			free_list(tmp);
		current->head = NULL;
		free(current);
		current = NULL;
		if (previous)
			previous->next = next;
		if (previous == NULL && next == NULL)
		{
			win->lstlst = NULL;
			win->lst = NULL;
			win->tmp = NULL;
			win->sector = 0;
			win->link = 0;
		}
		if (previous == NULL && next != NULL)
			win->lstlst = next;
		while (next)
		{
			next->sector -= 1;
			next = next->next;
		}
		win->overed_sector = -1;
	}
}
