/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 11:42:46 by agay              #+#    #+#             */
/*   Updated: 2019/03/21 19:03:18 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	bresenham2(t_mlx *mlx, int *size, t_doom doom, int color)
{
	int		i;

	i = 1;
	size[4] = size[1] / 2;
	while (i++ <= size[1])
	{
		doom.y += size[3];
		size[4] += size[0];
		if (size[4] >= size[1])
		{
			size[4] -= size[1];
			doom.x += size[2];
		}
		mlx->data[(int)doom.y * PI_X + (int)doom.x] = color;
	}
}

void	bresenham(t_mlx *mlx, int *size, t_doom doom, int color)
{
	int		i;

	i = 1;
	mlx->data[(int)doom.y * PI_X + (int)doom.x] = color;
	if (size[0] > size[1])
	{
		size[4] = size[0] / 2;
		while (i++ <= size[0])
		{
			doom.x += size[2];
			size[4] += size[1];
			if (size[4] >= size[0])
			{
				size[4] -= size[0];
				doom.y += size[3];
			}
			mlx->data[(int)doom.y * PI_X + (int)doom.x] = color;
		}
	}
	else
		bresenham2(mlx, size, doom, color);
}

void	draw_utility(t_mlx *mlx, t_doom doom, int color)
{
	int		size[5];

	if (doom.x1 < 0 || doom.x1 > PI_X)
		doom.x1 = (doom.x1 < 0) ? 0 : PI_X;
	if (doom.y1 < 0 || doom.y1 > PI_X)
		doom.y1 = (doom.y1 < 0) ? 0 : PI_Y;
	if (doom.x < 0 || doom.x > PI_X)
		doom.x = (doom.x < 0) ? 0 : PI_X;
	if (doom.y < 0 || doom.y > PI_X)
		doom.y = (doom.y < 0) ? 0 : PI_Y;
	size[0] = doom.x1 - doom.x;
	size[1] = doom.y1 - doom.y;
	size[2] = (size[0] > 0) ? 1 : -1;
	size[3] = (size[1] > 0) ? 1 : -1;
	size[0] = abs(size[0]);
	size[1] = abs(size[1]);
	bresenham(mlx, size, doom, color);
}
