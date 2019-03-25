/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:44:39 by agay              #+#    #+#             */
/*   Updated: 2019/03/22 14:28:02 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		key(int key, void **tab)
{
	t_mlx	*mlx;
	t_doom	*doom;
	t_map	*m;

	mlx = tab[0];
	doom = tab[1];
	m = tab[2];
	if (key == 13)
	{		
		m->player.coor.x = m->player.coor.x + cos(m->player.angle);
		m->player.coor.y = m->player.coor.y - sin(m->player.angle);
	}
	else if (key == 1)
	{
		m->player.coor.x = m->player.coor.x - cos(m->player.angle);
		m->player.coor.y = m->player.coor.y + sin(m->player.angle);
	}
	else if (key == 0)
		m->player.angle = m->player.angle + 0.1;
	else if (key == 2)
		m->player.angle = m->player.angle - 0.1;
	draw(mlx, *doom, m);
	return (1);
}
