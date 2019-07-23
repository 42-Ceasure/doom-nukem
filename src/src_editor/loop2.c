/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:09:20 by abechet           #+#    #+#             */
/*   Updated: 2019/07/23 13:09:33 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		och4(t_win *win, t_lst *tmp, t_lstlst *tmp2)
{
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp && win->moving == 0)
		{
			if (tmp->x == win->x0 && tmp->y == win->y0)
			{
				win->tmp = tmp;
				win->moving = 1;
			}
			else
				tmp = tmp->next;
		}
		if (win->moving == 1)
		{
			win->tmp->x = win->x2;
			win->tmp->y = win->y2;
			if (tmp2->closed == 1)
				last_is_first(tmp2->head);
		}
		tmp2 = tmp2->next;
	}
}

void		och3(t_win *win, t_lst *tmp, t_lstlst *tmp2, t_lstasset *tmp3)
{
	if (win->left_click == 1 && win->mode == 1)
	{
		tmp2 = win->lstlst;
		tmp3 = win->lstasset;
		och4(win, tmp, tmp2);
		while (tmp3 && win->moving == 0)
		{
			if (tmp3->x == win->x0 && tmp3->y == win->y0)
			{
				win->tmpasset = tmp3;
				win->moving = 2;
			}
			else
				tmp3 = tmp3->next;
		}
		if (win->moving == 2)
		{
			if (win->tmpasset)
			{
				win->tmpasset->x = win->x2;
				win->tmpasset->y = win->y2;
			}
		}
	}
}

void		och2(t_win *win, t_lstlst *tmp2)
{
	if (win->sector == win->link)
	{
		tmp2 = win->lstlst;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = lstlstnew(win);
	}
}

void		och(t_win *win, t_lstlst *tmp2, int closed)
{
	if (win->left_click && win->mode == 0)
	{
		if (win->lstlst == NULL)
			win->lstlst = lstlstnew(win);
		och2(win, tmp2);
		win->drawing = 1;
		if (win->lst == NULL)
		{
			win->lst = lstnew(win->x1, win->y1, win->sector);
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->head = win->lst;
		}
		else
			closed = check_list(win, win->lst, win->x1, win->y1);
		if (closed)
		{
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->closed = 1;
		}
	}
}

void		on_click(t_win *win)
{
	int			closed;
	t_lst		*tmp;
	t_lstlst	*tmp2;
	t_lstasset	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	closed = 0;
	if (win->left_click)
	{
		win->changemode = 0;
		if (win->triangles)
			free_triangles(win);
	}
	if (win->mode == 3)
		overing(win);
	if (win->left_click && win->mode == 3)
	{
		delete_sector(win);
		delete_asset(win);
	}
	och(win, tmp2, closed);
	och3(win, tmp, tmp2, tmp3);
	och5(win);
}
