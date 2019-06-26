/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ennemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 13:33:43 by ochaar            #+#    #+#             */
/*   Updated: 2019/06/22 18:09:58 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	is_fall(t_map *m)
{
	double	nxtz;

	m->ennemy.height = STAND;
	m->ennemy.ground = !m->ennemy.fall;
	if (m->ennemy.fall == 1)
	{
		m->ennemy.move_speed.z = m->ennemy.move_speed.z - m->gravity;
		nxtz = m->ennemy.coor.z + m->ennemy.move_speed.z;
		if (m->ennemy.move_speed.z < 0 && nxtz < m->sector[m->ennemy.sector].floor + m->ennemy.height)
		{
			m->ennemy.coor.z = m->sector[m->ennemy.sector].floor + m->ennemy.height;
			m->ennemy.move_speed.z = 0;
			m->ennemy.fall = 0;
			m->ennemy.ground = 1;
		}
		else if (m->ennemy.move_speed.z > 0 && nxtz > m->sector[m->ennemy.sector].ceiling)
		{
			m->ennemy.move_speed.z = 0;
			m->ennemy.fall = 1;
		}
		if (m->ennemy.fall == 1)
		{
			m->ennemy.coor.z = m->ennemy.coor.z + m->ennemy.move_speed.z;
			m->ennemy.moving = 1;
		}
	}
}

void move_ennemy(double dx, double dy, t_map *m)
{
	int s;
	t_intersect i;
	t_coor coor;
	

	i.x1 = m->ennemy.coor.x;
	i.y1 = m->ennemy.coor.y;
	i.x2 = m->ennemy.coor.x + dx;
	i.y2 = m->ennemy.coor.y + dy;
	s = 0;
	while (s < m->sector[m->ennemy.sector].wall_count)
	{
		i.x3 = m->sector[m->ennemy.sector].dot[s].x;
		i.y3 = m->sector[m->ennemy.sector].dot[s].y;
		i.x4 = m->sector[m->ennemy.sector].dot[s + 1].x;
		i.y4 = m->sector[m->ennemy.sector].dot[s + 1].y;
		coor.x = i.x2;
		coor.y = i.y2;
		if(m->sector[m->ennemy.sector].network[s] >= 0  
		&& intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->ennemy.sector = m->sector[m->ennemy.sector].network[s];
			break;
		}
		s++;
	}
	m->ennemy.coor.x = m->ennemy.coor.x + dx;
	m->ennemy.coor.y = m->ennemy.coor.y + dy;
}

void		is_moving_enne(t_map *m)
{
	int s;
	t_intersect i;
	t_coor		coor;

	s = 0;
	i.x1 = m->ennemy.coor.x;
	i.y1 = m->ennemy.coor.y;
	i.x2 = m->ennemy.coor.x + m->ennemy.move_speed.x;
	i.y2 = m->ennemy.coor.y + m->ennemy.move_speed.y;
	coor.x = i.x2;
	coor.y = i.y2;
	i.dx = m->ennemy.move_speed.x;
	i.dy = m->ennemy.move_speed.y;
	while (s < m->sector[m->ennemy.sector].wall_count)
	{
		i.x3 = m->sector[m->ennemy.sector].dot[s].x;
		i.y3 = m->sector[m->ennemy.sector].dot[s].y;
		i.x4 = m->sector[m->ennemy.sector].dot[s + 1].x;
		i.y4 = m->sector[m->ennemy.sector].dot[s + 1].y;
		if(intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->ennemy.hole_low = 9e9;
			m->ennemy.hole_high = -9e9;
			if (m->sector[m->ennemy.sector].network[s] >= 0)
			{
				m->ennemy.hole_low = vmax(m->sector[m->ennemy.sector].floor, m->sector[m->sector[m->ennemy.sector].network[s]].floor);
				m->ennemy.hole_high = vmin(m->sector[m->ennemy.sector].ceiling, m->sector[m->sector[m->ennemy.sector].network[s]].ceiling);
			}
			if (m->ennemy.hole_high < m->ennemy.coor.z + HEADMARGIN
			|| m->ennemy.hole_low > m->ennemy.coor.z - m->ennemy.height + KNEEH)
			{
				i.xd = m->sector[m->ennemy.sector].dot[s + 1].x - m->sector[m->ennemy.sector].dot[s].x;
				i.yd = m->sector[m->ennemy.sector].dot[s + 1].y - m->sector[m->ennemy.sector].dot[s].y;
				m->ennemy.move_speed.x = i.xd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->ennemy.move_speed.y = i.yd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->ennemy.moving = 0;
			}
			/*if (is_on_a_map_dot(m, m->ennemy.sector) == -1)
			{
				m->ennemy.move_speed.x = 0;
				m->ennemy.move_speed.y = 0;
			}*/
		}
		s++;
	}
	move_ennemy(m->ennemy.move_speed.x, m->ennemy.move_speed.y, m);
	m->ennemy.fall = 1;
}
