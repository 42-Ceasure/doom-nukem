/*BIG42HEADER*/

#include "doom.h"

void	fit_to_editor(t_env *w)
{
	SDL_SetWindowSize(w->win, WIN_X, WIN_X);
}

void	fit_to_game(t_env *w)
{
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
}
