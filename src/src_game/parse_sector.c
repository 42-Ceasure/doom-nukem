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
