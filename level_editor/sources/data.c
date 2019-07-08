/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 10:51:32 by abechet           #+#    #+#             */
/*   Updated: 2019/06/25 10:51:44 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int		len_listasset(t_lstasset *lstasset)
{
	t_lstasset	*tmp;
	int		i;

	i = 0;
	tmp = lstasset;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

int		int_len(int nb)
{
	int	i;

	i = 0;
	while (nb > 9)
	{
		nb /= 10;
		i++;
	}
	i++;
	return (i);
}

void		same_line_dots(t_win *win, int y, int index)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	char		*line;
	int			*dot_tab;
	int			i;
	int			j;
	int			k;
	int			l;
	int			w;
	int			z;

	i = 0;
	j = 0;
	k = 0;
	w = 0;
	z = 0;
	l = 0;
	tmp = NULL;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
				i++;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	if (!(dot_tab = (int *)malloc(sizeof(int) * i)))
		clear_n_exit(win, 1);
	tmp = NULL;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		while (tmp)
		{
			z = 0;
			w = 0;
			if (tmp->y == y)
			{
				while (w < j)
				{
					if (dot_tab[w] == tmp->x)
					{
						l++;
						z = 1;
					}
					w++;
				}
				if (z == 0)
				{
					dot_tab[j] = tmp->x;
					j++;
				}
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	i = i - l;
	win->same_dots += l;
	win->index_dot  += i;
	sort_int_tab(dot_tab, i);
	j = 0;
	while (j < i)
	{
		k = k + int_len(dot_tab[j]);
		j++;
	}
	k = k + int_len(y);
	k = k + i - 1;
	k = k + 7;
	/*
		i = nombre d'int de la ligne
		i - 1 = nombre de virgule
		5 = dots:
		int len de y pour le y
		1 pour : apres le y
		1 pour \0
	*/
	if (!(win->tab[index] = (char *)malloc(sizeof(char) * k)))
		clear_n_exit(win, 1);
	win->tab[index][0] = 'd';
	win->tab[index][1] = 'o';
	win->tab[index][2] = 't';
	win->tab[index][3] = 's';
	win->tab[index][4] = ':';
	line = ft_itoa(y);
	j = 5;
	w = 0;
	l = 0;
	z = int_len(y);
	while (w < z)
	{
		win->tab[index][j] = line[w];
		j++;
		w++;
	}
	win->tab[index][j] = ':';
	j++;
	while (l < i)
	{
		line = ft_itoa(dot_tab[l]);
		z = int_len(dot_tab[l]);
		w = 0;
		while (w < z)
		{
			win->tab[index][j] = line[w];
			j++;
			w++;
		}
		if (l < i - 1)
		{
			win->tab[index][j] = ',';
			j++;
		}
		l++;
	}
	win->tab[index][j] = '\0';
	printf("%s \n", win->tab[index]);
}

void	dots_in_tab(t_win *win)
{
	int			x;
	int			y;
	int			i;
	int			j;
	t_lst		*tmp;
	t_lstlst	*tmp2;
	int			boole;

	x = 0;
	y = WIN_Y;
	i = 0;
	j = 0;
	tmp = NULL;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y < y)
				y = tmp->y;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	y--;
	while (y < WIN_Y)
	{
		y++;
		boole = 0;
		tmp = NULL;
		tmp2 = win->lstlst;
		while (tmp2)
		{
			if (tmp2)
				tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y)
				{
					j++;
					boole = 1;
				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		if (boole)
			same_line_dots(win, y, j);
	}
	win->tab_index = j;
}

void	create_tab(t_win *win, int len_dots)
{
	int		len_sectors;
	int		len_assets;
	int		i;
	int		y;

	y = 0;
	len_assets = len_listasset(win->lstasset);
	len_sectors = len_listlist(win->lstlst);
	i = len_assets + len_sectors + len_dots;
	// le len dot est faux puisqu'il compte les points sur les meme lignes
	if (!(win->tab = (char **)malloc(sizeof(char *) * i + 1)))
		clear_n_exit(win, 1);
	win->tab_malloced = 1;
	dots_in_tab(win);
}

void		save_map(t_win *win)
{
	int			len;
	int			len_dots;
	int			i;
	int			j;
	int			z;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	i = 0;
	j = 0;
	z = -1;
	len_dots = 0;
	tmp = NULL;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		i = len_list(tmp);
		len_dots = len_dots + i;
		if (tmp2)
		{
			if (tmp2->closed)
				z = tmp2->sector;
		}
		tmp2 = tmp2->next;
	}

	len = len_listlist(win->lstlst);
	if (len - 1 == z)
	{
		create_tab(win, len_dots);
		//number_of_cases(win);
		sectors_in_tab(win);
		//sectors_in_tab2(win);
	}

	win->number = 0;
	win->same_dots = 0;
	win->index_dot = 0;
	win->tab_index = 0;

	i = 0;
	while (i < 20)
	{
		printf("%s \n", win->tab[i]);
		i++;
	}

	win->tab = NULL;
	win->tab_malloced = 0;


	//free_all(win);

}
