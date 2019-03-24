//

#include "doom-nukem.h"

void		exit_game(t_env *w, t_map *m)
{
	free(w);
	free(m);
	SDL_Quit();
	exit(1);
}

void		key_events(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_M])
		exit_game(w, m);
		// recap_parsing(m, "map_general");
	if (w->inkeys[SDL_SCANCODE_J])
		exit_game(w, m);
		// recap_parsing(m, "map_list_dots");
	if (w->inkeys[SDL_SCANCODE_K])
		exit_game(w, m);
		// recap_parsing(m, "map_list_sectors");
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
		}
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
	}
	return (0);
}
