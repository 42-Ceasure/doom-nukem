/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:24:13 by abechet           #+#    #+#             */
/*   Updated: 2019/07/22 17:03:42 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_lstlst	*fill_link(t_env *w, t_win *win,
	t_lstlst *tmp3, t_point point)
{
	t_lstlst	*tmp;
	t_lst		*l0;
	t_lst		*l1;
	t_lst		*l2;

	l0 = polylstnew(w, win, point.p0);
	l1 = polylstnew(w, win, point.p1);
	l2 = polylstnew(w, win, point.p2);
	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		clear_n_exit(w, win);
	tmp->head = l0;
	tmp->head->next = l1;
	tmp->head->next->next = l2;
	tmp->head->next->next->next = NULL;
	tmp->next = NULL;
	tmp->txtr_wall = tmp3->txtr_wall;
	tmp->txtr_ceiling = tmp3->txtr_ceiling;
	tmp->txtr_floor = tmp3->txtr_floor;
	tmp->txtr_lower_extrude = tmp3->txtr_lower_extrude;
	tmp->txtr_higher_extrude = tmp3->txtr_higher_extrude;
	return (tmp);
}

t_lstlst	*stock_last_triangle(t_env *w, t_win *win,
	t_lstlst *triangle, t_lstlst *tmp3, t_point p)
{
	t_lstlst	*tmp2;

	tmp2 = NULL;
	if (triangle == NULL)
		triangle = fill_link(w, win, tmp3, p);
	else
	{
		tmp2 = triangle;
		while (tmp2->next)
			tmp2 = tmp2->next;
		tmp2->next = fill_link(w, win, tmp3, p);
	}
	return (triangle);
}

t_count		init_cpt(t_count cpt, t_lst *polygone)
{
	cpt.n = len_list(polygone);
	cpt.j0 = left_vertex(polygone, cpt.n);
	cpt.j1 = near_vertex(cpt.n, cpt.j0, 1);
	cpt.j2 = near_vertex(cpt.n, cpt.j0, -1);
	return (cpt);
}

t_lstlst	*recursive_triangulate(t_env *w, t_win *win,
	t_lstlst *tmp3, t_lst *polygone)
{
	int			*tab;
	t_point		p;
	t_count		cpt;
	t_lst		*polygone1;

	cpt.i = 0;
	cpt = init_cpt(cpt, polygone);
	tab = indice(w, win, cpt.j0, cpt.j1, cpt.j2);
	p.p0 = get_point_in_list(polygone, cpt.j0);
	p.p1 = get_point_in_list(polygone, cpt.j1);
	p.p2 = get_point_in_list(polygone, cpt.j2);
	cpt.x = vertex_max_dist(polygone, p, tab);
	if (cpt.x == 0)
	{
		if (!(polygone1 = new_poly(w, win, polygone, cpt.j1, cpt.j2)))
			clear_n_exit(w, win);
		win->triangles = stock_last_triangle(w, win, win->triangles, tmp3, p);
		if (len_list(polygone1) == 3)
			win->triangles = stock_triangles(w, win, win->triangles,
				tmp3, polygone1);
		else
		{
			recursive_triangulate(w, win, tmp3, polygone1);
			free_list(polygone1);
		}
	}
	else
		win->triangles = two_poly(w, win, polygone, cpt, tmp3);
	return (win->triangles);
}

void		recursive_check(t_env *w, t_win *win)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		recursive_triangulate(w, win, tmp2, tmp2->head);
		tmp2 = tmp2->next;
	}
}
