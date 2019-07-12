/*BIG42HEADER*/

#include "doom.h"

void	fit_to_editor(t_env *w)
{

	// Rajoute ton centrage de fenetre si tu veux

	w->res.width = w->editor_res.width;
	w->res.height = w->editor_res.height;
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	free(w->pix);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	clean_render(w, 0x12000000);
	img_update(w);
}

void	fit_to_game(t_env *w)
{
	w->res.width = w->game_res.width;
	w->res.height = w->game_res.height;
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	free(w->pix);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	clean_render(w, 0x12000000);
	img_update(w);
}
