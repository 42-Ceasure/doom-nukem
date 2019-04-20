/**/

#include "doom.h"

void			keyup_events(t_env *w, t_map *m)
{
	if (KEY == SDLK_LCTRL)
		m->player.stance = 0;
	if (KEY == SDLK_TAB)
		m->player.display = 0;
}