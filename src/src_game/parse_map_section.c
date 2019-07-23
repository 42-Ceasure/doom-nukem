/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_section.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:04:03 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 14:48:50 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			parse_map_dots(t_map *m, char *y, char *x)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(x, ',');
	while (tmp[i] != NULL)
	{
		if (m->i < m->dots_count)
		{
			m->dot[m->i].x = ft_atof(tmp[i]);
			m->dot[m->i].y = ft_atof(y);
		}
		i++;
		m->i++;
		m->dotsc++;
	}
	if (m->i > m->dots_count)
		return (-1);
	ft_memreg(tmp);
	return (0);
}

int			alloc_sector(t_map *m)
{
	if ((m->sector[m->s].dot = (t_dot *)malloc(sizeof(t_dot)
		* (m->sector[m->s].wall_count + 1))) == NULL)
		return (-1);
	if ((m->sector[m->s].network = (int *)malloc(sizeof(int)
		* m->sector[m->s].wall_count)) == NULL)
		return (-1);
	return (0);
}

int			parse_sectors(t_map *m, char **tab)
{
	int		i;
	char	**tmp;

	i = 0;
	if (m->s < m->sector_count)
	{
		tmp = ft_strsplit(tab[1], ',');
		m->sector[m->s].floor = ft_atof(tmp[0]);
		m->sector[m->s].ceiling = ft_atof(tmp[1]);
		ft_memreg(tmp);
		tmp = ft_strsplit(tab[2], ',');
		while (tmp[i] != NULL)
			i++;
		m->sector[m->s].wall_count = i;
		if (alloc_sector(m) == -1)
			return (-1);
		if (parse_sector_dots(m, tmp) == -1)
			return (-1);
		parse_sector_network(m, tab[3]);
		parse_sector_texturing(m, tab[4]);
	}
	else
		return (-1);
	m->s++;
	return (0);
}

int			parse_map_section(t_map *m, char **tab)
{
	if (ft_strcmp(tab[0], "\tdots") == 0)
	{
		if (parse_map_dots(m, tab[1], tab[2]) == -1)
		{
			ft_putendl("error on parsing of the dot section");
			return (-1);
		}
	}
	else if (ft_strcmp(tab[0], "\tsector") == 0)
	{
		if (parse_sectors(m, tab) == -1)
		{
			ft_putendl("error on parsing of the \"sector\" section");
			return (-1);
		}
	}
	else if (ft_strcmp(tab[0], "Section") != 0)
		return (-1);
	return (0);
}
