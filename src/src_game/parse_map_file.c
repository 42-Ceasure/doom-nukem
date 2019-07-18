/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:27:27 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/17 11:18:09 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		first_line(char **tab, t_map *m)
{
	char	**tmp;

	tmp = ft_strsplit(tab[1], ',');
	m->dots_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[2], ',');
	M_S_C = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[3], ',');
	m->sprite_map_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[4], ',');
	m->ennemy_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
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
	return (0);
}

int		second_parse(t_env *w, t_map *m, char **tmp)
{
	if (m->section_number == 2)
	{
		if (parse_player_section(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 3)
	{
		if (parse_sprite_map(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 4)
	{
		if (parse_ennemy_map(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 5)
	{
		if (parse_level_map(m, tmp) == -1)
			return (-1);
	}
	else if (m->section_number == 6)
		w->stopread = 1;
	return (0);
}

int		parse_line(t_env *w, t_map *m)
{
	char	**tmp;

	tmp = ft_strsplit(m->line, ':');
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 0)
	{
		if (first_line(tmp, m) == -1)
			return (-1);
	}
	else if (m->section_number == 1)
	{
		process_hint_w(w, 4, "map");
		if (parse_map_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	else if (second_parse(w, m, tmp) == -1)
		return (-1);
	ft_memreg(tmp);
	return (0);
}
