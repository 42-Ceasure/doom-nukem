/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:14:09 by agay              #+#    #+#             */
/*   Updated: 2019/06/13 15:49:56 by ochaar           ###   ########.fr       */
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
	if (PH > -1 && m->player.switching == 0 && m->sprite[PH].take == 1)
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
	else if (m->sprite[PH].take == 1)
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
	
	tmp.v1x = m->sprite[x].sx - PL_X;
	tmp.v1y = m->sprite[x].sy - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	tmp.x1 = WIDTH / 2 - (tmp.t1x * tmp.xscale1 + (m->sprite[x].w / 2
		* m->sprite[x].range));
	if (ft_strcmp(m->sprite[x].type, "decor") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprite[x].sector].ceiling
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - 10;
	if (ft_strcmp(m->sprite[x].type, "item") == 0 || ft_strcmp(m->sprite[x].type, "ennemy") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprite[x].sector].floor
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - 10;
	tmp.diffx = fabs(m->player.coor.x - m->sprite[x].sx);
	tmp.diffy = fabs(m->player.coor.y - m->sprite[x].sy);
	m->sprite[x].range = sqrt((tmp.diffx * tmp.diffx) + (tmp.diffy * tmp.diffy)) / 10;
	m->sprite[x].range = 1 / m->sprite[x].range;
	if (m->sprite[x].range > 1)
		m->sprite[x].range = 1;
	return (tmp);
}

int     cross(double x1, double x2, double x3, double x4, double y1, double y2, double y3, double y4)
{
    double      a1;
    double      b1;
    double      a2;
    double      b2;
    double      res;

	res = 0.0;
    if (x1 != x2 && x4 != x3)
    {
        a1 = (y2 - y1) / (x2 - x1);
        a2 = (y4 - y3) / (x4 - x3);
        if (a1 == a2)
            return (0);
        b1 = y1 - (a1 * x1);
        b2 = y3 - (a2 * x3);
        res = (b2 - b1) / (a1 - a2);
        if (((res >= x1 && res <= x2) || (res >= x2 && res <= x1))
			&& ((res > x3 && res < x4) || (res > x4 && res < x3)))
            return (1);
    }
    else
    {
        if (x1 == x2 && x3 == x4)
            return (0);
        else if (x1 == x2)
        {
            a2 = (y4 - y3) / (x4 - x3);
            b2 = y3 - (a2 * x3);
            res = a2 * x1 + b2;
        }
        else if (x3 == x4)
        {
            a1 = (y2 - y1) / (x2 - x1);
            b1 = y1 - (a1 * x1);
            res = a1 * x3 + b1;
        }
        if (((res >= y1 && res <= y2) || (res >= y2 && res <= y1))
			&& ((res > y3 && res < y4) || (res > y4 && res < x3)))
                return (1);
    }
    return (0);
}

void		is_visible(t_map *m, int x, int y, int i)
{
	int		h;
	int		j;
	t_coor	p;

	p.x = x;
	p.y = y;
	j = 0;
	while (j < m->sector_count)
	{
		h = 0;
		while (h < m->sector[j].wall_count)
		{
			if (m->visible[j].wall[h] == 1 && m->sector[j].network[h] < 0)
			{
				if (pointside(p, m->sector[j].dot[h].x , m->sector[j].dot[h].y,
					m->sector[j].dot[h + 1].x, m->sector[j].dot[h + 1].y) <= 0)
					if (cross(m->player.coor.x, x, m->sector[j].dot[h].x, m->sector[j].dot[h + 1].x,
						m->player.coor.y, y, m->sector[j].dot[h].y, m->sector[j].dot[h + 1].y) == 1)
						m->sprite[i].vis = 0;
			}
			h++;
		}
		j++;
	}
}

void		draw_sprite(t_env *w, t_map *m, int x)
{
	t_cal_sprt	data;
	int			y_tex;
	int			x_tex;

	y_tex = 0;
	x_tex = 0;
	if (m->sprite[x].take == 1)
		return;
	data = calcul_sprite(w, m, x);
	m->sprite[x].vis = 1;
	//is_visible(m, m->sprite[x].sx, m->sprite[x].sy, x);
	if (m->sector[m->sprite[x].sector].floor > m->player.coor.z) //verifie si la hauteur du sprite est plus haute que le joueur
		m->sprite[x].vis = 0;
	//remplacer le .floor par un int z une fois que la map sera parse
	if (data.t1z > 0 && m->sprite[x].vis == 1)
	{
		while (y_tex < m->sprite[x].h)
		{
			x_tex = 0;
			while (x_tex < m->sprite[x].w)
			{
				if (m->sprite[x].pix[y_tex * m->sprite[x].w + x_tex] != 0xFF00FF00
					&& (data.y1a >= 0 && data.y1a < HEIGHT) && (data.x1
						>= 0 && data.x1 < WIDTH))
					w->pix[(int)(data.y1a) * WIDTH + (int)(data.x1)]
						= m->sprite[x].pix[y_tex * m->sprite[x].w + x_tex];
				data.x1 += 1 * m->sprite[x].range;
				x_tex++;
			}
			data.x1 -= m->sprite[x].w * m->sprite[x].range;
			data.y1a += 1 * m->sprite[x].range;
			y_tex++;
		}
	}

	// faire du scale avec keep ratio
	// nex_height = m->sprite[x].h * 2;
	// new_width = (nex_height * m->sprite[x].w) / m->sprite[x].h;

	// faire du scale sans keep ratio
	/*nex_height = 200;
	new_width = 200;
	step_x_tex = (float)m->sprite[x].h / (float)nex_height;
	step_y_tex = (float)m->sprite[x].w / (float)new_width; 
	data.y1a = 0;
	data.x1 = 0;
	if (data.t1z > 0 && g == 1)
	{
		while (data.y1a < nex_height)
		{
			x_tex = 0;
			while (data.x1 < new_width)
			{
				if (m->sprite[x].pix[(int)y_tex * m->sprite[x].w + (int)x_tex] != 0xFF00FF00
					&& (data.y1a >= 0 && data.y1a < HEIGHT) && (data.x1 >= 0 && data.x1 < WIDTH))
					w->pix[(int)(data.y1a) * WIDTH + (int)(data.x1)] = m->sprite[x].pix[(int)y_tex
						* m->sprite[x].w + (int)x_tex];
				data.x1 += 1;
				x_tex += step_y_tex;
			}
			data.x1 -= new_width;
			data.y1a += 1;
			y_tex += step_x_tex;
		}
	}*/
}

void		draw_ennemy(t_env *w, t_map *m, int x)
{
	double	diffx;
	double	diffy;

	diffx = m->player.coor.x - m->sprite[x].sx;
	diffy = m->player.coor.y - m->sprite[x].sy;
	m->sprite[5].sx += diffx * 0.005;
	m->sprite[5].sy += diffy * 0.005;
	m->sprite[6].sx += diffx * 0.005;
	m->sprite[6].sy += diffy * 0.005;
	draw_sprite(w, m, x);
}
