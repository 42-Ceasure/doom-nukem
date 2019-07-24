/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data8.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:53:00 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 17:20:16 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		stph2(t_env *w, t_win *win, int y, int i, int index)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;

	dot_tab = create_y_dot_tab(w, win, y, i);
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
	free_dot_tab(dot_tab);
}

void		stph(t_env *w, t_win *win, int y, int i)
{
	int		index;

	index = 0;
	i = number_of_dot_per_line_with_same(win, y);
	if (i > 0)
		stph2(w, win, y, i, index);
}

void		sort_triangles_points(t_env *w, t_win *win)
{
	int			y;
	int			i;

	i = 0;
	y = WIN_Y;
	y = y_min_point(win);
	while (y < WIN_Y)
	{
		stph(w, win, y, i);
		y++;
	}
}
