/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sector.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 14:42:33 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 14:46:47 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			parse_sector_network(t_map *m, char *net)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(net, ',');
	while (i < m->sector[m->s].wall_count && tmp[i] != '\0')
	{
		if (ft_strcmp(tmp[i], "x") != 0)
			m->sector[m->s].network[i] = ft_atoi(tmp[i]);
		else
			m->sector[m->s].network[i] = -1;
		i++;
	}
	if (i != m->sector[m->s].wall_count)
		return (-1);
	ft_memreg(tmp);
	return (0);
}

int			parse_sector_texturing(t_map *m, char *text)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(text, ',');
	while (i < 6)
	{
		m->sector[m->s].texturing[i] = ft_atoi(tmp[i]);
		i++;
	}
	ft_memreg(tmp);
	return (0);
}

int			parse_sector_dots(t_map *m, char **dots)
{
	int		i;
	int		mem[2];

	i = 0;
	mem[0] = 0;
	mem[1] = 0;
	while (i < m->sector[m->s].wall_count)
	{
		mem[0] = ft_atoi(dots[i]);
		if (mem[0] > m->dots_count - 1)
		{
			ft_putendl("Error on map file.");
			return (-1);
		}
		if (i == 0)
			mem[1] = mem[0];
		m->sector[m->s].dot[i].x = m->dot[mem[0]].x;
		m->sector[m->s].dot[i].y = m->dot[mem[0]].y;
		i++;
	}
	m->sector[m->s].dot[i].x = m->dot[mem[1]].x;
	m->sector[m->s].dot[i].y = m->dot[mem[1]].y;
	ft_memreg(dots);
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
