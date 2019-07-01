/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:19:02 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/01 20:28:36 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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

/*void		is_visible(t_map *m, int x, int y, int i)
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
}*/

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
	if (ft_strcmp(m->sprite[m->sprt[x].index].type, "item") == 0
		|| ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - (m->sprite[m->sprt[x].index].h * tmp.zoom * ratio);
	return (tmp);
}

void		draw_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	data;
	//int			tmpix;
	double		range;

	if (ft_strcmp(m->sprite[m->sprt[x].index].type, "ennemy") != 0)
	{
		data = calcul_sprite(w, m, x, ratio);
		range = data.zoom;
	}
	/*else
	{
		data = calcul_sprite_ennemy(w, m, x, ratio);
		range = data.zoom;
		tmpix = get_tmpix_scaled(w, m->sprite[x], (m->sprite[x].w * range * ratio), 0, (WIDTH / 2 - (int)data.x1), (HEIGHT / 2 - (int)data.y1a));
		if (m->player.firing == 1 && m->weap[PH].range * m->ennemy.range >= 200)
		{
			if ((data.x1 <= WIDTH / 2 && data.x1 >= WIDTH / 2 - m->sprite[x].w * range * ratio)
				&& (data.y1a <= HEIGHT / 2 && data.y1a >= HEIGHT / 2 - m->sprite[x].h * range * ratio)
					&& m->sprite[x].pix[tmpix] != 0xFF00FF00 && m->ennemy.is_dead != 1)
			{
				if (m->weap[PH].ammo == 1)
					m->ennemy.dead = 1;
				else
				{
					m->ennemy.nb_ammo++;
					m->ennemy.touche = 1;
					Mix_PlayChannel(6, m->ennemy.dammage, 0);
					if (m->ennemy.nb_ammo % 4 == 0)
						m->ennemy.dead = 1;
				}
			}
		}
		m->player.firing = 0;
	}*/
	//is_visible(m, m->sprite[x].sx, m->sprite[x].sy, x);
	/*if (m->sector[m->ennemy.sector].floor > m->player.coor.z) //verifie si la hauteur du sprite est plus haute que le joueur
		m->sprite[x].vis = 0;*/
	//remplacer le .floor par un int z une fois que la map sera parse
	if (data.t1z > 0 && m->sprt[x].vis == 1)
		final_sprite_to_screen(w, m->sprite[m->sprt[x].index], data.x1, data.y1a, m->sprite[m->sprt[x].index].w * range * ratio, 0);
}

void	swipe_sprite(t_env *w, t_map *m, int x)
{
	if (w->dtime.walk == 0)
		m->k++;
	if (m->ennemy[x].range < 1)
	{
		if (m->k % 3 == 0)
			m->ennemy[x].index = 5;
		if (m->k % 3 == 1)
			m->ennemy[x].index = 6;
		if (m->k % 3 == 2)
			m->ennemy[x].index = 7;
	}
	else
	{
		if (m->k % 2 == 0)
		{
			m->ennemy[x].index = 8;
			m->i = 1;
		}
		else
		{
			m->ennemy[x].index = 9;
			if (m->i == 1)
			{
				m->player.hp -= 10;
				m->i = 0;
			}
		}
	}
	if (m->ennemy[x].touche == 1)
	{
		m->ennemy[x].index = 10;
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
		draw_sprite(w, m, x, 1);
		if (m->sprt[x].range >= 2 && ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0
			&& m->sprt[x].vis == 1 && m->player.hp < 100)
		{
			m->player.hp += 30;
			m->sprt[x].vis = 0;
			printf("%d\n", x);
		}
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		if (m->ennemy[x].dead == 0)
			swipe_sprite(w, m, x);
		else
		{
			if (w->dtime.dead == 0)
				m->ennemy[x].count++;
			if (m->ennemy[x].count % 3 == 0 && m->ennemy[x].is_dead == 0)
				m->ennemy[x].index = 10;
			else if (m->ennemy[x].count % 3 == 1 && m->ennemy[x].is_dead == 0)
				m->ennemy[x].index = 11;
			else
			{
				m->ennemy[x].index = 12;
				m->ennemy[x].is_dead = 1;
			}
			draw_ennemy(w, m, x, 5);
		}
		x++;
	}
}
