/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handed.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 14:25:59 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/15 14:41:20 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		fire_aim(t_env *w, t_map *m)
{
	if (m->player.handed == 0)
		safe_texture_to_screen(w, m->fire, WIDTH / 2 - m->fire.w / 2,
			HEIGHT / 2 - m->fire.h / 2 + 45);
	else if (m->player.handed == 1 || m->player.handed == 2)
		safe_texture_to_screen(w, m->fire, WIDTH / 2 - m->fire.w / 2,
			HEIGHT / 2 - m->fire.h / 2 + 20);
	safe_sprite_to_screen(w, m->weap[PH].sprt[1], m->weap[PH].sprt[1].sx,
			m->weap[PH].sprt[1].sy + (m->weap[PH].recoil / 1.5));
}

void		set_fire(t_env *w, t_map *m)
{
	int		y;

	y = m->weap[PH].sprt[0].sy + m->weap[PH].recoil;
	m->player.refresh = m->weap[PH].recoil * 2;
	m->yaw = vmid(m->yaw - m->weap[PH].dispertion, -2, 2);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
	PL_A = PL_A + m->weap[PH].dispertion / 2 * w->random;
	if (PH > -1 && m->player.firing)
	{
		if (m->player.aiming == 1)
			fire_aim(w, m);
		else
		{
			if (m->player.handed == 0 || m->player.handed == 2)
				safe_texture_to_screen(w, m->fire, WIDTH / 2 - m->fire.w / 2
					+ 56, HEIGHT / 2 - m->fire.h / 2 + 67);
			else if (m->player.handed == 1)
				safe_texture_to_screen(w, m->fire, WIDTH / 2 - m->fire.w / 2
					+ 45, HEIGHT / 2 - m->fire.h / 2 + 60);
			safe_sprite_to_screen(w, m->weap[PH].sprt[0],
				m->weap[PH].sprt[0].sx, y);
		}
	}
}

void		print_weapon(t_env *w, t_map *m)
{
	int		y;

	y = m->weap[PH].sprt[2].sy + 60 - vabs(m->player.bal / 2);
	if (m->player.aiming == 1)
		safe_sprite_to_screen(w, m->weap[PH].sprt[1], m->weap[PH].sprt[1].sx,
			m->weap[PH].sprt[1].sy);
	else
	{
		if (m->player.moving != 0 && m->player.jump == 0
			&& m->player.refresh == 0)
			safe_sprite_to_screen(w, m->weap[PH].sprt[2],
				m->weap[PH].sprt[2].sx + m->player.bal, y);
		else if (m->player.moving != 0 && m->player.refresh == 0)
			safe_sprite_to_screen(w, m->weap[PH].sprt[2],
				m->weap[PH].sprt[2].sx, m->weap[PH].sprt[2].sy);
		else
			safe_sprite_to_screen(w, m->weap[PH].sprt[0],
				m->weap[PH].sprt[0].sx, m->weap[PH].sprt[0].sy);
	}
}

void		hand(t_env *w, t_map *m)
{
	if (PH > -1 && m->player.switching == 0 && m->player.take[PH] == 1)
	{
		if (m->player.firing == 1)
			set_fire(w, m);
		else
			print_weapon(w, m);
		if (m->player.refresh > 0)
			m->player.refresh--;
	}
	else if (m->player.take[PH] == 1)
	{
		safe_sprite_to_screen(w, m->weap[PH].sprt[0], m->weap[PH].sprt[0].sx,
			m->weap[PH].sprt[0].sy + m->player.switching);
	}
	if (m->player.switching > 0)
		m->player.switching = m->player.switching - 10;
}
