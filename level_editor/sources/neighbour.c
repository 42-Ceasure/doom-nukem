/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:09:03 by abechet           #+#    #+#             */
/*   Updated: 2019/06/18 10:09:17 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		len_listlist(t_lstlst *lstlst)
{
	int		i;
	t_lstlst *tmp2;

	i = 0;
	tmp2 = lstlst;
	while (tmp2)
	{
		//printf("%d tmp2 sector \n", tmp2->sector);
		i++;
		tmp2 = tmp2->next;
	}
	return (i);
}

int		check_segment(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			headx;
	int			heady;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp)
		{
			headx = tmp->x;
			heady = tmp->y;
		}
		while (tmp)
		{
			//printf("%d sector \n", sector);
			//printf("%d tmp sector \n", tmp->sector);

			if (tmp->next)
			{

				if ((x1 == tmp->x && y1 == tmp->y) && (x2 == tmp->next->x && y2 == tmp->next->y) && sector != tmp->sector)
					return (1);
				if ((y1 == tmp->next->y && x1 == tmp->next->x) && (y2 == tmp->y && x2 == tmp->x) && sector != tmp->sector)
					return (1);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int		check_neighbour(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			sector;
	int			ret;
	int			neighbour;

	int			headx;
	int			heady;

	int			i;

	neighbour = 0;
	if (win->lstlst == NULL)
		return (-1);
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp)
		{
			headx = tmp->x;
			heady = tmp->y;
		}
		i = len_list(tmp);

		while (tmp)
		{
			ret = 0;
			x1 = tmp->x;
			y1 = tmp->y;
			sector = tmp->sector;
			if (tmp->next)
			{
				x2 = tmp->next->x;
				y2 = tmp->next->y;
			}
			else
			{
				x2 = headx;
				y2 = heady;
			}
			ret = check_segment(win, x1, y1, x2, y2, sector);
			if (ret == 1)
				neighbour += 1;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	//printf("%d neighbours \n", neighbour);
	return (neighbour);
}
