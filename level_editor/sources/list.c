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

int		check_list(t_win *win, t_lst *lst, int x, int y, int sector)
{
	t_lst	*tmp;
	t_lst	*new;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	if (x == tmp->x && y == tmp->y)
		return (1);
	tmp = lst;
	if (x == win->lst->x && y == win->lst->y && win->lst->next != NULL)
	{
		printf("close right\n");
		win->drawing = 0;
	}
	new = lstnew(x, y, sector);
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (0);
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
