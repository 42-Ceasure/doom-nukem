/*BIG42HEADER*/

#include "doom.h"

void		key_events(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W] && !w->inkeys[SDL_SCANCODE_LSHIFT])
		go_forward(m);
	if (w->inkeys[SDL_SCANCODE_S])
		go_back(m);
	if (w->inkeys[SDL_SCANCODE_A])
		go_left(m);
	if (w->inkeys[SDL_SCANCODE_D])
		go_right(m);
	if (w->inkeys[SDL_SCANCODE_Q])
		look_left(m);
	if (w->inkeys[SDL_SCANCODE_E])
		look_right(m);
	if (w->inkeys[SDL_SCANCODE_SPACE])
		jump(w, m);
	if (w->inkeys[SDL_SCANCODE_LSHIFT] && w->inkeys[SDL_SCANCODE_W])
		sprint(m);
	// a modif
	if (w->inkeys[SDL_SCANCODE_PAGEUP])
		m->sector[m->player.sector].floor += 0.1;
	if (w->inkeys[SDL_SCANCODE_PAGEDOWN])
		m->sector[m->player.sector].floor -= 0.1;
	if (w->inkeys[SDL_SCANCODE_HOME])
		m->sector[m->player.sector].ceiling += 0.1;
	if (w->inkeys[SDL_SCANCODE_END])
		m->sector[m->player.sector].ceiling -= 0.1;
}
