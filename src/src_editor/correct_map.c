/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:58:10 by abechet           #+#    #+#             */
/*   Updated: 2019/07/24 10:52:19 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			check_player_start(t_win *win)
{
	t_lstasset	*tmp;
	int			ret;

	ret = -1;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
		{
			ret = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (ret == 0)
		ret = triangulate_player_start(win, tmp->x, tmp->y);
	return (ret);
}
t_dot		first_dot(t_lst *tmp, t_lstlst *tmp2, t_dot p2)
{
	if (tmp->next == NULL)
	{
		p2.x = tmp2->head->next->x;
		p2.y = tmp2->head->next->y;
	}
	else
	{
		p2.x = tmp->next->x;
		p2.y = tmp->next->y;
	}
	return (p2);
}

int			is_crossed(t_point p, t_lst *tmp, t_lst *tmp0)
{
	if ((p.p1.x != p.p2.x || p.p1.y != p.p2.y) && (p.p2.x != p.p3.x || p.p2.y != p.p3.y)
		&& (p.p3.x != p.p4.x || p.p3.y != p.p4.y) && (p.p4.x != p.p1.x || p.p4.y != p.p1.y))
	{
		if (tmp->sector != tmp0->sector)
		{
			if ((p.p1.x != p.p3.x || p.p1.y != p.p3.y)
				&& (p.p2.x != p.p4.x || p.p2.y != p.p4.y))
			{
				ft_putendl("Crossed segments \n");
				return (-3);
			}
		}
		else
		{
			ft_putendl("Crossed segments \n");
			return (-3);
		}
	}
	return (0);
}

int			one_sector(t_point p, t_lst *tmp, t_lst *tmp0, t_lstlst *tmp2)
{
	while (tmp0)
	{
		if (p.index2 != p.index3 && p.index3 + 1 != p.index2
			&& p.index4 != p.index2 && p.index4 + 1 != p.index2)
		{
			if (p.index3 != p.index2 && p.index2 + 1 != p.index3
				&& p.index5 != p.index3 && p.index5 + 1 != p.index3)
			{
				p.p4 = first_dot(tmp0, tmp2, p.p4);
				p.p3.x = tmp0->x;
				p.p3.y = tmp0->y;
				if ((p.ret = sector_intersect_with_itself(p.p1,
					p.p2, p.p3, p.p4)) == 1)
					if (is_crossed(p, tmp, tmp0) == -3)
						return (-3);
			}
		}
		p.index2++;
		tmp0 = tmp0->next;
	}
	return (0);
}

int			multi_sector(t_lstlst *tmp2, t_lst *tmp, t_point p)
{
	t_lst		*tmp0;

	p.index2 = 0;
	while (tmp2)
	{
		tmp0 = tmp2->head;
		p.len = len_list(tmp0);
		p.index4 = p.index3 + p.len - 2;
		p.index5 = p.index2 + p.len - 2;
		if (one_sector(p, tmp, tmp0, tmp2) == -3)
			return (-3);
		tmp2 = tmp2->next;
	}
	return (0);
}

int			correct_intersections_in_a_sector(t_win *win)
{
	t_lstlst	*tmp3;
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_point		p;

	p.index3 = 0;
	tmp3 = win->lstlst;
	while (tmp3)
	{
		tmp = tmp3->head;
		while (tmp)
		{
			p.p2 = first_dot(tmp, tmp3, p.p2);
			p.p1.x = tmp->x;
			p.p1.y = tmp->y;
			tmp2 = win->lstlst;
			if (multi_sector(tmp2, tmp, p) == -3)
				return (-3);
			p.index3++;
			tmp = tmp->next;
		}
		tmp3 = tmp3->next;
	}
	return (0);
}

int			point_in_triangle2(t_dot p0, t_dot p1, t_dot p2, t_dot m)
{
	if (pointside2(m, p0, p1.x, p1.y) >= 0)
	{
		if (pointside2(m, p0, p1.x, p1.y) > 0
		&& pointside2(m, p1, p2.x, p2.y) > 0
		&& pointside2(m, p2, p0.x, p0.y) > 0)
			return (1);
	}
	else
	{
		if (pointside2(m, p0, p1.x, p1.y) < 0
		&& pointside2(m, p1, p2.x, p2.y) < 0
		&& pointside2(m, p2, p0.x, p0.y) < 0)
			return (1);
	}
	return (0);
}

int			sector_inside_sector_helper(t_dot m, t_lstlst *tmp3, t_lstlst *tmp2)
{
	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	int			ret;
	t_lst		*tmp0;

	ret = 0;
	while (tmp3)
	{
		if (tmp3->sector != -1)
		{
			tmp0 = tmp3->head;
			if (tmp3->sector != tmp2->sector)
			{
				p0 = get_point_in_list(tmp0, 0);
				p1 = get_point_in_list(tmp0, 1);
				p2 = get_point_in_list(tmp0, 2);
				ret = point_in_triangle2(p0, p1, p2, m);
				if (ret == 1)
					return (-5);
			}
		}
		tmp3 = tmp3->next;
	}
	return (0);
}

int			sector_inside_sector(t_win *win)
{
	t_lstlst	*tmp2;
	t_lstlst	*tmp3;
	t_lst		*tmp;
	t_dot		m;

	tmp2 = win->triangles;
	while (tmp2)
	{
		if (tmp2->sector != -1)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				tmp3 = win->triangles;
				m.x = tmp->x;
				m.y = tmp->y;
				if (sector_inside_sector_helper(m, tmp3, tmp2) == -5)
					return (-5);
				tmp = tmp->next;
			}
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int			point_on_top_helper(t_lstlst *tmp2, t_lst *tmp, t_lst *tmp0)
{
	int			index;
	int			index0;

	while (tmp2)
	{
		tmp = tmp2->head;
		index = 0;
		while (tmp->next)
		{
			index0 = 0;
			tmp0 = tmp2->head;
			while (tmp0->next)
			{
				if (index != index0)
					if (tmp->x == tmp0->x && tmp->y == tmp0->y)
						return (-6);
				tmp0 = tmp0->next;
				index0++;
			}
			tmp = tmp->next;
			index++;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int			point_on_top(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_lst		*tmp0;
	int			ret;

	tmp = NULL;
	tmp0 = NULL;
	tmp2 = win->lstlst;
	ret = point_on_top_helper(tmp2, tmp, tmp0);
	if (ret == -6)
		return (-6);
	return (0);
}

int			sectors_on_top_helper(t_lst *tmp, t_lstlst *tmp3)
{
	int		i;
	t_lst	*tmp0;

	i = 0;
	while (tmp->next)
	{
		tmp0 = tmp3->head;
		while (tmp0->next)
		{
			if (tmp->x == tmp0->x && tmp->y == tmp0->y)
				i++;
			tmp0 = tmp0->next;
		}
		tmp = tmp->next;
	}
	return (i);
}

int			sectors_on_top(t_lstlst *tmp2)
{
	t_lstlst	*tmp3;
	t_lst		*tmp;
	int			len2;
	int			i;

	while (tmp2->next)
	{
		tmp3 = tmp2->next;
		len2 = len_list(tmp2->head);
		while (tmp3)
		{
			if (len2 == len_list(tmp3->head))
			{
				tmp = tmp2->head;
				i = sectors_on_top_helper(tmp, tmp3);
				if (i == len2 - 1)
					return (-7);
			}
			tmp3 = tmp3->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

int			correct_map_helper(t_win *win)
{
	t_lstlst	*tmp2;
	int			ret;

	tmp2 = win->lstlst;
	ret = 0;
	ret = sectors_on_top(tmp2);
	if (ret == -7)
	{
		printf("Two sectors on top of each other\n");
		return (ret);
	}
	ret = point_on_top(win);
	if (ret == -6)
	{
		printf("Two points on top of each other in same sector\n");
		return (ret);
	}
	ret = sector_inside_sector(win);
	if (ret == -5)
	{
		printf("Sector inside a sector\n");
		return (ret);
	}
	return (ret);
}

int			correct_map(t_win *win)
{
	int		ret;

	ret = 0;
	ret = correct_map_helper(win);
	if (ret != 0)
		return (ret);
	ret = correct_three_points(win);
	if (ret == -4)
	{
		printf("Too many points of a sector on same x\n");
		return (ret);
	}
	ret = correct_intersections_in_a_sector(win);
	if (ret == -3)
	{
		printf("Crossed segments \n");
		return (ret);
	}
	ret = check_player_start(win);
	if (ret == -1)
		printf("Map need a player start \n");
	if (ret == -2)
		printf("Player start need to be inside a sector \n");
	return (ret);
}
