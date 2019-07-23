/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_reset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:01:57 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/23 14:00:31 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fill_sprite(t_map_sprite *sprite, char **tmp)
{
	sprite->index = ft_atoi(tmp[1]);
	sprite->sector = ft_atoi(tmp[2]);
	sprite->sx = ft_atof(tmp[3]);
	sprite->sy = ft_atof(tmp[4]);
	sprite->vis = 1;
	sprite->taken = 0;
	sprite->range = 0.5;
}

int		parse_sprite_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;
	int		check;

	check = 0;
	if (tab[0] == NULL)
		return (-1);
	if (ft_strcmp(tab[0], "Section") != 0
		&& tab[1] != NULL && m->spmc < m->sprite_map_count)
	{
		tmp = ft_strsplit(tab[1], ',');
		while (tmp[check] != NULL)
			check++;
		if (check == 5)
		{
			nb = ft_atoi(tmp[0]);
			fill_sprite(&m->sprt[nb], tmp);
			m->sprt[nb].name = ft_strdup(tab[0]);
			m->spmc++;
		}
		else
			return (-1);
		ft_memreg(tmp);
	}
	return (0);
}

int		set_ennemy(t_map *m, int nb)
{
	m->ennemy[nb].range = 0.5;
	m->ennemy[nb].dead = 0;
	m->ennemy[nb].is_dead = 0;
	m->ennemy[nb].die = 1;
	m->ennemy[nb].count = 0;
	m->ennemy[nb].cpt = 0;
	m->ennemy[nb].nb_ammo = 0;
	m->ennemy[nb].touche = 0;
	m->ennemy[nb].move_speed.x = 0;
	m->ennemy[nb].move_speed.y = 0;
	m->ennemy[nb].move_speed.z = 0;
	m->ennemy[nb].move_speedless.x = 0;
	m->ennemy[nb].move_speedless.y = 0;
	m->ennemy[nb].move_speedless.z = 0;
	return (0);
}

void	fill_ennemy(t_map *m, t_ennemy *ennemy, char **tmp)
{
	ennemy->index = ft_atoi(tmp[1]);
	ennemy->sector = ft_atoi(tmp[2]);
	ennemy->coor.x = ft_atof(tmp[3]);
	ennemy->coor.y = ft_atof(tmp[4]);
	ennemy->coor.z = m->sector[ennemy->sector].floor + STAND;
	ennemy->fall = 1;
	ennemy->ground = 0;
	ennemy->moving = 0;
	ennemy->height = 0;
	ennemy->hole_low = 0;
	ennemy->hole_high = 0;
}

int		parse_ennemy_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;
	int		check;

	check = 0;
	if (tab[0] == NULL)
		return (-1);
	if (ft_strcmp(tab[0], "Section") != 0
		&& tab[1] != NULL && m->ennemyc < m->ennemy_count)
	{
		tmp = ft_strsplit(tab[1], ',');
		while (tmp[check] != NULL)
			check++;
		if (check == 5)
		{
			nb = ft_atoi(tmp[0]);
			fill_ennemy(m, &m->ennemy[nb], tmp);
			set_ennemy(m, nb);
			m->ennemyc++;
		}
		ft_memreg(tmp);
	}
	return (0);
}
