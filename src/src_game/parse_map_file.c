/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:27:27 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 14:02:24 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	reset_player(t_env *w, t_map *m)
{
	m->player.bullet[0] = 0;
	m->player.bullet[1] = 0;
	m->player.take[0] = 0;
	m->player.take[1] = 0;
	m->player.take[2] = 0;
	m->player.take[3] = 0;
	m->player.intactu_ammo = 0;
	m->player.firing = 0;
	m->player.shooting = 0;
	m->player.field_of_vision_h = w->mem_field_of_vision_h;
	m->player.field_of_vision_v = w->mem_field_of_vision_v;
	m->player.aiming = 0;
	m->elevator = 0;
	m->weap[0].actu_ammo = m->weap[0].magazine;
	m->weap[1].actu_ammo = m->weap[1].magazine;
	m->weap[2].actu_ammo = m->weap[2].magazine;
}

void	init_map_structs(t_map *m)
{
	int	i;

	i = 0;
	while (i < m->sprite_map_count)
	{
		m->sprt[i].name = NULL;
		i++;
	}
}

int		parse_level_map(t_map *m, char **tab)
{
	char	**tmp;

	if (tab[0] == NULL)
		return (-1);
	if (ft_strcmp(tab[0], "Section") != 0
		&& tab[1] != NULL)
	{
		tmp = ft_strsplit(tab[1], ',');
		m->endsector = ft_atoi(tmp[0]);
		m->linklvl = ft_strdup(tmp[1]);
		ft_memreg(tmp);
	}
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

	if ((tmp = ft_strsplit(m->line, ':')) == NULL)
		return (-1);
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 0)
	{
		if (first_line(m) == -1)
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
