/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 10:54:39 by agay              #+#    #+#             */
/*   Updated: 2019/04/01 16:01:51 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	*intersection(t_doom doom, double **xy)
{
	double		a1;
	double		b1;

	a1 = doom.wslope - doom.rslope;
	b1 = doom.orop - doom.orow;
	xy[0][0] = b1 / a1;
	xy[0][1] = doom.rslope * xy[0][0] + doom.orop;
	return (*xy);
}

void	set_wall(t_mlx *mlx, double	hight, int x)
{
	int        y;

	y = 0;
	while (y < (PI_Y - hight) / 2)
	{
		mlx->data[y * PI_X + x] = 0x1E7FCB;
		y++;
	}
	while (y < (PI_Y + hight) / 2)
	{
		mlx->data[y * PI_X + x] = 0xFFFFFF;
		y++;
	}
	while (y < PI_Y)
	{
		mlx->data[y * PI_X + x] = 0x4E3D28;
		y++;
	}
}

int		get_angle_quadrant(double angle)
{
	if (angle >= 0 * M_PI / 180 && angle < 90 * M_PI / 180)
		return (1);
	else if (angle >= 90 * M_PI / 180 && angle < 180 * M_PI / 180)
		return (2);
	else if (angle >= 180 * M_PI / 180 && angle < 270 * M_PI / 180)
		return (3);
	else if (angle >= 270 * M_PI / 180 && angle < 360 * M_PI / 180)
		return (4);
	return (0);
}

int		get_ray_quadrant(t_doom doom)
{
	if (doom.diffx > 0)
	{
		if (doom.diffy > 0)
			return (2);
		else 
			return (1);
	}
	else
	{
		if (doom.diffy > 0)
			return (2);
		else
			return (2);
	}
}

void	draw(t_mlx *mlx, t_doom doom, t_map m)
{
	double	*xy;
	double	*xy1;
	int		i;
	int		x;
	int		color;

	xy = NULL;
	xy1 = NULL;
	x = 0;
	color = 0xFFFFFF;
	if ((xy = malloc(sizeof(double) * 2)) == NULL)
		return ;
	if ((xy1 = malloc(sizeof(double) * 2)) == NULL)
		return ;
	mlx_pixel_put(mlx->mlx, mlx->win, m.player.coor.x * 20 + 100, m.player.coor.y * 20 + 100, 0xFF0000);
	doom.save = m.player.angle;
	//m.player.angle += 30 * M_PI / 180;
	while (x < PI_X)
	{
		doom.rslope = tan(m.player.angle);
		doom.orop = m.player.coor.y - m.player.coor.x * doom.rslope;
		i = 0;
		while (i < 4)
		{
			doom.wslope = (m.sector->dot[i + 1].y - m.sector->dot[i].y) / (m.sector->dot[i + 1].x - m.sector->dot[i].x);
			if (m.sector->dot[i + 1].x - m.sector->dot[i].x == 0)
				doom.wslope = 999999.999999;
			doom.orow = m.sector->dot[i].y - m.sector->dot[i].x * doom.wslope;
			intersection(doom, &xy1);
			doom.diffx = m.player.coor.x - xy[0];
			doom.diffy = m.player.coor.y - xy[1];	
			if (get_ray_quadrant(doom) == get_angle_quadrant(m.player.angle))
			{
				if (doom.dist == -42)
					doom.dist = (fabs(doom.diffx) > fabs(doom.diffy)) ? doom.diffx / sin(m.player.angle) : doom.diffy / cos(m.player.angle);
				else
					doom.dist1 = (fabs(doom.diffx) > fabs(doom.diffy)) ? doom.diffx / sin(m.player.angle) : doom.diffy / cos(m.player.angle);
				if (doom.dist1 != -42 && doom.dist1 < doom.dist)
				{
					doom.dist = doom.dist1;
					xy = xy1;
				}
			}
			i++;
		}
		mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFFFFF);
		x++;
		m.player.angle = m.player.angle - doom.ar;
	}
	free(xy);
	//mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
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
	m->player.angle = (double)m->player.angle * M_PI / 180;
	doom.fov = (PI_X / 2) / tan(30 * M_PI / 180);
	doom.ar = (double)((60 * M_PI / 180) / PI_X);
	doom.dist = -42;
	doom.dist1 = -42;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, PI_X, PI_Y, "DOOm");
	mlx.img = mlx_new_image(mlx.mlx, PI_X, PI_Y);
	mlx.data = (int *)mlx_get_data_addr(mlx.img, &mlx.bits, &mlx.size, &mlx.endian);
	tab[0] = &mlx;
	tab[1] = &doom;
	tab[2] = m;
	draw(&mlx, doom, *m);
	mlx_key_hook(mlx.win, key, tab);
	mlx_loop(mlx.mlx);
}
