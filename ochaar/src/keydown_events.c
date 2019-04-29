/**/

#include "doom.h"

void		affichage(t_env *w, t_map *m)
{
	int i;

	i = 0;
	if (KEY == SDLK_i)
	{
		if (w->hud != 1)
			w->hud = 1;
		else
			w->hud = 0;
	}
	if (KEY == SDLK_UP)
		m->player.field_of_vision_v += 5;
	if (KEY == SDLK_DOWN)
		m->player.field_of_vision_v -= 5;
	if (KEY == SDLK_RIGHT)
		m->player.field_of_vision_h += 5;
	if (KEY == SDLK_LEFT)
		m->player.field_of_vision_h -= 5;
	if (KEY == SDLK_PAGEUP)
		m->sector[m->player.sector].floor += 1;
	if (KEY == SDLK_PAGEDOWN)
		m->sector[m->player.sector].floor -= 1;
	if (KEY == SDLK_HOME)
		m->sector[m->player.sector].ceiling += 1;
	if (KEY == SDLK_END)
		m->sector[m->player.sector].ceiling -= 1;
	if (KEY == SDLK_TAB)
		m->player.display = 1;
	if (KEY == SDLK_f)
	{
		if (m->sector[1].ceiling < 40)
			m->sector[1].ceiling += 2;
		else
			m->sector[1].ceiling -= 39;
	}
}

void		music(t_env *w)
{
	if (KEY == SDLK_p)
	{
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
	if (KEY == SDLK_KP_PLUS)
	{
		w->sound.volume += 5;
		w->sound.volume = (int)vmid(0, w->sound.volume, 128);
		Mix_VolumeMusic(w->sound.volume);
	}
	if (KEY == SDLK_KP_MINUS)
	{
		w->sound.volume -= 5;
		w->sound.volume = (int)vmid(0, w->sound.volume, 128);
		Mix_VolumeMusic(w->sound.volume);
	}
}

void		sit_down(t_env *w, t_map *m)
{
	if (KEY == SDLK_LCTRL)
	{
		m->player.stance = 1;
		m->player.fall = 1;
	}
	if (KEY == SDLK_z)
	{
		if (m->player.stance != 2)
			m->player.stance = 2;
		else
			m->player.stance = 0;
		m->player.fall = 1;
	}
	if (KEY == SDLK_x)
	{
		if (m->player.stance != 1)
			m->player.stance = 1;
		else
			m->player.stance = 0;
		m->player.fall = 1;
	}
}

void		keydown_events(t_env *w, t_map *m)
{
	if (KEY == 27)
		exit_game(w, m);
	if (KEY == SDLK_t)
	{
		if (m->trippymod == 1)
			m->trippymod = 0;
		else
			m->trippymod = 1;
	}
	if (KEY == SDLK_KP_9)
		printf("hfov:%f,vfov:%f\n", m->player.field_of_vision_h, m->player.field_of_vision_v);
	if (KEY == SDLK_1)
		m->player.handed = 0;
	if (KEY == SDLK_2)
		m->player.handed = 1;
	if (KEY == SDLK_3)
		m->player.handed = 2;
	sit_down(w, m);
	music(w);
	affichage(w, m);
}
