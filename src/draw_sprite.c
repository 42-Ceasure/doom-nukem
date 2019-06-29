/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:19:02 by ochaar            #+#    #+#             */
/*   Updated: 2019/06/29 17:00:25 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		swipe_sprite(t_env *w, t_map *m, int x)
{
	if (w->dtime.walk == 0)
		m->k++;
	if (m->ennemy.range < 1)
	{
		if (m->k % 3 == 0)
			x = 5;
		if (m->k % 3 == 1)
			x = 6;
		if (m->k % 3 == 2)
			x = 7;
	}
	else
	{
		if (m->k % 2 == 0)
		{
			x = 8;
			m->i = 1;
		}
		else
		{
			x = 9;
			if (m->i == 1)
			{
				m->player.hp -= 10;
				m->i = 0;
			}
		}
	}
	if (m->ennemy.touche == 1)
	{
		x = 10;
		if (w->dtime.dead == 0)
			m->ennemy.count++;
		if (m->ennemy.count % 3 == 2)
		{
			m->ennemy.touche = 0;
			m->ennemy.count = 0;
		}
	}
	draw_ennemy(w, m, x);
	x += 4;
	return (x);
}

void	count_sprite(t_env *w, t_map *m)
{
	int x;

	x = 0;
	while (x < 10)
	{
		if (ft_strcmp(m->sprite[x].type, "ennemy") != 0)
			draw_sprite(w, m, x, 1);
		else if (m->ennemy.dead == 0)
			x = swipe_sprite(w, m, x);
		else
		{
			if (w->dtime.dead == 0)
				m->ennemy.count++;
			if (m->ennemy.count % 3 == 0 && m->ennemy.is_dead == 0)
				x = 10;
			else if (m->ennemy.count % 3 == 1 && m->ennemy.is_dead == 0)
				x = 11;
			else
			{
				x = 12;
				m->ennemy.is_dead = 1;
			}
			draw_ennemy(w, m, x);
		}
		x++;
	}
}
