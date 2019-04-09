//

#include "doom.h"

void		empty_world(t_env *w)
{
	if (w->pix != NULL)
		free(w->pix);
	if (w)
		free(w);
}

void		empty_map(t_map *m)
{
	int i;

	i = 0;
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
	if (m != NULL)
		free(m);
}

void		exit_game(t_env *w, t_map *m)
{
	empty_map(m);
	SDL_Quit();
	empty_world(w);
	exit(1);
}
