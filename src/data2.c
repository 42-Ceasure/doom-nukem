/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:58:10 by abechet           #+#    #+#             */
/*   Updated: 2019/06/27 12:58:21 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fill_sector_dots_tab(t_win *win, t_lst *tmp, int *tab)
{
	int		i;
	int		j;

	i = 0;
	j = len_list(tmp);
	if (win->lstlst)
	{
		while (i < j - 1)
		{
			tab[i] = tmp->nb;
			//printf("%d tab \n", tab[i]);
			i++;
			tmp = tmp->next;
			if (tmp == NULL)
				break;
		}
	}
}

void		sector_line(t_win *win, int index, t_lstlst *tmp2)
{
	t_lst		*tmp;
	char		*line;
	int			*sector_dots_tab;
	int			i;
	int			j;
	int			k;
	int			w;
	int			z;
	int			a;

	k = 0;
	tmp = tmp2->head;
	j = len_list(tmp);
	i = 12; //pour sector:0,30:
	i = j - 1; //pour les virgules des points
	i = i + j + 1; // pour les virgules des voisins, le : et le \0

	if (!(sector_dots_tab = (int *)malloc(sizeof(int) * j)))
		clear_n_exit(win, 1);

	fill_sector_dots_tab(win, tmp, sector_dots_tab);

	while (k < j)
	{
		i = i + int_len(sector_dots_tab[k]);
		k++;
	}

	if (!(win->tab[index] = (char *)malloc(sizeof(char) * i)))
		clear_n_exit(win, 1);


	win->tab[index][0] = 's';
	win->tab[index][1] = 'e';
	win->tab[index][2] = 'c';
	win->tab[index][3] = 't';
	win->tab[index][4] = 'o';
	win->tab[index][5] = 'r';
	win->tab[index][6] = ':';
	win->tab[index][7] = '0';
	win->tab[index][8] = ',';
	win->tab[index][9] = '3';
	win->tab[index][10] = '0';
	win->tab[index][11] = ':';

	k = 0;
	w = 12;
	while (k < j)
	{
		line = ft_itoa(sector_dots_tab[k]);
		z = int_len(sector_dots_tab[k]);
		a = 0;
		while (a < z)
		{
			win->tab[index][w] = line[a];
			w++;
			a++;
		}
		if (k < j - 1)
		{
			win->tab[index][w] = ',';
			w++;
		}
		k++;
	}
}

void		sectors_in_tab(t_win *win)
{
	int			len_sectors;
	int			index;
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	len_sectors = len_listlist(win->lstlst);
	index = win->index_dot;
	len_sectors += index;
	while (index < len_sectors)
	{
		sector_line(win, index, tmp2);
		index++;
		tmp2 = tmp2->next;
		if (tmp2 == NULL)
			break;
	}
}
