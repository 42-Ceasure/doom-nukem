/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 10:54:39 by agay              #+#    #+#             */
/*   Updated: 2019/03/25 19:16:16 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	img_clear(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < PI_Y / 2)
	{
		x = 0;
		while (x < PI_X)
		{
			mlx->data[y * PI_X + x] = 0x00BFFF;
			x++;
		}
		y++;
	}
	y = PI_Y;
	x = 0;
	while (y >= PI_Y / 2)
	{
		x = 0;
		while (x < PI_X)
		{
			mlx->data[y * PI_X + x] = 0x808080;
			x++;
		}
		y--;
	}
}

double	*intersection(double rslope, t_doom doom, double **xy)
{
	double	b1;

	b1 = (doom.cx - doom.x) * doom.wslope + (doom.y - doom.cy);
	xy[0][0] = b1 / (doom.wslope - rslope) + doom.cx;
	xy[0][1] = xy[0][0] * doom.wslope;
	return (*xy);
}

void	set_wall(t_mlx *mlx, t_doom doom, int x)
{
	int		y;

	y = PI_Y / 2;
	while (y < (PI_Y / 2) + (doom.wallh / 2))
	{
		mlx->data[y * PI_X + x] = 0xFFFFFF;
		y++;
	}
	y = PI_Y / 2;
	while (y > (PI_Y / 2) - (doom.wallh / 2))
	{
		mlx->data[y * PI_X + x] = 0xFFFFFF;
		y--;
	}
}

void	draw(t_mlx *mlx, t_doom doom)
{
	int		x;
	int		i;
	double	*xy;
	double	rslope;

	x = 0;
	xy = NULL;
	i = 0;
	if ((xy = malloc(sizeof(double) * 2)) == NULL)
		return ;
	img_clear(mlx);
	mlx->data[(int)doom.cy * PI_X + (int)doom.cx] = 0xFF0000;
	draw_utility(mlx, doom, 0xFF0000);
	doom.wslope = (doom.y1 - doom.y) / (doom.x1 - doom.x);
	doom.save = doom.a;
	doom.a = doom.a + (30 * M_PI / 180);
	while (x != PI_X)
	{
		rslope = tan(doom.a);
		intersection(rslope, doom, &xy);
		doom.diffx = doom.cx - xy[0];
		doom.diffy = doom.cy - xy[1];
		doom.dist = (fabs(doom.diffx) > fabs(doom.diffy)) ? doom.diffx / cos(doom.a)
		: doom.diffy / sin(doom.a);
		doom.dist *= cos(doom.save - doom.a);
		if (doom.dist == 0)
			doom.dist = 1;
		doom.wallh = doom.fov / doom.dist;
		set_wall(mlx, doom, x);
		doom.a -= doom.ar;
		x++;
	}
	free(xy);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		main(void)
{
	t_doom	doom;
	t_mlx	mlx;
	void	*tab[2];

	doom.cx = 3;
	doom.cy = 3;
	doom.x = 0;
	doom.y = 0;
	doom.x1 = 6;
	doom.y1 = 0;
	doom.a = 90 * M_PI / 180;
	doom.fov = (PI_X / 2) / tan(30 * M_PI / 180);
	doom.ar = (double)(60 * M_PI / 180) / PI_X;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, PI_X, PI_Y, "DOOm");
	mlx.img = mlx_new_image(mlx.mlx, PI_X, PI_Y);
	mlx.data = (int *)mlx_get_data_addr(mlx.img, &mlx.bits, &mlx.size, &mlx.endian);
	tab[0] = &mlx;
	tab[1] = &doom;
	draw(&mlx, doom);
	mlx_key_hook(mlx.win, key, tab);
	mlx_loop(mlx.mlx);
}
