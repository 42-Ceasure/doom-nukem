/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:19:02 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/03 17:08:44 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_cal_sprt	calcul_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	tmp;
	
	tmp.v1x = m->sprt[x].sx - PL_X;
	tmp.v1y = m->sprt[x].sy - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	tmp.diffx = fabs(m->player.coor.x - m->sprt[x].sx);
	tmp.diffy = fabs(m->player.coor.y - m->sprt[x].sy);
	m->sprt[x].range = sqrt((tmp.diffx * tmp.diffx) + (tmp.diffy * tmp.diffy)) / 10;
	m->sprt[x].range = 1 / m->sprt[x].range;
	tmp.zoom = m->sprt[x].range;
	if (m->player.aiming == 1)
		tmp.zoom *= 2;
	tmp.x1 = WIDTH / 2 - (tmp.t1x * tmp.xscale1 + (m->sprite[m->sprt[x].index].w / 2
		* tmp.zoom * ratio));
	/*if (ft_strcmp(m->sprite[x].type, "decor") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprite[x].sector].ceiling
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - 10;*/
	if (ft_strcmp(m->sprite[m->sprt[x].index].type, "item") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor - m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - (m->sprite[m->sprt[x].index].h * tmp.zoom * ratio);		
	else if (ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor - m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - (100 * tmp.zoom * ratio);
	return (tmp);
}

void		draw_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	data;
	double		range;

	data = calcul_sprite(w, m, x, ratio);
	range = data.zoom;
	if (data.t1z > 0 && m->sprt[x].vis == 1)
	{
		if (ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0)
			final_sprite_to_screen(w, m->sprite[m->sprt[x].index], data.x1, data.y1a, 0, 100 * range * ratio);
		else
			final_sprite_to_screen(w, m->sprite[m->sprt[x].index], data.x1, data.y1a, m->sprite[m->sprt[x].index].w * range * ratio, 0);
	}
}

void	swipe_sprite(t_env *w, t_map *m, int x)
{
	if (w->dtime.walk == 0)
		m->ennemy[x].cpt++;
	if (m->ennemy[x].range < 1)
	{
		if (m->ennemy[x].cpt % 3 == 0)
			m->ennemy[x].index = 6;
		if (m->ennemy[x].cpt % 3 == 1)
			m->ennemy[x].index = 7;
		if (m->ennemy[x].cpt % 3 == 2)
			m->ennemy[x].index = 8;
	}
	else
	{
		if (m->ennemy[x].cpt % 2 == 0)
		{
			m->ennemy[x].index = 9;
			m->ennemy[x].die = 1;
		}
		else
		{
			m->ennemy[x].index = 10;
			if (m->ennemy[x].die == 1)
			{
				m->player.hp -= 10;
				m->ennemy[x].die = 0;
			}
		}
	}
	if (m->ennemy[x].touche == 1)
	{
		m->ennemy[x].index = 11;
		if (w->dtime.dead == 0)
			m->ennemy[x].count++;
		if (m->ennemy[x].count % 3 == 2)
		{
			m->ennemy[x].touche = 0;
			m->ennemy[x].count = 0;
		}
	}
	draw_ennemy(w, m, x, 5);
}

void	count_sprite(t_env *w, t_map *m)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		if (m->sprt[x].taken != 1)
			draw_sprite(w, m, x, 1);
		if (m->sprt[x].range >= 2 && ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0
			&& m->sprt[x].taken != 1)
		{
			if (ft_strcmp(m->sprt[x].name, "\thealth") == 0 && m->player.hp < 100)
			{
				m->player.hp += 30;
				m->sprt[x].taken = 1;
			}
			else if (ft_strcmp(m->sprt[x].name, "\tcartouche") == 0)
			{
				m->player.bullet[1] += 6;
				m->sprt[x].taken = 1;
			}
			else if (ft_strcmp(m->sprt[x].name, "\tammo") == 0)
			{
				m->player.bullet[0] += 30;
				m->sprt[x].taken = 1;
			}
		}
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		if (m->ennemy[x].vis == 1)
		{
			if (m->ennemy[x].dead == 0)
				swipe_sprite(w, m, x);
			else
			{
				if (w->dtime.dead == 0)
					m->ennemy[x].count++;
				if (m->ennemy[x].count % 3 == 0 && m->ennemy[x].is_dead == 0)
					m->ennemy[x].index = 11;
				else if (m->ennemy[x].count % 3 == 1 && m->ennemy[x].is_dead == 0)
					m->ennemy[x].index = 12;
				else
				{
					m->ennemy[x].index = 13;
					m->ennemy[x].is_dead = 1;
				}
				draw_ennemy(w, m, x, 5);
			}
		}
		x++;
	}
	m->player.firing = 0;
}

void	test_sprite(t_map *m, double xx, double yy)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		if (m->sprt[x].sx == (int)xx && m->sprt[x].sy == (int)yy)
			m->sprt[x].vis = 1;
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		if ((int)m->ennemy[x].coor.x == (int)xx && (int)m->ennemy[x].coor.y == (int)yy)
			m->ennemy[x].vis = 1;
		x++;
	}
}

void	clear_sprite(t_map *m)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		m->sprt[x].vis = 0;
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		m->ennemy[x].vis = 0;
		x++;
	}
}
