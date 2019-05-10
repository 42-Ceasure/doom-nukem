/**/

#include "doom.h"

void		buttonup_event(t_env *w, t_map *m)
{
	if (BUTTON == SDL_BUTTON_LEFT)
		m->player.firing = 0;
	if (BUTTON == SDL_BUTTON_RIGHT)
	{
		m->player.field_of_vision_h = WIDTH / 2;
		m->player.field_of_vision_v = HEIGHT / 2;
		m->player.aiming = 0;
	}
}

void		buttondown_event(t_env *w, t_map *m)
{
	if (BUTTON == SDL_BUTTON_LEFT)
	{
		if (Mix_Playing(3) == 0 && ft_strcmp(m->weap[PH].name, "shotgun_simple") == 0
			&& m->weap[PH].actu_ammo > 0)
		{
			m->player.firing = 1;
			Mix_PlayChannel(3, m->weap[PH].shoot, 0);
			m->weap[PH].actu_ammo -= 1;
		}
		else if (m->weap[PH].actu_ammo > 0 && ft_strcmp(m->weap[PH].name, "shotgun_simple") != 0)
		{
			m->player.firing = 1;
			Mix_PlayChannel(3, m->weap[PH].shoot, 0);
			m->weap[PH].actu_ammo -= 1;
		}
		update_ttf_txtr3(w, m);
	}
	if (BUTTON == SDL_BUTTON_RIGHT)
	{
		m->player.field_of_vision_h = WIDTH;
		m->player.field_of_vision_v = HEIGHT;
		m->player.aiming = 1;
	}
}

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
