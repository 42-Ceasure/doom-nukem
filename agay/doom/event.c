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

	mlx = tab[0];
	doom = tab[1];
	if (key == 13)
	{		
		doom->cx = doom->cx + cos(doom->a);
		doom->cy = doom->cy - sin(doom->a);
	}
	else if (key == 1)
	{
		doom->cx = doom->cx - cos(doom->a);
		doom->cy = doom->cy + sin(doom->a);
	}
	else if (key == 0)
		doom->a = doom->a + 0.1;
	else if (key == 2)
		doom->a = doom->a - 0.1;
	draw(mlx, *doom);
	return (1);
}
