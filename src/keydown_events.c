/**/

#include "doom.h"

void		affichage(t_env *w, t_map *m)
{
	if (KEY == SDLK_i)
		hud(m);
	if (KEY == SDLK_TAB)
		minimap(m);
	if (KEY == SDLK_f)
	 	och_door(m);
	if (KEY == SDLK_m)
		ramassage(m);
}

void		music(t_env *w)
{
	if (KEY == SDLK_p)
		pause_music();
	if (KEY == SDLK_KP_PLUS)
		volume_more(w);
	if (KEY == SDLK_KP_MINUS)
		volume_less(w);
}

void		sit_down(t_env *w, t_map *m)
{
	if (KEY == SDLK_LCTRL)
		crouch(m);
	if (KEY == SDLK_z)
		crawl_lock(m);
	if (KEY == SDLK_x)
		crouch_lock(m);
}

void		keydown_events(t_env *w, t_map *m)
{
	if (KEY == SDLK_1)
		switch_weapon(m, 0);
	if (KEY == SDLK_2)
		switch_weapon(m, 1);
	if (KEY == SDLK_3)
		switch_weapon(m, 2);
	if (KEY == SDLK_r)
		reload_weapon(w, m);
	if (KEY == SDLK_k)
	{
		w->sequential_frame = 1;
		sequential_frame(w, m);
	}
	if (KEY == SDLK_UP)
		jet_pack(m);
	sit_down(w, m);
	music(w);
	affichage(w, m);
}
