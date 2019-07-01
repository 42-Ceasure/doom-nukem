/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_ennemy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 13:33:43 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/01 18:22:22 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	is_fall(t_map *m, int x)
{
	double	nxtz;

	m->ennemy[x].height = STAND;
	m->ennemy[x].ground = !m->ennemy[x].fall;
	if (m->ennemy[x].fall == 1)
	{
		m->ennemy[x].move_speed.z = m->ennemy[x].move_speed.z - m->gravity;
		nxtz = m->ennemy[x].coor.z + m->ennemy[x].move_speed.z;
		if (m->ennemy[x].move_speed.z < 0 && nxtz < m->sector[m->ennemy[x].sector].floor + m->ennemy[x].height)
		{
			m->ennemy[x].coor.z = m->sector[m->ennemy[x].sector].floor + m->ennemy[x].height;
			m->ennemy[x].move_speed.z = 0;
			m->ennemy[x].fall = 0;
			m->ennemy[x].ground = 1;
		}
		else if (m->ennemy[x].move_speed.z > 0 && nxtz > m->sector[m->ennemy[x].sector].ceiling)
		{
			m->ennemy[x].move_speed.z = 0;
			m->ennemy[x].fall = 1;
		}
		if (m->ennemy[x].fall == 1)
		{
			m->ennemy[x].coor.z = m->ennemy[x].coor.z + m->ennemy[x].move_speed.z;
			m->ennemy[x].moving = 1;
		}
	}
}

void move_ennemy(double dx, double dy, t_map *m, int x)
{
	int s;
	t_intersect i;
	t_coor coor;
	

	i.x1 = m->ennemy[x].coor.x;
	i.y1 = m->ennemy[x].coor.y;
	i.x2 = m->ennemy[x].coor.x + dx;
	i.y2 = m->ennemy[x].coor.y + dy;
	s = 0;
	while (s < m->sector[m->ennemy[x].sector].wall_count)
	{
		i.x3 = m->sector[m->ennemy[x].sector].dot[s].x;
		i.y3 = m->sector[m->ennemy[x].sector].dot[s].y;
		i.x4 = m->sector[m->ennemy[x].sector].dot[s + 1].x;
		i.y4 = m->sector[m->ennemy[x].sector].dot[s + 1].y;
		coor.x = i.x2;
		coor.y = i.y2;
		if(m->sector[m->ennemy[x].sector].network[s] >= 0  
		&& intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->ennemy[x].sector = m->sector[m->ennemy[x].sector].network[s];
			break;
		}
		s++;
	}
	m->ennemy[x].coor.x = m->ennemy[x].coor.x + dx;
	m->ennemy[x].coor.y = m->ennemy[x].coor.y + dy;
}

void		is_moving_enne(t_map *m, int x)
{
	int s;
	t_intersect i;
	t_coor		coor;

	s = 0;
	i.x1 = m->ennemy[x].coor.x;
	i.y1 = m->ennemy[x].coor.y;
	i.x2 = m->ennemy[x].coor.x + m->ennemy[x].move_speed.x;
	i.y2 = m->ennemy[x].coor.y + m->ennemy[x].move_speed.y;
	coor.x = i.x2;
	coor.y = i.y2;
	i.dx = m->ennemy[x].move_speed.x;
	i.dy = m->ennemy[x].move_speed.y;
	while (s < m->sector[m->ennemy[x].sector].wall_count)
	{
		i.x3 = m->sector[m->ennemy[x].sector].dot[s].x;
		i.y3 = m->sector[m->ennemy[x].sector].dot[s].y;
		i.x4 = m->sector[m->ennemy[x].sector].dot[s + 1].x;
		i.y4 = m->sector[m->ennemy[x].sector].dot[s + 1].y;
		if(intersectbox(i) 
		&& pointside(coor, i.x3, i.y3, i.x4, i.y4) <= 0)
		{
			m->ennemy[x].hole_low = 9e9;
			m->ennemy[x].hole_high = -9e9;
			if (m->sector[m->ennemy[x].sector].network[s] >= 0)
			{
				m->ennemy[x].hole_low = vmax(m->sector[m->ennemy[x].sector].floor, m->sector[m->sector[m->ennemy[x].sector].network[s]].floor);
				m->ennemy[x].hole_high = vmin(m->sector[m->ennemy[x].sector].ceiling, m->sector[m->sector[m->ennemy[x].sector].network[s]].ceiling);
			}
			if (m->ennemy[x].hole_high < m->ennemy[x].coor.z + HEADMARGIN
			|| m->ennemy[x].hole_low > m->ennemy[x].coor.z - m->ennemy[x].height + 10)
			{
				i.xd = m->sector[m->ennemy[x].sector].dot[s + 1].x - m->sector[m->ennemy[x].sector].dot[s].x;
				i.yd = m->sector[m->ennemy[x].sector].dot[s + 1].y - m->sector[m->ennemy[x].sector].dot[s].y;
				m->ennemy[x].move_speed.x = i.xd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->ennemy[x].move_speed.y = i.yd * (i.dx * i.xd + i.dy * i.yd) / (i.xd * i.xd + i.yd * i.yd);
				m->ennemy[x].moving = 0;
			}
			/*if (is_on_a_map_dot(m, m->ennemy[x].sector) == -1)
			{
				m->ennemy[x].move_speed.x = 0;
				m->ennemy[x].move_speed.y = 0;
			}*/
		}
		s++;
	}
	move_ennemy(m->ennemy[x].move_speed.x, m->ennemy[x].move_speed.y, m, 0);
	m->ennemy[x].fall = 1;
}
