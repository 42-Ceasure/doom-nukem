/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:14:09 by agay              #+#    #+#             */
/*   Updated: 2019/06/07 16:14:32 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		set_fire(t_env *w, t_map *m)
{
	m->player.refresh = m->weap[PH].recoil * 2;
	m->yaw = vmid(m->yaw - m->weap[PH].dispertion, -4, 4);
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
		m->player.firing = 0;
	}
}

void		hand(t_env *w, t_map *m)
{
	if (PH > -1 && m->player.switching == 0)
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
	else
	{
		safe_sprite_to_screen(w, m->weap[PH].sprt[0], m->weap[PH].sprt[0].sx,
			m->weap[PH].sprt[0].sy + m->player.switching);
	}
	if (m->player.switching > 0)
		m->player.switching = m->player.switching - 10;
}

t_cal_sprt	calcul_sprite(t_env *w, t_map *m, int x)
{
	t_cal_sprt	tmp;

	//printf("%f\n", m->sector[0].dot[0].x);
	tmp.v1x = m->sprite[x].sx - PL_X;
	tmp.v1y = m->sprite[x].sy - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	tmp.x1 = WIDTH / 2 - (int)(tmp.t1x * tmp.xscale1);
	tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprite[x].sector].floor
		- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - 10;
	tmp.diffx = fabs(m->player.coor.x - m->sprite[x].sx);
	tmp.diffy = fabs(m->player.coor.y - m->sprite[x].sy);
	return (tmp);
}

void		sprite(t_env *w, t_map *m, int x)
{
	t_cal_sprt	data;
	int			d;
	int			i;
	int			g;		//variable booleen pour afficher sprite

	d = 0;
	data = calcul_sprite(w, m, x);
	m->sprite[x].range = sqrt((data.diffx * data.diffx) + (data.diffy * data.diffy)) / 10;
	m->sprite[x].range = 1 / m->sprite[x].range;
	if (m->sprite[x].range > 1)
		m->sprite[x].range = 1;
	g = 1;
    //if (z > m->sector[m->player.sector].ceiling)		illogique?
    //    g = 0;
/*	i = 0;
    while (i < m->sector_count)
    {
        while (h < m->sector[i].wall_count)
        {
            if (m->visible[i].wall[h] == 1 && m->sector[i].network[h] < 0)
                if (pointside(p, m->sector[i].dot[h].x , m->sector[i].dot[h].y, m->sector[i].dot[h + 1].x, m->sector[i].dot[h + 1].y) <= 0)
                    g = 0;
            h++;
        }
        h = 0;						sprite visible?
        i++;
    }*/
	if (m->sprite[x].take == 1)
		g = 0;
	if (data.t1z > 0 && g == 1)
	{
		while (d < m->sprite[x].h)
		{
			i = 0;
			while (i < m->sprite[x].w)
			{
				if (m->sprite[x].pix[d * m->sprite[x].w + i] != 0xFF00FF00
					&& (data.y1a >= 0 && data.y1a < HEIGHT) && (data.x1
						>= 0 && data.x1 < WIDTH))
					w->pix[(int)(data.y1a) * WIDTH + (int)(data.x1)]
						= m->sprite[x].pix[d * m->sprite[x].w + i];
				data.x1 += 1 * m->sprite[x].range;
				i++;
			}
			data.x1 -= m->sprite[x].w * m->sprite[x].range;
			data.y1a += 1 * m->sprite[x].range;
			d++;
		}
	}
}
