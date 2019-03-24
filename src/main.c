//

#include "doom-nukem.h"

void		exit_game(t_env *w)
{
	free(w);
	SDL_Quit();
	exit(1);
}

void		run(t_env *w)
{
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
				if (KEY == 27)
					exit_game(w);
		}
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
	//SDL_SetRelativeMouseMode(SDL_TRUE);
	//SDL_ShowCursor(SDL_DISABLE);
	return (0);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		m;

	if ((w = malloc(sizeof(t_env))) == NULL)
		return (0);
	if ((init_sdl(w)) == -1)
	{
		write(1, "cannot intitialize SDL2\n", 24);
		return (0);
	}
	if (ac == 1)
		m = set_basic_run(w);
	else
		m = set_advanced_run(w, av);
	if (w->win)
		run(w);
	return (0);
}
