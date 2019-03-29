void	draw(t_mlx *mlx, t_doom doom, t_map m)
{
	int		x;
	double	*xy;
	double	rslope;

	x = 0;
	xy = NULL;
	if ((xy = malloc(sizeof(double) * 2)) == NULL)
		return ;
	//mlx_pixel_put(mlx->mlx, mlx->win, m->sector->dot[0].x * 20 + 100, m->sector->dot[0].y * 20 + 100, 0xFF0000);
	//mlx_pixel_put(mlx->mlx, mlx->win,  m->sector->dot[1].x * 20 + 100, m->sector->dot[1].y * 20 + 100, 0xFF0000);
	//mlx_pixel_put(mlx->mlx, mlx->win, m->sector->dot[4].x * 20 + 100, m->sector->dot[4].y * 20 + 100, 0xFF0000);
	mlx_pixel_put(mlx->mlx, mlx->win, m.player.coor.x * 20 + 100, m.player.coor.y * 20 + 100, 0xFF0000);
	draw_utility(mlx, doom, 0xFF0000);
	doom.save = m.player.angle;
	m.player.angle += 30 * M_PI / 180;
	//m.player.angle = 140 * M_PI / 180;
	while (m.player.angle > 0)
	{
		doom.wslope = (m.sector->dot[mlx->i + 1].y - m.sector->dot[mlx->i].y) / (m.sector->dot[mlx->i + 1].x - m.sector->dot[mlx->i].x);
		if (m.sector->dot[mlx->i + 1].x - m.sector->dot[mlx->i].x == 0)
			doom.wslope = 999999.999999;
		rslope = tan(m.player.angle);
		intersection(rslope, doom, &xy, m, mlx);
		if (doom.wslope == 999999.999999 && m.sector->dot[mlx->i].y < m.sector->dot[mlx->i + 1].y)
		{
			if (xy[1] >= m.sector->dot[mlx->i].y && xy[1] <= m.sector->dot[mlx->i + 1].y)
				mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFFFFF);
		}
		else if (doom.wslope == 999999.999999 && m.sector->dot[mlx->i].y > m.sector->dot[mlx->i + 1].y)
		{
			if (xy[1] >= m.sector->dot[mlx->i + 1].y && xy[1] <= m.sector->dot[mlx->i].y)
				mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFFFFF);
		}
		else if (m.sector->dot[mlx->i].x < m.sector->dot[mlx->i + 1].x && xy[0] >= m.sector->dot[mlx->i].x && xy[0] <= m.sector->dot[mlx->i + 1].x)
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFFFFF);
		else if (m.sector->dot[mlx->i].x > m.sector->dot[mlx->i + 1].x && xy[0] >= m.sector->dot[mlx->i + 1].x && xy[0] <= m.sector->dot[mlx->i].x)
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFFFFF);
		else
			mlx->i++;
		if (mlx->i > 3)
		{
			mlx->i = 0;
			break;
		}
		m.player.angle -= doom.ar;
		//printf("angle = %f\n", m.player.angle);
		ft_putnbr(mlx->i);
		x++;
	}
	free(xy);
}

void	draw(t_mlx *mlx, t_doom doom, t_map m)
{
	int		x;
	double	*xy;
	double	rslope;

	x = 0;
	xy = NULL;
	if ((xy = malloc(sizeof(double) * 2)) == NULL)
		return ;
	//mlx_pixel_put(mlx->mlx, mlx->win, m->sector->dot[0].x * 20 + 100, m->sector->dot[0].y * 20 + 100, 0xFF0000);
	//mlx_pixel_put(mlx->mlx, mlx->win,  m->sector->dot[1].x * 20 + 100, m->sector->dot[1].y * 20 + 100, 0xFF0000);
	//mlx_pixel_put(mlx->mlx, mlx->win, m->sector->dot[4].x * 20 + 100, m->sector->dot[4].y * 20 + 100, 0xFF0000);
	mlx_pixel_put(mlx->mlx, mlx->win, m.player.coor.x * 20 + 100, m.player.coor.y * 20 + 100, 0xFF0000);
	draw_utility(mlx, doom, 0xFF0000);
	doom.save = m.player.angle;
	m.player.angle += (30 * M_PI / 180);
	while (x < PI_X)
	{
		doom.wslope = (m.sector->dot[mlx->i + 1].y - m.sector->dot[mlx->i].y) / (m.sector->dot[mlx->i + 1].x - m.sector->dot[mlx->i].x);
		if (m.sector->dot[mlx->i + 1].x == m.sector->dot[mlx->i].x)
			doom.wslope = 999999.999999;
		rslope = tan(m.player.angle);
		intersection(rslope, doom, &xy, m, mlx);
		if (xy[0] >= m.sector->dot[mlx->i].x && xy[0] <= m.sector->dot[mlx->i + 1].x)
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFFFFF);
		else if (m.sector->dot[mlx->i].x > m.sector->dot[mlx->i + 1].x && (xy[0] >= m.sector->dot[mlx->i + 1].x && xy[0] <= m.sector->dot[mlx->i].x))
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFF0000);
		else if ((xy[1] >= m.sector->dot[mlx->i].y && xy[1] <= m.sector->dot[mlx->i + 1].y) && xy[0] >= m.sector->dot[mlx->i].x && xy[0] <= m.sector->dot[mlx->i + 1].x)
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFF00FF);
		else if ((m.sector->dot[mlx->i + 1].x == m.sector->dot[mlx->i].x) && (xy[1] >= m.sector->dot[mlx->i].y && xy[1] <= m.sector->dot[mlx->i + 1].y))
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFb800);
		else if ((m.sector->dot[mlx->i + 1].x == m.sector->dot[mlx->i].x) && (xy[1] >= m.sector->dot[mlx->i + 1].y && xy[1] <= m.sector->dot[mlx->i].y))
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xFFa1a1);
		else
		{
			mlx->i++;
			mlx_pixel_put(mlx->mlx, mlx->win, xy[0] * 20 + 100, xy[1] * 20 + 100, 0xb8b8b8);
		}
		ft_putnbr(mlx->i);
		m.player.angle -= doom.ar;
		x++;
	}
	//mlx->i++;
	free(xy);
}
