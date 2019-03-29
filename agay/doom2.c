/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/22 10:54:39 by agay              #+#    #+#             */
/*   Updated: 2019/03/29 22:49:51 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

double	*intersection(double rslope, t_doom doom, double **xy, t_map m, t_mlx *mlx)
{
	double	b1;

	b1 = (m.player.coor.x - m.sector->dot[mlx->i].x) * doom.wslope + (m.player.coor.y - m.sector->dot[mlx->i].y);
	xy[0][0] = b1 / (rslope - doom.wslope) + m.player.coor.x;
	xy[0][1] = m.sector->dot[mlx->i].y + (xy[0][0] - m.sector->dot[mlx->i].x) * doom.wslope;
	return (*xy);
}

void	set_wall(t_mlx *mlx, t_doom doom, int x)
{
	int        y;

	y = 0;
	while (y < (PI_Y - doom.wallh) / 2)
	{
		mlx->data[y * PI_X + x] = 0x1E7FCB;
		y++;
	}
	while (y < (PI_Y + doom.wallh) / 2)
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

void	draw(t_mlx *mlx, t_doom doom, t_map m)
{
	int		x;
	double	*xy;
	double	rslope;
	int		color;

	x = 0;
	xy = NULL;
	if ((xy = malloc(sizeof(double) * 2)) == NULL)
		return ;
	//mlx_pixel_put(mlx->mlx, mlx->win, m->sector->dot[0].x * 20 + 100, m->sector->dot[0].y * 20 + 100, 0xFF0000);
	//	//mlx_pixel_put(mlx->mlx, mlx->win,  m->sector->dot[1].x * 20 + 100, m->sector->dot[1].y * 20 + 100, 0xFF0000);
	//		//mlx_pixel_put(mlx->mlx, mlx->win, m->sector->dot[4].x * 20 + 100, m->sector->dot[4].y * 20 + 100, 0xFF0000);
	mlx_pixel_put(mlx->mlx, mlx->win, m.player.coor.x * 20 + 100, m.player.coor.y * 20 + 100, 0xFF0000);
	draw_utility(mlx, doom, 0xFF0000);
	doom.save = m.player.angle;
	m.player.angle = m.player.angle + (30 * M_PI / 180);
	while (x < PI_X)
	{
		if (mlx->i == 0)
			color = 0xFFFFFF;
		else if (mlx->i == 1)
			color = 0xFFb800;
		else if (mlx->i == 2)
			color = 0xFF0000;
		else if (mlx->i == 3)
			color = 0xFF00FF;
		if (m.player.angle == (-1.637094))
		{
			ft_putstr("test");
			mlx->dodo = 1;
		}
		doom.wslope = (m.sector->dot[mlx->i + 1].y - m.sector->dot[mlx->i].y) / (m.sector->dot[mlx->i + 1].x - m.sector->dot[mlx->i].x);
		if (m.sector->dot[mlx->i + 1].x - m.sector->dot[mlx->i].x == 0)
			doom.wslope = 999999.999999;
		rslope = tan(m.player.angle);
		intersection(rslope, doom, &xy, m, mlx);
		//if (mlx->i == 1)
			xy[1] = fabs(xy[1]);
		//if (mlx->dodo == 1)
		//	printf("angle = %f i = %d x = %f, y = %f, wslope = %f, rslope = %f, save = %f\n", m.player.angle, mlx->i, xy[0], xy[1], doom.wslope, rslope, doom.save);
		doom.diffx = (m.player.coor.x - xy[0]);
		doom.diffy = (m.player.coor.y - xy[1]);
		doom.dist = (fabs(doom.diffx) < fabs(doom.diffy)) ? doom.diffx / cos(m.player.angle) : doom.diffy / sin(m.player.angle);
		doom.dist *= cos(doom.save - m.player.angle);
		if (doom.dist == 0)
			doom.dist = 1;
		doom.wallh = fabs(doom.fov / doom.dist);
			printf("h = %f\n", doom.wallh);
		if (xy[0] >= m.sector->dot[mlx->i].x && xy[0] <= m.sector->dot[mlx->i + 1].x)
			set_wall(mlx, doom, x);
			//mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, color);
		else if (m.sector->dot[mlx->i].x > m.sector->dot[mlx->i + 1].x && (xy[0] >= m.sector->dot[mlx->i + 1].x && xy[0] <= m.sector->dot[mlx->i].x))
			set_wall(mlx, doom, x);
			//mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, color);
		else if ((xy[1] >= m.sector->dot[mlx->i].y && xy[1] <= m.sector->dot[mlx->i + 1].y) && xy[0] >= m.sector->dot[mlx->i].x && xy[0] <= m.sector->dot[mlx->i + 1].x)
			set_wall(mlx, doom, x);
			//mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, color);
		else if ((m.sector->dot[mlx->i + 1].x == m.sector->dot[mlx->i].x) && (xy[1] >= m.sector->dot[mlx->i].y && xy[1] <= m.sector->dot[mlx->i + 1].y))
			set_wall(mlx, doom, x);
			//mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, color);
		else if ((m.sector->dot[mlx->i + 1].x == m.sector->dot[mlx->i].x) && (xy[1] >= m.sector->dot[mlx->i + 1].y && xy[1] <= m.sector->dot[mlx->i].y))
			set_wall(mlx, doom, x);
			//mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, color);
		else
			mlx->i++;
		m.player.angle -= doom.ar;
		x++;
	}
	mlx->i = 0;
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
	m->player.angle = m->player.angle * M_PI / 180;
	doom.fov = (PI_X / 2) / tan(30 * M_PI / 180);
	doom.ar = (double)(60 * M_PI / 180) / PI_X;
	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, PI_X, PI_Y, "DOOm");
	mlx.img = mlx_new_image(mlx.mlx, PI_X, PI_Y);
	mlx.data = (int *)mlx_get_data_addr(mlx.img, &mlx.bits, &mlx.size, &mlx.endian);
	doom.x = 0;
	doom.y = 0;
	doom.x1 = 10;
	doom.y1 = 1;
	doom.x2 = 10;
	doom.y2 = 7;
	doom.x3 = 0;
	doom.y3 = 8;
	mlx.i = 0;
	mlx.dodo = 0;
	tab[0] = &mlx;
	tab[1] = &doom;
	tab[2] = m;
	draw(&mlx, doom, *m);
	mlx_key_hook(mlx.win, key, tab);
	mlx_loop(mlx.mlx);
}
