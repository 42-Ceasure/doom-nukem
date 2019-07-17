/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_and_reset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:01:57 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/12 13:31:23 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	reset_player(t_map *m)
{
	m->player.bullet[0] = 0;
	m->player.bullet[1] = 0;
	m->player.take[0] = 0;
	m->player.take[1] = 0;
	m->player.take[2] = 0;
	m->player.take[3] = 0;
	m->player.intactu_ammo = 0;
	m->weap[0].actu_ammo = m->weap[0].magazine;
	m->weap[1].actu_ammo = m->weap[1].magazine;
	m->weap[2].actu_ammo = m->weap[2].magazine;
}

int		parse_sprite_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;

	if (ft_strcmp(tab[0], "Section") != 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		nb = ft_atoi(tmp[0]);
		m->sprt[nb].name = ft_strdup(tab[0]);
		m->sprt[nb].index = ft_atoi(tmp[1]);
		m->sprt[nb].sector = ft_atoi(tmp[2]);
		m->sprt[nb].sx = ft_atof(tmp[3]);
		m->sprt[nb].sy = ft_atof(tmp[4]);
		m->sprt[nb].vis = 1;
		m->sprt[nb].taken = 0;
		m->sprt[nb].range = 0.5;
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
	if (!(m->ennemy[nb].dammage = Mix_LoadWAV("./sounds/oof.wav")))
		return (-1);
	Mix_VolumeChunk(m->ennemy[nb].dammage, 110);
	m->ennemy[nb].move_speed.x = 0;
	m->ennemy[nb].move_speed.y = 0;
	m->ennemy[nb].move_speed.z = 0;
	m->ennemy[nb].move_speedless.x = 0;
	m->ennemy[nb].move_speedless.y = 0;
	m->ennemy[nb].move_speedless.z = 0;
	return (0);
}

int		parse_ennemy_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;

	if (ft_strcmp(tab[0], "Section") != 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		nb = ft_atoi(tmp[0]);
		m->ennemy[nb].index = ft_atoi(tmp[1]);
		m->ennemy[nb].sector = ft_atoi(tmp[2]);
		m->ennemy[nb].coor.x = ft_atof(tmp[3]);
		m->ennemy[nb].coor.y = ft_atof(tmp[4]);
		m->ennemy[nb].coor.z = m->sector[m->ennemy[nb].sector].floor + STAND;
		m->ennemy[nb].fall = 1;
		m->ennemy[nb].ground = 0;
		m->ennemy[nb].moving = 0;
		m->ennemy[nb].height = 0;
		m->ennemy[nb].hole_low = 0;
		m->ennemy[nb].hole_high = 0;
		set_ennemy(m, nb);
		ft_memreg(tmp);
	}
	return (0);
}

int		parse_level_map(t_map *m, char **tab)
{
	char	**tmp;

	if (ft_strcmp(tab[0], "Section") != 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		m->endsector = ft_atoi(tmp[0]);
		m->linklvl = ft_strdup(tmp[1]);
		ft_memreg(tmp);
	}
	return (0);
}