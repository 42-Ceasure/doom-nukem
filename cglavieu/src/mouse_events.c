/*BIG42HEADER*/

#include "doom.h"

void		buttonup_event(t_env *w, t_map *m)
{
	if (BUTTON == SDL_BUTTON_LEFT)
		set_shoot(m, 0);
	if (BUTTON == SDL_BUTTON_RIGHT)
		stop_aim(w, m);
}

void		buttondown_event(t_env *w, t_map *m)
{
	if (BUTTON == SDL_BUTTON_LEFT)
		set_shoot(m, 1);
	if (BUTTON == SDL_BUTTON_RIGHT)
		aim(w, m);
}

void		motion_events(t_env *w, t_map *m)
{
	look_around(w, m);
	if (m->player.display == 0)
	{
		w->event.motion.x = WIDTH / 2;
		w->event.motion.y = HEIGHT / 2;
	}
	move_player(0, 0, m);
}
