/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 10:54:39 by agay              #+#    #+#             */
/*   Updated: 2019/03/25 21:03:32 by agay             ###   ########.fr       */
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

double	*intersection(double rslope, t_doom doom, double **xy, t_map *m)
{
	double	b1;

	b1 = (m->player.coor.x - doom.x) * doom.wslope + (doom.y - m->player.coor.y);
	xy[0][0] = b1 / (doom.wslope - rslope) + m->player.coor.x;
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

void	draw(t_mlx *mlx, t_doom doom, t_map *m)
{
	int		x;
	double	*xy;
	double	rslope;

	x = 0;
	xy = NULL;
	printf("player x = %f, y = %f, angle = %f\n", m->player.coor.x, m->player.coor.y, m->player.angle);
	if ((xy = malloc(sizeof(double) * 2)) == NULL)
		return ;
	img_clear(mlx);
	mlx->data[(int)m->player.coor.y * PI_X + (int)m->player.coor.x] = 0xFF0000;
	draw_utility(mlx, doom, 0xFF0000);
	doom.wslope = (m->sector->dot[1].y - m->sector->dot[0].y) / (m->sector->dot[1].x - m->sector->dot[0].x);
	doom.save = m->player.angle;
	m->player.angle = m->player.angle + (30 * M_PI / 180);
	while (x != PI_X)
	{
		rslope = tan(m->player.angle);
		intersection(rslope, doom, &xy, m);
		doom.diffx = m->player.coor.x - xy[0];
		doom.diffy = m->player.coor.y - xy[1];
		doom.dist = (fabs(doom.diffx) > fabs(doom.diffy)) ? doom.diffx / cos(m->player.angle)
		: doom.diffy / sin(m->player.angle);
		doom.dist *= cos(doom.save - m->player.angle);
		if (doom.dist == 0)
			doom.dist = 1;
		doom.wallh = doom.fov / doom.dist;
		set_wall(mlx, doom, x);
		m->player.angle -= doom.ar;
		x++;
	}
	m->player.angle = doom.save;
	free(xy);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	set_basic_run(t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->section_number = 0;
	m->dots_count = 0;
	m->sector_count = 0;
	m->map_name = "test";
	m->map_path = "maps/test.dn3d";
	m->dot = NULL;
	m->sector = NULL;
	if (quick_look(m) == -1)
		write(1, "error map measure\n", 19);
	if (do_parse(m) == -1)
		write(1, "error on map collect\n", 22);
}

void	set_advanced_run(char **av, t_map *m)
{
	set_basic_run(m);
	if ((ft_strcmp(av[1], "-recap_parsing") == 0) && av[2] != NULL)
		recap_parsing(m, av);
	else
	{
		ft_putendl("\nThis part of the program is curently in development.");
		ft_putendl("the only command usable now is \"-recap_parsing\" with args :");
		ft_putendl("  \"map_list_general\"  \"map_list_dots\"  \"map_list_sectors\"");
		ft_putendl("  \"map_list_sector all <attribut>\"  \"player_list_vars\"\n");
		ft_putendl("possibles <attribut> are \"general\" \"dots\" \"network\"");
	}
	free(m);
}

int		main(int ac, char **av)
{
	t_doom	doom;
	t_mlx	mlx;
	t_map	*m;
	void	*tab[3];

	if ((m = (t_map *)malloc(sizeof(t_map))) == NULL)
		return (0);
	if (ac == 1)
		set_basic_run(m);
	else
	{
		set_advanced_run(av, m);
		return (0);
	}
	printf("angle(main) :%f\n", m->player.angle);
	m->player.angle = m->player.angle * M_PI / 180;
	printf("angle corrige (main) :%f\n", m->player.angle);
	doom.fov = (PI_X / 2) / tan(30 * M_PI / 180);
	doom.ar = (double)(60 * M_PI / 180) / PI_X;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, PI_X, PI_Y, "DOOm");
	mlx.img = mlx_new_image(mlx.mlx, PI_X, PI_Y);
	mlx.data = (int *)mlx_get_data_addr(mlx.img, &mlx.bits, &mlx.size, &mlx.endian);
	tab[0] = &mlx;
	tab[1] = &doom;
	tab[2] = m;
	draw(&mlx, doom, m);
	mlx_key_hook(mlx.win, key, tab);
	mlx_loop(mlx.mlx);
}
