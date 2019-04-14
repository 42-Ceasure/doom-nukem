/*BIG42HEADER*/

#include "doom.h"

void		empty_world(t_env *w)
{
	if (w != NULL)
	{
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
		if (m->dot != NULL)
			free(m->dot);
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
	Mix_FreeMusic(w->musique);
	Mix_FreeChunk(w->jump);
	Mix_FreeChunk(w->shoot);
   	Mix_CloseAudio();
	empty_map(m);
	SDL_Quit();
	empty_world(w);
	exit(1);
}