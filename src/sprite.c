/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:14:09 by agay              #+#    #+#             */
/*   Updated: 2019/07/02 12:38:47 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		set_fire(t_env *w, t_map *m)
{
	m->player.refresh = m->weap[PH].recoil * 2;
	// MODIF
	m->yaw = vmid(m->yaw - m->weap[PH].dispertion, -1.5, 1.5);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
	PL_A = PL_A + m->weap[PH].dispertion / 2 * w->random;
	if (PH > -1 && m->player.firing)
	{
		if (m->player.aiming == 1)
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
		else
		{
			if (m->player.handed == 0 || m->player.handed == 2)
				safe_texture_to_screen(w, m->fire, WIDTH / 2 - m->fire.w / 2 + 56,
					HEIGHT / 2 - m->fire.h / 2 + 67);
			else if (m->player.handed == 1)
				safe_texture_to_screen(w, m->fire, WIDTH / 2 - m->fire.w / 2 + 45,
					HEIGHT / 2 - m->fire.h / 2 + 60);
			safe_sprite_to_screen(w, m->weap[PH].sprt[0], m->weap[PH].sprt[0].sx,
					m->weap[PH].sprt[0].sy + m->weap[PH].recoil);
		}
	}
	//m->player.firing = 0;
}

void		hand(t_env *w, t_map *m)
{
	if (PH > -1 && m->player.switching == 0 && m->player.take[PH] == 1)
	{
		if (m->player.firing == 1)
			set_fire(w, m);
		else
		{
			if (m->player.aiming == 1)
				safe_sprite_to_screen(w, m->weap[PH].sprt[1], m->weap[PH].sprt[1].sx,
					m->weap[PH].sprt[1].sy);
			else
			{
				if (m->player.moving != 0 && m->player.jump == 0 && m->player.refresh == 0)
					safe_sprite_to_screen(w, m->weap[PH].sprt[2], m->weap[PH].sprt[2].sx + m->player.bal,
						m->weap[PH].sprt[2].sy + 60 - vabs(m->player.bal / 2));
				else if (m->player.moving != 0 && m->player.refresh == 0)
					safe_sprite_to_screen(w, m->weap[PH].sprt[2], m->weap[PH].sprt[2].sx,
						m->weap[PH].sprt[2].sy);
				else
					safe_sprite_to_screen(w, m->weap[PH].sprt[0], m->weap[PH].sprt[0].sx,
						m->weap[PH].sprt[0].sy);
			}
		}
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

t_cal_sprt	calcul_sprite_ennemy(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	tmp;

	tmp.v1x = m->ennemy[x].coor.x - PL_X;
	tmp.v1y = m->ennemy[x].coor.y - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	tmp.diffx = fabs(m->player.coor.x - m->ennemy[x].coor.x);
	tmp.diffy = fabs(m->player.coor.y - m->ennemy[x].coor.y);
	m->ennemy[x].range = sqrt((tmp.diffx * tmp.diffx) + (tmp.diffy * tmp.diffy)) / 10;
	m->ennemy[x].range = 1 / m->ennemy[x].range;
	if (m->ennemy[x].range > 6)
		m->ennemy[x].range = 6;
	tmp.zoom = m->ennemy[x].range;
	if (m->player.aiming == 1)
		tmp.zoom *= 2;
	tmp.x1 = WIDTH / 2 - (tmp.t1x * tmp.xscale1 + (m->sprite[m->ennemy[x].index].w / 2
		* tmp.zoom * ratio));
	tmp.y1a = HEIGHT / 2 - (int)(yaw((m->ennemy[x].coor.z - m->ennemy[x].height
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - (m->sprite[m->ennemy[x].index].h * tmp.zoom * ratio);
	return (tmp);
}

void		draw_ennemy(t_env *w, t_map *m, int x, int ratio)
{
	double	diffx;
	double	diffy;
	double	diffz;
	t_cal_sprt	data;
	int			tmpix;
	double		range;

	diffx = m->player.coor.x - m->ennemy[x].coor.x;
	diffy = m->player.coor.y - m->ennemy[x].coor.y;
	diffz = m->player.coor.z - m->ennemy[x].coor.z;
	m->ennemy[x].move_speed.x = diffx * 0.005;
	m->ennemy[x].move_speed.y = diffy * 0.005;
	if (m->ennemy[x].dead != 1)
		m->ennemy[x].move_speed.z = diffz * 0.005;
	m->ennemy[x].movespeed = 1;
	data = calcul_sprite_ennemy(w, m, x, ratio);
	range = data.zoom;
	tmpix = get_tmpix_scaled(w, m->sprite[m->ennemy[x].index], (m->sprite[m->ennemy[x].index].w * range * ratio), 0, (WIDTH / 2 - (int)data.x1), (HEIGHT / 2 - (int)data.y1a));
	if (m->player.firing == 1 && m->weap[PH].range * m->ennemy[x].range >= 200)
	{
		if ((data.x1 <= WIDTH / 2 && data.x1 >= WIDTH / 2 - m->sprite[m->ennemy[x].index].w * range * ratio)
			&& (data.y1a <= HEIGHT / 2 && data.y1a >= HEIGHT / 2 - m->sprite[m->ennemy[x].index].h * range * ratio)
				&& m->sprite[m->ennemy[x].index].pix[tmpix] != 0xFF00FF00 && m->ennemy[x].is_dead != 1)
		{
			if (m->weap[PH].ammo == 1)
				m->ennemy[x].dead = 1;
			else
			{
				m->ennemy[x].nb_ammo++;
				m->ennemy[x].touche = 1;
				if (m->ennemy[x].nb_ammo % 4 == 0)
					m->ennemy[x].dead = 1;
			}
			Mix_PlayChannel(6, m->ennemy[x].dammage, 0);
		}
	}
	if (data.t1z > 0)
		final_sprite_to_screen(w, m->sprite[m->ennemy[x].index], data.x1, data.y1a, m->sprite[m->ennemy[x].index].w * range * ratio, 0);
}
