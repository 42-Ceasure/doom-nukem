//

#include "doom-nukem.h"

void	img_clear(t_env *w)
{
	int		x;
	int		y;

	y = 0;
	while (y <= HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			w->pix[y * WIDTH + x] = color(0x121E7FCB);
			x++;
		}
		y++;
	}
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			w->pix[y * WIDTH + x] = color(0x124E3D28);
			x++;
		}
		y++;
	}
}

void		exit_game(t_env *w, t_map *m)
{
	free(w);
	free(m);
	SDL_Quit();
	exit(1);
}

void		motion_events(t_env *w, t_map *m)
{
	if (w->event.motion.xrel < 0)
	{
		m->player.angle += 0.0174533;
		w->event.motion.x = WIDTH / 2;
		w->event.motion.y = HEIGHT / 2;
	}
	if (w->event.motion.xrel > 0)
	{
		m->player.angle -= 0.0174533;
		w->event.motion.xrel = WIDTH / 2;
		w->event.motion.yrel = HEIGHT / 2;
	}
}

void		key_events(t_env *w, t_map *m)
{
	double x_unit;
	double y_unit;

	if (w->inkeys[SDL_SCANCODE_W])
	{
		x_unit = cos(m->player.angle) * 0.1;
		y_unit = sin(m->player.angle) * 0.1;
		m->player.coor.x -= x_unit;
		m->player.coor.y -= y_unit;
	}
	if (w->inkeys[SDL_SCANCODE_S])
	{
		x_unit = cos(m->player.angle) * 0.1;
		y_unit = sin(m->player.angle) * 0.1;
		m->player.coor.x += x_unit;
		m->player.coor.y += y_unit;
	}
	// if (w->inkeys[SDL_SCANCODE_A])
	// 	m->player.coor.x += 0.1; 
	// if (w->inkeys[SDL_SCANCODE_D])
	// 	m->player.coor.x -= 0.1;
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
	SDL_ShowCursor(SDL_DISABLE);
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
//		img_clear(w);
		if (draw(w, m) == -1)
			ft_putendl("problem on Raycasting...");
		SDL_UpdateTexture(w->txtr, NULL, w->pix, WIDTH * sizeof(Uint32));
		SDL_RenderCopy(w->rdr, w->txtr, NULL, NULL);
		SDL_RenderPresent(w->rdr);
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
	}
	return (0);
}
