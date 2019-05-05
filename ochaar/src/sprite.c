/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 23:14:09 by agay              #+#    #+#             */
/*   Updated: 2019/05/05 17:52:36 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*void	fire(t_map, t_env *m, t_sprite *sprite)
{
	int		i;
	int		d;

	d = 0;
	while (d < 36)
	{
		i = 0;
		while (i < 36)
		{
			w->pix[(HEIGHT - 36 + d) * WIDTH + (WIDTH / 2 - 36 / 2 + i)] = sprite[3].pix[d * 36 + i];
			i++;
		}
		d++;
	}
}*/

// void	hand(t_map *m, t_env *w)
// {
// 	int			i;
// 	int			d;

// 	i = 0;
// 	d = 0;
// 	if (m->player.moving != 0)
// 	{
// 		while (d < 121)
// 		{
// 			i = 0;
// 			while (i < 128)
// 			{
// 				if (m->sprite[1].pix[d * 128 + i] != 4278231784)
// 					w->pix[(HEIGHT - 121 + d) * WIDTH + ((WIDTH / 2 + 40) - 128 / 2 + i)] = m->sprite[1].pix[d * 128 + i];
// 				i++;
// 			}
// 			d++;
// 		}
// 	}
// 	else
// 	{
// 		while (d < 131)
// 		{
// 			i = 0;
// 			while (i < 131)
// 			{
// 				if (m->sprite[2].pix[d * 131 + i] != 4278231784)
// 					w->pix[(HEIGHT - 131 + d) * WIDTH + (WIDTH / 2 - 131 / 2 + i)] = m->sprite[2].pix[d * 131 + i];
// 				i++;
// 			}
// 			d++;
// 		}
// 	}
// }

void	place_sprite(t_map *m, t_env *w, int nb, int decal)
{
	int			i;
	int			d;

	d = 0;
	while (d < m->weap[PH].sprt[nb].h)
	{
		i = 0;
		while (i < m->weap[PH].sprt[nb].w)
		{
			if (m->weap[PH].sprt[nb].pix[d * m->weap[PH].sprt[nb].w + i]
				!= m->weap[PH].sprt[nb].pix[0])
				w->pix[(d + m->weap[PH].sprt[nb].sy - decal) * WIDTH
					+ (i + m->weap[PH].sprt[nb].sx)] = m->weap[PH].sprt[nb].pix[d
						* m->weap[PH].sprt[nb].w + i];
			i++;
		}
		d++;
	}
}

void	fire(t_map *m, t_env *w)
{
	int i;
	int j;

	i = 0;
	while (i < m->fire.h)
	{
		j = 0;
		while (j < m->fire.w)
		{
			if (m->fire.pix[i * m->fire.w + j] != m->fire.pix[0])
				w->pix[(i - m->fire.h / 2 + HEIGHT / 2) * WIDTH + (j - m->fire.w / 2 + WIDTH / 2)] = m->fire.pix[i * m->fire.w + j];
			j++;
		}
		i++;
	}
}

void	hand(t_map *m, t_env *w)
{
	if (PH > -1)
	{
		if (m->player.aiming == 1)
		{
			if (m->player.firing == 1)
			{
				fire(m, w);
				place_sprite(m, w, 1, 5);
			}
			else
				place_sprite(m, w, 1, 0);
		}
		else
		{
			if (m->player.moving != 0)
				place_sprite(m, w, 2, 0);
			else
			{
				if (m->player.firing == 1)
				{
					//fire(m, w);
					place_sprite(m, w, 0, 5);
				}
				else
					place_sprite(m, w, 0, 0);
			}
		}
	}
}

// void	sprite(t_env *w, t_map *m)
// {
// 	int		x;
// 	int		y;
// 	double	v1x;
// 	double	v2x;
// 	double	v2y;
// 	// double	yb;
// 	double	v1y;
// 	double	t1x;
// 	double	t2x;
// 	double	t1z;
// 	double	t2z;
// 	double	xscale1;
// 	double	xscale2;
// 	double	x1;
// 	double	x2;
// 	double	y1b;
// 	double	y2b;
// 	double	yscale1;
// 	double	yscale2;
// 	// double	cyb;
// 	int		d;
// 	int		i;
// 	// t_draw		work;
// 	//t_sprite	handh;

// 	d = 0;
// 	hand(m, w);
// 	while (d < WIDTH)
// 	{
// 		work.ytop[d] = 0;
// 		work.ybot[d] = 40;
// 		d++;
// 	}
// 	d = 0;
// 	x = 40;
// 	y = 4;
// 	v1x = x - PL_X;
// 	v2x = (x + 64) - PL_X;
// 	v1y = y - PL_Y;
// 	v2y = (y + 64) - PL_Y;
// 	t1x = v1x * PL_AS - v1y * PL_AC;
// 	t2x = v2x * PL_AS - v2y * PL_AC;
// 	t1z = v1x * PL_AC + v1y * PL_AS;
// 	t2z = v2x * PL_AC + v2y * PL_AS;
// 	xscale1 = m->player.field_of_vision_h / t1z;
// 	xscale2 = m->player.field_of_vision_h / t2z;
// 	yscale1 = m->player.field_of_vision_v / t1z;
// 	yscale2 = m->player.field_of_vision_v / t2z;
// 	x1 = WIDTH / 2 - (int)(t1x * xscale1);
// 	x2 = WIDTH / 2 - (int)(t2x * xscale2);
// 	y1b = HEIGHT / 2 - (int)(yaw((m->sector[3].floor - m->player.coor.z), t1z, m) * yscale1);
// 	y2b = HEIGHT / 2 - (int)(yaw((m->sector[3].floor - m->player.coor.z), t2z, m) * yscale2);
// 	if (t1z > 0)
// 	{
// 		while (d < 64)
// 		{
// 			i = 0;
// 			yb = (d - x1) * (y2b - y1b) / (x2 - x1) + y1b;
// 			// cyb = vmid(yb, work.ytop[d], work.ybot[d]);
// 			while (i < 64)
// 			{
// 				//if (sprite.pix[d * 64 + i] != 4288151688 && (cyb >= 0 && cyb + d < HEIGHT) && (x1 >= 0 && x1 + i < WIDTH))
// 				//w->pix[(int)(cyb + d) * WIDTH + (int)(x1 + i)] = sprite.pix[d * 64 + i];
// 				i++;
// 			}
// 			d++;
// 		}
// 	}
// 	d = 0;
// }
