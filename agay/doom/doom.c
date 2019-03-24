/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 17:18:10 by agay              #+#    #+#             */
/*   Updated: 2019/03/23 20:03:38 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	img_clear(t_mlx *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < PI_Y)
	{
		x = 0;
		while (x < PI_X)
		{
			mlx->data[y * PI_X + x] = 0x000000;
			x++;
		}
		y++;
	}
}

void	draw(t_mlx *mlx, t_doom doom)
{
	img_clear(mlx);	
	doom.x = doom.vx1;
	doom.x1 = doom.vx2;
	doom.y = doom.vy1;
	doom.y1 = doom.vy2;
	doom.tx1 = doom.vx1 - doom.cx;
	doom.ty1 = doom.vy1 - doom.cy;
	doom.tx2 = doom.vx2 - doom.cx;
	doom.ty2 = doom.vy2 - doom.cy;
	doom.tz1 = doom.tx1 * cos(doom.a) + doom.ty1 * sin(doom.a);
	doom.tz2 = doom.tx2 * cos(doom.a) + doom.ty2 * sin(doom.a);
	doom.tx1 = doom.tx1 * sin(doom.a) - doom.ty1 * cos(doom.a);
	doom.tx2 = doom.tx2 * sin(doom.a) - doom.ty2 * cos(doom.a);
	doom.x = doom.tx1;
	doom.x1 = doom.tx2;
	doom.y = doom.
	draw_utility(mlx, doom, 0xFF00FF);
	doom.dx1 = -doom.tx1 * 16 / doom.tz1;
	doom.dx2 = -doom.tx2 * 16 / doom.tz2;
	doom.dy1a = -250 / doom.tz1;
	doom.dy1b = 250 / doom.tz1;
	doom.dy2a = -250 / doom.tz2;
	doom.dy2b = 250 / doom.tz2;
	doom.x = 250 + doom.dx1;
	doom.x1 = 250 + doom.dx2;
	doom.y = 250 + doom.dy1a;
	doom.y1 = 250 + doom.dy2a;
	draw_utility(mlx, doom, 0xFFFFFF);
	doom.x = 250 + doom.dx1;
	doom.y = 250 + doom.dy1b;
	doom.x1 = 250 + doom.dx2;
	doom.y1 = 250 + doom.dy2b;
	draw_utility(mlx, doom, 0xFFFFFF);
	doom.x1 = 250 + doom.dx1;
	doom.y = 250 + doom.dy1a;
	doom.y1 = 250 + doom.dy1b;
	draw_utility(mlx, doom, 0xFF0000);
	doom.x1 = 250 + doom.dx2;
	doom.x = 250 + doom.dx2;
	doom.y = 250 + doom.dy2a;
	doom.y1 = 250 + doom.dy2b;
	draw_utility(mlx, doom, 0xFF0000);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

int		main(void)
{
	t_doom	doom;
	t_mlx	mlx;
	void	*tab[2];

	doom.cx = 250;
	doom.cy = 250;
	doom.vx1 = 270;
	doom.vx2 = 270;
	doom.vy1 = 220;
	doom.vy2 = 270;
	doom.a = 90;
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
