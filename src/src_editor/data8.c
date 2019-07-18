/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:53:00 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:53:08 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		stph2(t_win *win, int y, int i)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			index;
	int			*dot_tab;

	index = 0;
	dot_tab = create_y_dot_tab(win, y, i);
	while (index < i)
	{
		tmp2 = win->triangles;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y && tmp->x == dot_tab[index])
					tmp->nb = win->number;
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		index++;
		if (dot_tab[index] != dot_tab[index - 1])
			win->number++;
	}
}

void		stph(t_win *win, int y, int i)
{
	i = number_of_dot_per_line_with_same(win, y);
	if (i > 0)
		stph2(win, y, i);
}

void		sort_triangles_points(t_win *win)
{
	int			y;
	int			i;

	i = 0;
	y = WIN_Y;
	y = y_min_point(win);
	while (y < WIN_Y)
	{
		stph(win, y, i);
		y++;
	}
}
