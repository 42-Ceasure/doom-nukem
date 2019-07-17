/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:47:14 by abechet           #+#    #+#             */
/*   Updated: 2019/07/16 23:52:45 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			triangulate_a_triangle(t_win *win, t_dot m)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			ret;

	t_dot		p0;
	t_dot		p1;
	t_dot		p2;

	ret = -1;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (len_list(tmp2->head) == 4)
		{
			tmp = tmp2->head;
			p0 = get_point_in_list(tmp, 0);
			p1 = get_point_in_list(tmp, 1);
			p2 = get_point_in_list(tmp, 2);

			ret = point_in_triangle(p0, p1, p2, m);
			if (ret == 1)
				return (tmp2->sector);
		}
		tmp2 = tmp2->next;
	}
	return (ret);
}

void		triangulate_all_assets(t_win *win)
{
	t_lstasset	*tmp3;
	t_lstlst	*tmp2;
	t_lst		*tmp;

	int			ret;

	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	t_dot		m;

	ret = -1;
	tmp3 = win->lstasset;
	while (tmp3)
	{
		tmp2 = win->triangles;
		if (tmp2->sector != -1)
		{
			while (tmp2)
			{
				tmp = tmp2->head;
				p0 = get_point_in_list(tmp, 0);
				p1 = get_point_in_list(tmp, 1);
				p2 = get_point_in_list(tmp, 2);
				m.x = tmp3->x;
				m.y = tmp3->y;
				ret = triangulate_a_triangle(win, m);
				if (ret != -1)
					tmp3->sector = ret;
				ret = point_in_triangle(p0, p1, p2, m);
				if (ret == 1)
					tmp3->sector = tmp2->sector;
				//printf("%d tmp3 sector \n", tmp3->sector);
				tmp2 = tmp2->next;
			}
		}
		tmp3 = tmp3->next;
	}
}
