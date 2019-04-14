/**/

#include "doom.h"

void		motion_events(t_env *w, t_map *m)
{
	PL_A = PL_A + w->event.motion.xrel * 0.001;
	if (PL_A > 2 * M_PI)
		PL_A = PL_A - 2 * M_PI;
	if (PL_A < 0)
		PL_A = PL_A + 2 * M_PI;
	m->yaw = vmid(m->yaw + w->event.motion.yrel * 0.002, -4, 4);
	m->player.yaw = m->yaw - m->player.move_speed.z * 0.02;
	if (m->player.display == 0)
	{
		w->event.motion.x = WIDTH / 2;
		w->event.motion.y = HEIGHT / 2;
	}
	move_player(0, 0, m);
}