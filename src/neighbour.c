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

#include "doom.h"

int		ret_neighbour_sector(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (tmp->sector);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (tmp->sector);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (-1);
}

int		check_segment(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (1);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (1);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int		which_sector_neighbour(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (tmp->sector);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (tmp->sector);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (-1);
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
	return (neighbour);
}

int		number_of_neighbours_in_sector(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			ret;
	int			neighbour;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			headx;
	int			heady;

	neighbour = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			if (tmp)
			{
				headx = tmp->x;
				heady = tmp->y;
			}
			while (tmp)
			{
				ret = 0;
				x1 = tmp->x;
				y1 = tmp->y;
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
		}
		tmp2 = tmp2->next;
	}
	return (neighbour);
}

int		*get_neighbours(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			index;
	int			ret;
	int			*neighbour_tab;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			headx;
	int			heady;

	index = 0;
	neighbour_tab = NULL;
	i = number_of_neighbours_in_sector(win, sector);
	if (i == 0)
		return (neighbour_tab);
	if (!(neighbour_tab = (int *)malloc(sizeof(int) * i)))
		clear_n_exit(win, 1);
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			if (tmp)
			{
				headx = tmp->x;
				heady = tmp->y;
			}
			while (tmp)
			{
				x1 = tmp->x;
				y1 = tmp->y;
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
				ret = ret_neighbour_sector(win, x1, y1, x2, y2, sector);
				if (ret != -1)
				{
					neighbour_tab[index] = ret;
					index++;
				}
				tmp = tmp->next;
			}
		}
		tmp2 = tmp2->next;
	}
	return (neighbour_tab);
}
