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

#include "editor.h"



double sign(double a)
{
	return (((a) > 0) - ((a) < 0));
}

double v_c_p(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

double pointside(t_dot m, double x0, double y0, double x1, double y1)
{
	return(v_c_p(x1 - x0, y1 - y0, m.x - x0, m.y - y0));
}

/*double isoverlap(double a0, double a1, double b0, double b1)
{
	if ((vmin(a0,a1) <= vmax(b0,b1) && vmin(b0,b1) <= vmax(a0,a1)))
		return (1);
	else
		return (0);
}

double intersectbox(t_intersect i)
{

	if (isoverlap(i.x1, i.x2, i.x3, i.x4) && isoverlap(i.y1, i.y2, i.y3, i.y4))
		return (1);
	else
		return (0);
}

t_coor intersect(t_intersect i)
{
	t_coor coor;
	double tmp1;
	double tmp2;
	double tmp3;
	double tmp4;

	tmp1 = v_c_p(i.x1, i.y1, i.x2, i.y2);
	tmp2 = i.x1 - i.x2;
	tmp3 = v_c_p(i.x3, i.y3, i.x4, i.y4);
	tmp4 = i.x3 - i.x4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.x = (coor.z / v_c_p(i.x1 - i.x2, i.y1 - i.y2, i.x3 - i.x4, i.y3 - i.y4));
	tmp1 = v_c_p(i.x1, i.y1, i.x2, i.y2);
	tmp2 = i.y1 - i.y2;
	tmp3 = v_c_p(i.x3, i.y3, i.x4, i.y4);
	tmp4 = i.y3 - i.y4;
	coor.z = v_c_p(tmp1, tmp2, tmp3, tmp4);
	coor.y = (coor.z / v_c_p(i.x1 - i.x2, i.y1 - i.y2, i.x3 - i.x4, i.y3 - i.y4));
	coor.z = 0;
	return (coor);
}*/



int		near_vertex(int n, int i, int di)
{
	if (n != 0)
		return ((n + (i + di) % n) % n);
	return (-10000);
}

int		point_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m)
{
	if (p2.y < p1.y)
	{
		if (pointside(m, p0.x, p0.y, p1.x, p1.y) < 0
		 	&& pointside(m, p1.x, p1.y, p2.x, p2.y) < 0
				&& pointside(m, p2.x, p2.y, p0.x, p0.y) < 0)
			return (1);
	}
	else
	{
		if (pointside(m, p0.x, p0.y, p1.x, p1.y) > 0
	 		&& pointside(m, p1.x, p1.y, p2.x, p2.y) > 0
				&& pointside(m, p2.x, p2.y, p0.x, p0.y) > 0)
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
			if (p.x < x)
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
	//printf("n =%d\n", n);
	distance = 0.0;
	j = 0;
	i = 0;
	while (i < n)
	{
		if (i != tab[0] && i != tab[1] && i != tab[2])
		{
			m = get_point_in_list(polygone, i);
			// if (m.x == -1 && m.y == -1)
			// 	return (-1);
			if (point_in_triangle(p0, p1, p2, m) == 1)
			{
				d = fabs(pointside(m, p1.x, p1.y, p2.x, p2.y));
				//printf("d =%d\n", d);
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

t_lstlst	*triangles_new(t_lst *polygone)
{
	t_lstlst	*tmp;

	if (!(tmp = (t_lstlst *)malloc(sizeof(t_lstlst))))
		return (NULL);
	tmp->head = polygone;
	tmp->next = NULL;
	return (tmp);
}

t_lstlst	*fill_link(t_dot p0, t_dot p1, t_dot p2)
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
	//tmp->head->next = NULL;

	tmp->head->next = l1;
	tmp->head->next->next = l2;
	tmp->head->next->next->next = NULL;
	tmp->next = NULL;
	return (tmp);
}


t_lstlst	*recursive_triangulate(t_win *win, t_lst *polygone, t_lstlst *triangles)
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
	n = len_list(polygone);
	j0 = left_vertex(polygone);
	j1 = near_vertex(n, j0, 1);
	j2 = near_vertex(n, j0, -1);
	printf("j0 %d  j1%d  j2%d\n", j0,j1,j2);
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
	//printf("%d k = \n", k);
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
			win->triangles = fill_link(p0, p1, p2);
		else
		{
			tmp2 = win->triangles;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = fill_link(p0, p1, p2);
		}
		if (len_list(polygone1) == 3)
		{
			if (win->triangles == NULL)
				win->triangles = triangles_new(polygone1);
			else
			{
				tmp2 = win->triangles;
				while (tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = triangles_new(polygone1);
			}
		}
		else
		{
			printf("recursive\n");
			recursive_triangulate(win, polygone1, win->triangles);
		}
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
				win->triangles = triangles_new(polygone1);
			else
			{
				tmp2 = win->triangles;
				while (tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = triangles_new(polygone1);
			}
		}
		else
			recursive_triangulate(win, polygone1, win->triangles);
		if (len_list(polygone2) == 3)
		{
			if (win->triangles == NULL)
				win->triangles = triangles_new(polygone2);
			else
			{
				tmp2 = win->triangles;
				while (tmp2->next)
					tmp2 = tmp2->next;
				tmp2->next = triangles_new(polygone2);
			}
		}
		else
			recursive_triangulate(win, polygone2, win->triangles);
	}
	return (win->triangles);
}

void		recursive_check(t_win *win)
{
	t_lstlst	*tmp2;
	int			i;

	i = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (len_list(tmp2->head) <= 3)
			i = 1;
		printf("%d len \n", len_list(tmp2->head));

		tmp2 = tmp2->next;
	}

	printf("%d i \n", i);
	//printf("%d len \n", len_list(tmp2->head));

	tmp2 = win->lstlst;
	if (i == 0)
	{
		clear_window(win);
		while (tmp2)
		{
			recursive_triangulate(win, tmp2->head, win->triangles);
			tmp2 = tmp2->next;
		}
	}
}
