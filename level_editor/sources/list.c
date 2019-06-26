/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 10:29:41 by abechet           #+#    #+#             */
/*   Updated: 2019/06/06 10:29:57 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

t_lstlst	*lstlstnew(t_win * win)
{
	t_lstlst	*tmp;

	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		return (NULL);
	tmp->sector = win->sector;
	tmp->closed = 0;
	tmp->head = win->lst;
	tmp->next = NULL;
	win->link += 1;
	return (tmp);
}

void	sector_confirm(t_win *win)
{
	win->lst = NULL;
	win->sector += 1;
	win->drawing = 0;
	win->just_close = 1;
}

int		check_list(t_win *win, t_lst *lst, int x, int y)
{
	t_lst	*tmp;
	t_lst	*new;
	int		closed;

	tmp = lst;
	closed = 0;
	while (tmp->next)
		tmp = tmp->next;
	if (x == tmp->x && y == tmp->y)
		return (1);
	//tmp = lst;

	new = lstnew(x, y, win->sector);

	if (x == win->lst->x && y == win->lst->y && win->lst->next != NULL)
	{
		sector_confirm(win);
		closed = 1;
	}
	//tmp = lst;
	//new = lstnew(x, y, win->sector);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	if (win->just_close)
		check_neighbour(win);
	return (closed);
}

t_lst	*lstnew(int x, int y, int sector)
{
	t_lst	*tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	tmp->x = x;
	tmp->y = y;
	tmp->sector = sector;
	tmp->next = NULL;
	return (tmp);
}
