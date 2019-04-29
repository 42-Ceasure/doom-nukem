/*BIG42HEADER*/

#include "doom.h"

void		empty_music(t_env *w, t_map *m)
{
	if (w->sound.musique != NULL)
		Mix_FreeMusic(w->sound.musique);
	if (w->sound.jump != NULL)
		Mix_FreeChunk(w->sound.jump);
	if (m->weap[0].shoot != NULL)
		Mix_FreeChunk(m->weap[0].shoot);
	if (m->weap[1].shoot != NULL)
		Mix_FreeChunk(m->weap[1].shoot);
	if (m->weap[2].shoot != NULL)
		Mix_FreeChunk(m->weap[2].shoot);
	//if (m->weap[3].shoot != NULL)
	//	Mix_FreeChunk(m->weap[3].shoot);
	if (w->sound.ground != NULL)
		Mix_FreeChunk(w->sound.ground);
	Mix_CloseAudio();
}

void		empty_world(t_env *w)
{
	if (w != NULL)
	{
		if (w->main_pic[0].pix != NULL)
			free(w->main_pic[0].pix);
		if (w->main_pic[1].pix != NULL)
			free(w->main_pic[1].pix);
		if (w->main_pic[2].pix != NULL)
			free(w->main_pic[2].pix);
		if (w->main_pic[3].pix != NULL)
			free(w->main_pic[3].pix);
		if (w->main_pic[4].pix != NULL)
			free(w->main_pic[4].pix);
		if (w->pix != NULL)
			free(w->pix);
		free(w);
	}
}

void		empty_map(t_map *m)
{
	int i;

	i = 0;
	if (m != NULL)
	{
		if (m->map_name != NULL)
			free(m->map_name);
		if (m->map_name != NULL)
			free(m->map_path);
		if (m->dot != NULL)
			free(m->dot);
		if (m->hud.pix != NULL)
			free(m->hud.pix);
		if (m->weap != NULL)
		{
			while (i < m->weapon_count)
			{
				free(m->weap[i].sprt[0].pix);
				free(m->weap[i].sprt[0].name);
				free(m->weap[i].sprt[1].pix);
				free(m->weap[i].sprt[1].name);
				free(m->weap[i].sprt[2].pix);
				free(m->weap[i].sprt[2].name);
				free(m->weap[i].name);
				i++;
			}
			free(m->weap);
		}
		i = 0;
		if (m->sector != NULL)
		{
			while (i < m->sector_count)
			{
				if (m->sector[i].dot != NULL)
					free(m->sector[i].dot);
				if (m->sector[i].network != NULL)
					free(m->sector[i].network);
				i++;
			}
			free(m->sector);
		}
		free(m);
	}
}

void		exit_game(t_env *w, t_map *m)
{
	empty_map(m);
	SDL_Quit();
	empty_world(w);
	exit(1);
}
