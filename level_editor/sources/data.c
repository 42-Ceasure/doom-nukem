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

/*void		write_in_file(t_win *win, char **tab)
{

}*/

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
	while (i < size -1)
	{
		if (tab[i] > tab[i + 1])
		{
			ft_swap(&tab[i], &tab[i + 1]);
			sort_int_tab(tab, size);
		}
		i++;
	}
}


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
					tmp->nb = win->number;
					win->number++;
					j++;
				}
				//printf("%d dot tab = \n", dot_tab[j]);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}

	i = i - l;

	sort_int_tab(dot_tab, i);

	j = 0;
	while (j < i)
	{
		k = k + int_len(dot_tab[j]);
		//printf("%d k = \n", k);
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
	//printf("%d y min \n", y);

	same_line_dots(win, y, j); //index a calculer suivant le nombre de dot
	y++;
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
					//y = tmp->y;
					boole = 1;

				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		if (boole)
			same_line_dots(win, y, j);
	}

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
	if (!(win->tab = (char **)malloc(sizeof(char *) * i + 1)))
		clear_n_exit(win, 1);


	//printf("%d dots \n", len_dots);
	//printf("%d sectors \n", len_sectors);
	//printf("%d assets \n", len_assets);

	dots_in_tab(win);
}

void		save_map(t_win *win)
{
	int			len_dots;
	int			i;
	int			j;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	i = 0;
	j = 0;
	len_dots = 0;
	tmp = NULL;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		i = len_list(tmp);
		len_dots = len_dots + i;
		tmp2 = tmp2->next;
	}
	//j = same_line_dots(win->lstlst);
	//len_dots -= j;

	create_tab(win, len_dots);

	//write_in_file(win, tab);

	//free_all(win);

}
