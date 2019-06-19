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

/*int		len_list(t_lstlst *lstlst)
{
	int		i;
	t_lstlst *tmp2;

	i = 0;
	tmp2 = lstlst;
	while (tmp2)
	{
		i++;
		tmp2 = tmp2->next;
	}
	return (i);
}

int		len_list(t_lstlst *lstlst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lstlst->head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		check_segment(t_win *win, int x1, int y1, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			//printf("%d sector \n", sector);
			//printf("%d tmp sector \n", tmp->sector);
			if (x1 == tmp->x && y1 == tmp->y && sector != tmp->sector)
				return (1);
			if (x1 == tmp->y && y1 == tmp->x && sector != tmp->sector)
				return (1);
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
	int			sector;
	int			ret;
	int			neighbour;

	int			i;

	neighbour = 0;
	if (win->lstlst == NULL)
		return (-1);
	tmp2 = win->lstlst;
	while (tmp2)
	{
		i = len_list(tmp2);
		printf("%d len \n", i);
		tmp = tmp2->head;
		while (tmp)
		{
			x1 = tmp->x;
			y1 = tmp->y;
			sector = tmp->sector;
			ret = check_segment(win, x1, y1, sector);
			if (ret == 1)
				neighbour += 1;
			ret = 0;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	//printf("%d neighbour \n", neighbour);
	return (neighbour);
}*/
