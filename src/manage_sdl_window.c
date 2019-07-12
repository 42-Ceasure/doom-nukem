/*BIG42HEADER*/

#include "doom.h"

void	fit_to_editor(t_env *w)
{
	SDL_SetWindowSize(w->win, WIN_X, WIN_Y);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIN_X, WIN_Y);
	clean_render(w, 0x12000000);
	img_update(w);
	SDL_Delay(3000);
}

void	fit_to_game(t_env *w)
{
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
}
