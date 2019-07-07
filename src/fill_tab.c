/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 16:09:48 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/07 16:18:26 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_swap(double *a, double *b)
{
	double		tmp;
	double		tmp2;
	double		tmp3;

	tmp = a[0];
	tmp2 = a[1];
	tmp3 = a[2];
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	b[0] = tmp;
	b[1] = tmp2;
	b[2] = tmp3;
}

double	**sort_double_tab(double **tab, int size)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i][0] > tab[i + 1][0])
		{
			ft_swap(tab[i], tab[i + 1]);
			sort_double_tab(tab, size);
		}
		i++;
	}
	return (tab);
}

double	**fill_tab_sprite(t_map *m, double **tab)
{
	int		x;
	double	diffx;
	double	diffy;

	x = 0;
	while (x < m->sprite_map_count)
	{
		tab[x] = (double*)malloc(sizeof(double) * 3 + 1);
		diffx = m->player.coor.x - m->sprt[x].sx;
		diffy = m->player.coor.y - m->sprt[x].sy;
		m->sprt[x].range = 1 / (sqrt((diffx * diffx) + (diffy * diffy)) / 10);
		tab[x][0] = m->sprt[x].range;
		tab[x][1] = x;
		tab[x][2] = 0;
		x++;
	}
	return (tab);
}

double	**fill_tab_ennemy(t_map *m, double **tab)
{
	int		i;
	double	diffx;
	double	diffy;

	i = 0;
	while (i < m->ennemy_count)
	{
		tab[m->sprite_map_count + i] = (double*)malloc(sizeof(double) * 3 + 1);
		diffx = m->player.coor.x - m->ennemy[i].coor.x;
		diffy = m->player.coor.y - m->ennemy[i].coor.y;
		m->ennemy[i].range = 1 / (sqrt((diffx * diffx) + (diffy * diffy)) / 10);
		tab[m->sprite_map_count + i][0] = m->ennemy[i].range;
		tab[m->sprite_map_count + i][1] = i;
		tab[m->sprite_map_count + i][2] = 1;
		i++;
	}
	return (tab);
}
