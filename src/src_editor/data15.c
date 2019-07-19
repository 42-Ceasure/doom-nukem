/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data15.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:03:53 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 14:04:04 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*int			triangles_neighbours_helper(t_win *win, t_lstlst *tmp2, int i)
{
	if (i == 0)
	{
		if (tab_sector1[0] == tab_sector2[0] || tab_sector1[0]
			== tab_sector2[1] || tab_sector1[0] == tab_sector2[2])
			index++;
		if (tab_sector1[1] == tab_sector2[0] || tab_sector1[1]
			== tab_sector2[1] || tab_sector1[1] == tab_sector2[2])
			index++;
	}
	if (i == 1)
	{
		if (tab_sector1[1] == tab_sector2[0] || tab_sector1[1]
			== tab_sector2[1] || tab_sector1[1] == tab_sector2[2])
			index++;
		if (tab_sector1[2] == tab_sector2[0] || tab_sector1[2]
			== tab_sector2[1] || tab_sector1[2] == tab_sector2[2])
			index++;
	}
	if (i == 2)
	{
		if (tab_sector1[2] == tab_sector2[0] || tab_sector1[2]
			== tab_sector2[1] || tab_sector1[2] == tab_sector2[2])
			index++;
		if (tab_sector1[0] == tab_sector2[0] || tab_sector1[0]
			== tab_sector2[1] || tab_sector1[0] == tab_sector2[2])
			index++;
	}
}*/

int			triangles_neighbours(t_win *win, t_lstlst *tmp2, int i)
{
	t_lstlst	*tmp3;
	int			*tab_sector1;
	int			*tab_sector2;
	int			index;
	int			swap;

	tab_sector1 = tab_sector3(win, tmp2->sector);
	if (tmp2->clockwise == 2)
	{
		swap = tab_sector1[1];
		tab_sector1[1] = tab_sector1[2];
		tab_sector1[2] = swap;
	}
	tmp3 = win->triangles;
	while (tmp3)
	{
		index = 0;
		if (tmp3->sector != -1 && tmp3->sector != tmp2->sector)
		{
			tab_sector2 = tab_sector3(win, tmp3->sector);
			if (tmp3->clockwise == 2)
			{
				swap = tab_sector2[1];
				tab_sector2[1] = tab_sector2[2];
				tab_sector2[2] = swap;
			}
			if (i == 0)
			{
				if (tab_sector1[0] == tab_sector2[0] || tab_sector1[0]
					== tab_sector2[1] || tab_sector1[0] == tab_sector2[2])
					index++;
				if (tab_sector1[1] == tab_sector2[0] || tab_sector1[1]
					== tab_sector2[1] || tab_sector1[1] == tab_sector2[2])
					index++;
			}
			if (i == 1)
			{
				if (tab_sector1[1] == tab_sector2[0] || tab_sector1[1]
					== tab_sector2[1] || tab_sector1[1] == tab_sector2[2])
					index++;
				if (tab_sector1[2] == tab_sector2[0] || tab_sector1[2]
					== tab_sector2[1] || tab_sector1[2] == tab_sector2[2])
					index++;
			}
			if (i == 2)
			{
				if (tab_sector1[2] == tab_sector2[0] || tab_sector1[2]
					== tab_sector2[1] || tab_sector1[2] == tab_sector2[2])
					index++;
				if (tab_sector1[0] == tab_sector2[0] || tab_sector1[0]
					== tab_sector2[1] || tab_sector1[0] == tab_sector2[2])
					index++;
			}
			if (index == 2)
				return (tmp3->sector);
		}
		tmp3 = tmp3->next;
	}
	return (-1);
}

void		check4(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->triangles;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp->nb != tmp->next->nb && tmp->next->nb != tmp->next->next->nb
			&& tmp->next->next->nb != tmp->nb)
		{
			tmp2->sector = win->triangle_sector;
			win->triangle_sector += 1;
		}
		else
			tmp2->sector = -1;
		while (tmp)
		{
			tmp->sector = tmp2->sector;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
}
