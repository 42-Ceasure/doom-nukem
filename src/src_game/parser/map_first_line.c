/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_first_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:53:23 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/24 14:03:24 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		first_line_compare(t_map *m, char **tmp)
{
	if (ft_strcmp(tmp[0], "dots") == 0
		&& fill_arg(&m->dots_count, tmp[1]) == 0)
		return (0);
	else if (ft_strcmp(tmp[0], "sector") == 0
		&& fill_arg(&m->sector_count, tmp[1]) == 0)
		return (0);
	else if (ft_strcmp(tmp[0], "sprite") == 0
		&& fill_arg(&m->sprite_map_count, tmp[1]) == 0)
		return (0);
	else if (ft_strcmp(tmp[0], "ennemy") == 0
		&& fill_arg(&m->ennemy_count, tmp[1]) == 0)
		return (0);
	else
		return (-1);
}

int		first_line_prepare(t_map *m, char **tab)
{
	char	**tmp;
	int		i;

	i = 0;
	while (i < 4)
	{
		tmp = ft_strsplit(tab[i], ':');
		if (tmp[0] == NULL || tmp[1] == NULL)
			return (-1);
		if (first_line_compare(m, tmp) != 0)
		{
			ft_memreg(tmp);
			return (-1);
		}
		ft_memreg(tmp);
		i++;
	}
	return (0);
}

int		first_line_check(t_map *m)
{
	char	**tmp;
	int		check;

	tmp = ft_strsplit(m->line, ',');
	check = 0;
	while (tmp[check] != NULL)
		check++;
	if (check != 4)
		return (-1);
	else
	{
		if (first_line_prepare(m, tmp) != 0)
			return (-1);
	}
	return (0);
}

int		parse_first_line(t_map *m)
{
	if (first_line_check(m) != 0)
		return (-1);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->sprt = (t_map_sprite *)malloc(sizeof(t_map_sprite)
		* m->sprite_map_count)) == NULL)
		return (-1);
	if ((m->ennemy = (t_ennemy *)malloc(sizeof(t_ennemy) * m->ennemy_count))
		== NULL)
		return (-1);
	init_map_structs(m);
	init_sprite_tab(m);
	return (0);
}
