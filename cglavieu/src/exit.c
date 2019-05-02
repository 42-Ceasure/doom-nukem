/*BIG42HEADER*/

#include "doom.h"

void		empty_music(t_env *w)
{
	if (w->sound.musique != NULL)
		Mix_FreeMusic(w->sound.musique);
	if (w->sound.jump != NULL)
		Mix_FreeChunk(w->sound.jump);
	if (w->sound.ground != NULL)
		Mix_FreeChunk(w->sound.ground);;
	if (w->sound.reload != NULL)
		Mix_FreeChunk(w->sound.reload);
	Mix_CloseAudio();
}

void		empty_world(t_env *w)
{
	int		i;

	i = 0;
	if (w != NULL)
	{
		if (w->main_pic[0].pix != NULL)
			free(w->main_pic[0].pix);
		if (w->main_pic[1].pix != NULL)
			free(w->main_pic[1].pix);
		if (w->pix != NULL)
			free(w->pix);
		if (w->hud.pix != NULL)
			free(w->hud.pix);
		while (i < 42)
		{
			free(w->ascii[i].pix);
			i++;
		}
		free(w->menu.y);
		ft_memreg3(w->menu.list);
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
				if (m->weap[i].shoot != NULL)
					Mix_FreeChunk(m->weap[i].shoot);
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

void		empty_sdl(t_env *w)
{
	SDL_DestroyTexture(w->txtr);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyWindow(w->win);
	SDL_Quit();
}

void		exit_game(t_env *w, t_map *m, int i)
{
	empty_music(w);
	empty_map(m);
	empty_sdl(w);
	empty_world(w);
	if (i == 1)
		exit(0);
}
