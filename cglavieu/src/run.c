//

#include "doom-nukem.h"

void		exit_game(t_env *w, t_map *m)
{
	free(w);
	free(m);
	SDL_Quit();
	exit(1);
}

void MovePlayer(double dx, double dy, t_map *m)
{
	int s;
	const t_sector *sect;
	t_intersect i;
	t_coor coor;
	/* Check if this movement crosses one of this sector's edges
	 * that have a neighboring sector on the other side.
	 * Because the edge vertices of each sector are defined in
	 * clockwise order, PointSide will always return -1 for a point
	 * that is outside the sector and 0 or 1 for a point that is inside.
	 */
	s = 0;
	sect = &m->sector[m->player.sector];
	i.x1 = m->player.coor.x;
	i.y1 = m->player.coor.y;
	i.x2 = i.x1 + dx;
	i.y2 = i.y1 + dy;
	i.x3 = sect->dot[s+0].x;
	i.y3 = sect->dot[s+0].y;
	i.x4 = sect->dot[s+1].x;
	i.y4 = sect->dot[s+1].y;
	coor.x = i.x2;
	coor.y = i.y2;
	while (s < sect->wall_count)
	{
		if(ft_strcmp(sect->network[s], "x") != 0 && intersectBox(i) && pointSide(coor, i.x3, i.y3, i.x4, i.y4) < 0)
		{
			m->player.sector = ft_atoi(sect->network[s]);
			printf("Player is now in sector %d\n", m->player.sector);
			break;
		}
		s++;
	}
	m->player.coor.x += dx;
	m->player.coor.y += dy;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		motion_events(t_env *w, t_map *m)
{
	PL_A = PL_A + w->event.motion.xrel * 0.001;
	m->player.anglesin = sin(m->player.angle);
	m->player.anglecos = cos(m->player.angle);
}

void		key_events(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W])
	{
		PL_X = PL_X + cos(PL_A) / 10;
		PL_Y = PL_Y + sin(PL_A) / 10;
		// m->player.move_speed.x += m->player.anglecos*0.2f;
		// m->player.move_speed.y += m->player.anglesin*0.2f; 
	}
	if (w->inkeys[SDL_SCANCODE_S])
	{
		PL_X = PL_X - cos(PL_A) / 10;
		PL_Y = PL_Y - sin(PL_A) / 10;
		// m->player.move_speed.x -= m->player.anglecos*0.2f;
		// m->player.move_speed.y -= m->player.anglesin*0.2f;
	}
	if (w->inkeys[SDL_SCANCODE_A])
	{
		PL_X = PL_X + sin(PL_A) / 10;
		PL_Y = PL_Y - cos(PL_A) / 10;
		// m->player.move_speed.x += m->player.anglesin*0.2f;
		// m->player.move_speed.y -= m->player.anglecos*0.2f;
	}
	if (w->inkeys[SDL_SCANCODE_D])
	{
		PL_X = PL_X - sin(PL_A) / 10;
		PL_Y = PL_Y + cos(PL_A) / 10;
		// m->player.move_speed.x -= m->player.anglesin*0.2f;
		// m->player.move_speed.y += m->player.anglecos*0.2f;
	}
	if (w->inkeys[SDL_SCANCODE_Q])
	{
		PL_A = PL_A - 0.1;
		if (PL_A > 2 * M_PI)
			PL_A = PL_A - 2 * M_PI;
		if (PL_A < 0)
			PL_A = PL_A + 2 * M_PI;

	}
	if (w->inkeys[SDL_SCANCODE_E])
	{
		PL_A = PL_A + 0.1;
		if (PL_A > 2 * M_PI)
			PL_A = PL_A - 2 * M_PI;
		if (PL_A < 0)
			PL_A = PL_A + 2 * M_PI;
	}
}

int			init_sdl(t_env *w)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (-1);
	w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
									SDL_WINDOWPOS_CENTERED,
									WIDTH,
									HEIGHT,
									SDL_WINDOW_RESIZABLE);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIDTH,
										HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	// SDL_ShowCursor(SDL_DISABLE);
	return (0);
}

int		run(t_env *w, t_map *m)
{
	if ((init_sdl(w)) == -1)
	{
		write(1, "cannot intitialize SDL2\n", 24);
		return (-1);
	}
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
				if (KEY == 27)
					exit_game(w, m);
			if (w->event.type == SDL_MOUSEMOTION)
				motion_events(w, m);
		}
		clean_render(w, 0x12000000);
		draw(w, *m);
		// draw_mini_map(w, *m);
		SDL_UpdateTexture(w->txtr, NULL, w->pix, WIDTH * sizeof(Uint32));
		SDL_RenderCopy(w->rdr, w->txtr, NULL, NULL);
		SDL_RenderPresent(w->rdr);
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
		//printf("px=%f,py=%f,pa=%f\n", m->player.coor.x, m->player.coor.y, m->player.angle);
	}
	return (0);
}
