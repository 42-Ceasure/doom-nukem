/**/

#include "doom.h"

void	hand(t_map *m, t_env *w)
{
	int			i;
	int			d;

	i = 0;
	d = 0;
	if (m->player.moving != 0)
	{
		while (d < 121)
		{
			i = 0;
			while (i < 128)
			{
				if (w->sprite[1].pix[d * 128 + i] != 4278231784)
					w->pix[(HEIGHT - 121 + d) * WIDTH + (WIDTH / 2 - 128 / 2 + i)] = w->sprite[1].pix[d * 128 + i];
				i++;
			}
			d++;
		}
	}
	else
	{
		while (d < 131)
		{
			i = 0;
			while (i < 131)
			{
				if (w->sprite[2].pix[d * 131 + i] != 4278231784)
					w->pix[(HEIGHT - 131 + d) * WIDTH + (WIDTH / 2 - 131 / 2 + i)] = w->sprite[2].pix[d * 131 + i];
				i++;
			}
			d++;
		}
	}
}
