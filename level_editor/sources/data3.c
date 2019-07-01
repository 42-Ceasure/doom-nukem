/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:47:14 by abechet           #+#    #+#             */
/*   Updated: 2019/07/01 14:47:31 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ft_swap(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_int_tab(int *tab, int size)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			ft_swap(&tab[i], &tab[i + 1]);
			sort_int_tab(tab, size);
		}
		i++;
	}
}

int		len_listlist(t_lstlst *lstlst)
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

int			number_of_dot_case(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;
	int			i;
	int			boole;

	y = 0;
	i = 0;
	while (y <= WIN_Y)
	{
		boole = 0;
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y && boole == 0)
				{
					i++;
					boole = 1;
				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		y++;
	}
	return (i);
}

int			total_number_of_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			len_dots;

	i = 0;
	len_dots = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		i = len_list(tmp);
		len_dots = len_dots + i;
		tmp2 = tmp2->next;
	}
	return (len_dots);
}

int			y_min_point(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;

	y = WIN_Y;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y < y)
				y = tmp->y;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (y);
}

int			x_min_on_line(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x;

	x = -1;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		x = WIN_X;
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				if (tmp->x < x)
					x = tmp->x;
			}
				tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (x);
}

int			number_of_dot_per_line_with_same(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;

	i = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
				i++;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (i);
}

int			*create_y_dot_tab(t_win *win, int y, int i)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			index;

	index = 0;
	if (!(dot_tab = (int *)malloc(sizeof(int) * i)))
		clear_n_exit(win, 1);

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				dot_tab[index] = tmp->x;
				index++;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	sort_int_tab(dot_tab, i);
	return (dot_tab);
}

int			number_of_dot_per_line(t_win *win, int y)
{
	int			*dot_tab;
	int			i;
	int			same;
	int			index;
	int			x;

	x = 0;
	index = 0;
	same = 0;
	i = number_of_dot_per_line_with_same(win, y);
	dot_tab = create_y_dot_tab(win, y, i);
	if (i > 1)
	{
		while (index < i - 1)
		{
			if (dot_tab[index] == dot_tab[index+1])
				same++;
			index++;
		}
	}
	i -= same;
	//free dot tab
	return (i);
}

int			total_exclusive_points(t_win *win)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (y <= WIN_Y)
	{
		i += number_of_dot_per_line(win, y);
		y++;
	}
	return (i);
}


void		sort_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x;
	int			y;
	int			same;
	int			used;
	int			i;
	int			index;
	int			*dot_tab;

	x = WIN_X;
	y = WIN_Y;
	tmp = NULL;
	same = 0;
	used = 0;
	index = 0;

	y = y_min_point(win);
	while (y < WIN_Y)
	{
		i = number_of_dot_per_line(win, y);
		if (i > 0)
		{
			index = 0;
			dot_tab = create_y_dot_tab(win, y, i);
			while (index < i)
			{
				tmp2 = win->lstlst;
				while (tmp2)
				{
					tmp = tmp2->head;
					while (tmp)
					{
						if (tmp->y == y && tmp->x == dot_tab[index])
						{
							tmp->nb = win->number;
							//printf("%d nb \n", win->number);
						}
						tmp = tmp->next;
					}
					tmp2 = tmp2->next;
				}
				win->number++;
				index++;
			}
		}
		y++;
	}
}


void		check(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			printf("%d nb \n", tmp->nb);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
}



void		fill_buffer(t_win *win)
{
	//char	*buffer[1000];


	printf("%d total exclusive \n", total_exclusive_points(win));

	sort_points(win);

	check(win);


	// open etc
}

void		map_save(t_win *win)
{
	int			len;
	int			z;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	z = -1;
	tmp = NULL;
	tmp2 = win->lstlst;

	//need check triangulation et croisements

	//check : all sector closed
	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		if (tmp2)
		{
			if (tmp2->closed)
				z = tmp2->sector;
		}
		tmp2 = tmp2->next;
	}
	len = len_listlist(win->lstlst);
	if (len - 1 == z)
		fill_buffer(win);
	win->number = 0;
	win->same_dots = 0;
	win->index_dot = 0;
	win->tab_index = 0;
}
