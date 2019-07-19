/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:24:13 by abechet           #+#    #+#             */
/*   Updated: 2019/06/18 10:24:22 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int vmin2(int a, int b)
{
    if (a < b)
        return (a);
    else
        return (b);
}
int vmax2(int a, int b)
{
    if (a > b)
        return (a);
    else
        return (b);
}

double pointside2(t_dot m, double x0, double y0, double x1, double y1)
{
	return(v_c_p(x1 - x0, y1 - y0, m.x - x0, m.y - y0));
}

int		isoverlap2(int a0, int a1, int b0, int b1)
{
	if ((vmin2(a0,a1) <= vmax2(b0,b1) && vmin2(b0,b1) <= vmax2(a0,a1)))
		return (1);
	else
		return (0);
}

int		intersectbox2(t_dot p1, t_dot p2, t_dot p3, t_dot p4)
{

	if (isoverlap2(p1.x, p2.x, p3.x, p4.x) && isoverlap2(p1.y, p2.y, p3.y, p4.y))
		return (1);
	else
		return (0);
}

int		near_vertex(int n, int i, int di)
{
	if (n != 0)
		return ((n + (i + di) % n) % n);
	return (-10000);
}

int		point_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m)
{
	if (pointside2(m, p0.x, p0.y, p1.x, p1.y) >= 0)
	{
		if (pointside2(m, p0.x, p0.y, p1.x, p1.y) >= 0
		&& pointside2(m, p1.x, p1.y, p2.x, p2.y) >= 0
		&& pointside2(m, p2.x, p2.y, p0.x, p0.y) >= 0)
			return (1);
	}
	else
	{
		if (pointside2(m, p0.x, p0.y, p1.x, p1.y) <= 0
		&& pointside2(m, p1.x, p1.y, p2.x, p2.y) <=0
		&& pointside2(m, p2.x, p2.y, p0.x, p0.y) <= 0)
			return (1);
	}
	return (0);
}

int		*indice(t_win *win, int i, int j, int k)
{
	int		*tab;

	if (!(tab = (int *)malloc(sizeof(int) * 3)))
		clear_n_exit(win, 1);
	tab[0] = i;
	tab[1] = j;
	tab[2] = k;
	return (tab);
}

int		len_list(t_lst *lst)
{
	t_lst	*tmp;
	int		i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

t_dot	get_point_in_list(t_lst *polygone, int index)
{
	t_dot	p;
	t_lst	*tmp;
	int		i;

	i = 0;
	p.x = -1;
	p.y = -1;
	tmp = polygone;
	if (tmp)
	{
		while (i < index)
		{
			if (tmp == NULL)
				return (p);
			tmp = tmp->next;
			i++;
		}
		p.x = tmp->x;
		p.y = tmp->y;
	}
	return (p);
}

t_lst	*polylstnew(t_dot d)
{
	t_lst	*tmp;

	if (!(tmp = (t_lst *)malloc(sizeof(t_lst))))
		return (NULL);
	tmp->x = d.x;
	tmp->y = d.y;
	tmp->next = NULL;

	return (tmp);
}

t_lst	*new_poly(t_lst *polygone, int start, int end)
{
	int			n;
	int			i;
	t_lst		*p;
	t_lst		*tmp;

	p = NULL;
	tmp = NULL;
	n = len_list(polygone);
	i = start;
	while (i != end)
	{
		if (p == NULL)
		{
			p = polylstnew(get_point_in_list(polygone, i));
			tmp = p;
			if (p->x == -1 && p->y == -1)
				return (NULL);
		}
		else
		{
			while (p->next)
				p = p->next;
			p->next = polylstnew(get_point_in_list(polygone, i));
		}
		i = near_vertex(n, i, 1);
		if (i == -10000)
			return (p);
	}
	if (p)
	{
		while (p->next)
			p = p->next;
		p->next = polylstnew(get_point_in_list(polygone, i));
	}

	// free la liste quelque part

	return (tmp);
}

int		left_vertex(t_lst *polygone)
{
	int		n;
	int		x;
	int		j;
	int		i;
	t_lst	*tmp;
	t_dot	p;

	j = 0;
	tmp = polygone;
	if (!tmp)
		return (j);
	x = tmp->x;
	n = len_list(tmp);
	i = 1;
	while (i < n)
	{
		p = get_point_in_list(tmp, i);
		if (p.x != -1 && p.y != -1)
		{
			if (p.x <= x)
			{
				x = p.x;
				j = i;
			}
		}
		i++;
	}
	return (j);
}

int		vertex_max_dist(t_lst *polygone, t_dot p0, t_dot p1, t_dot p2, int *tab)
{
	int		n;
	int		i;
	int		j;
	int		d;
	t_dot	m;
	double	distance;

	n = len_list(polygone);
	distance = 0.0;
	j = 0;
	i = 0;
	while (i < n)
	{
		if (i != tab[0] && i != tab[1] && i != tab[2])
		{
			m = get_point_in_list(polygone, i);
			if (point_in_triangle(p0, p1, p2, m) == 1)
			{
				d = fabs(pointside2(m, p1.x, p1.y, p2.x, p2.y));
				if (d > distance)
				{
					distance = d;
					j = i;
				}
			}
		}
		i++;
	}
	return (j);
	// free tab a la fin
}

t_lstlst	*triangles_new(t_lstlst *tmp3, t_lst *polygone)
{
	t_lstlst	*tmp;

	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		return (NULL);
	tmp->head = polygone;
	tmp->next = NULL;
	tmp->txtr_wall = tmp3->txtr_wall;
	tmp->txtr_ceiling = tmp3->txtr_ceiling;
	tmp->txtr_floor = tmp3->txtr_floor;
	tmp->txtr_lower_extrude = tmp3->txtr_lower_extrude;
	tmp->txtr_higher_extrude = tmp3->txtr_higher_extrude;

	return (tmp);
}

t_lstlst	*fill_link(t_lstlst *tmp3, t_dot p0, t_dot p1, t_dot p2)
{
	t_lstlst	*tmp;

	t_lst		*l0;
	t_lst		*l1;
	t_lst		*l2;

	l0 = polylstnew(p0);
	l1 = polylstnew(p1);
	l2 = polylstnew(p2);
	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		return (NULL);
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

t_lstlst	*recursive_triangulate(t_win *win, t_lstlst *tmp3, t_lst *polygone, t_lstlst *triangles)
{
	int		n;
	int		k;
	int		j0;
	int		j1;
	int		j2;
	int		*tab;
	t_dot	p0;
	t_dot	p1;
	t_dot	p2;
	t_lst	*polygone1;
	t_lst	*polygone2;
	t_lstlst	*tmp2;

	tmp2 = NULL;
	triangles = NULL;
	(void)triangles;
	n = len_list(polygone);
	j0 = left_vertex(polygone);
	j1 = near_vertex(n, j0, 1);
	j2 = near_vertex(n, j0, -1);
	if (j1 == -10000 || j2 == -10000)
		clear_n_exit(win, 1);
	tab = indice(win, j0, j1, j2);
	p0 = get_point_in_list(polygone, j0);
	p1 = get_point_in_list(polygone, j1);
	p2 = get_point_in_list(polygone, j2);
	if ((p0.x == -1 && p0.y == -1) || (p1.x == -1 && p1.y == -1)
		|| (p2.x == -1 && p2.y == -1))
	{
		printf("p0, p1 ou p2 error");
		clear_n_exit(win, 1);
	}
	k = vertex_max_dist(polygone, p0, p1, p2, tab);
	if (k == -1)
		clear_n_exit(win, 1);
	if (k == 0)
	{
		if ((polygone1 = new_poly(polygone, j1, j2)) == NULL)
		{
			printf("polygone1_1");
			clear_n_exit(win, 1);
		}

		if (win->triangles == NULL)
			win->triangles = fill_link(tmp3, p0, p1, p2);
		else
		{
			tmp2 = win->triangles;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = fill_link(tmp3, p0, p1, p2);
		}
		if (len_list(polygone1) == 3)
		{
			if (win->triangles == NULL)
				win->triangles = triangles_new(tmp3, polygone1);
			else
			{
				tmp2 = win->triangles;
				while (tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = triangles_new(tmp3, polygone1);
			}
		}
		else
			recursive_triangulate(win, tmp3, polygone1, win->triangles);
	}
	else
	{
		if ((polygone1 = new_poly(polygone, j0, k)) == NULL)
		{
			printf("polygone1_2");
			clear_n_exit(win, 1);
		}
		if ((polygone2 = new_poly(polygone, k , j0)) == NULL)
		{
			printf("polygone2");
			clear_n_exit(win, 1);
		}
		if (len_list(polygone1) == 3)
		{
			if (win->triangles == NULL)
				win->triangles = triangles_new(tmp3, polygone1);
			else
			{
				tmp2 = win->triangles;
				while (tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = triangles_new(tmp3, polygone1);
			}
		}
		else
			recursive_triangulate(win, tmp3, polygone1, win->triangles);
		if (len_list(polygone2) == 3)
		{
			if (win->triangles == NULL)
				win->triangles = triangles_new(tmp3, polygone2);
			else
			{
				tmp2 = win->triangles;
				while (tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = triangles_new(tmp3, polygone2);
			}
		}
		else
			recursive_triangulate(win, tmp3, polygone2, win->triangles);
	}
	return (win->triangles);
}

void		recursive_check(t_win *win)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		recursive_triangulate(win, tmp2, tmp2->head, win->triangles);
		tmp2 = tmp2->next;
	}
}
