/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 14:19:02 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/05 16:11:52 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

t_cal_sprt	calcul_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	tmp;
	
	tmp.v1x = m->sprt[x].sx - PL_X;
	tmp.v1y = m->sprt[x].sy - PL_Y;
	tmp.t1x = tmp.v1x * PL_AS - tmp.v1y * PL_AC;
	tmp.t1z = tmp.v1x * PL_AC + tmp.v1y * PL_AS;
	tmp.xscale1 = m->player.field_of_vision_h / tmp.t1z;
	tmp.yscale1 = m->player.field_of_vision_v / tmp.t1z;
	tmp.zoom = m->sprt[x].range;
	if (m->player.aiming == 1)
		tmp.zoom *= 2;
	tmp.x1 = WIDTH / 2 - (tmp.t1x * tmp.xscale1 + (m->sprite[m->sprt[x].index].w / 2
		* tmp.zoom * ratio));
	/*if (ft_strcmp(m->sprite[x].type, "decor") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprite[x].sector].ceiling
			- m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - 10;*/
	if (ft_strcmp(m->sprite[m->sprt[x].index].type, "item") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor - m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - (m->sprite[m->sprt[x].index].h * tmp.zoom * ratio);		
	else if (ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0)
		tmp.y1a = HEIGHT / 2 - (int)(yaw((m->sector[m->sprt[x].sector].floor - m->player.coor.z), tmp.t1z, m) * tmp.yscale1) - (100 * tmp.zoom * ratio);
	return (tmp);
}

void		draw_sprite(t_env *w, t_map *m, int x, int ratio)
{
	t_cal_sprt	data;
	double		range;

	data = calcul_sprite(w, m, x, ratio);
	range = data.zoom;
	if (data.t1z > 0 && m->sprt[x].vis == 1)
	{
		if (ft_strcmp(m->sprite[m->sprt[x].index].type, "auto") == 0)
			final_sprite_to_screen(w, m->sprite[m->sprt[x].index], data.x1, data.y1a, 0, 100 * range * ratio);
		else
			final_sprite_to_screen(w, m->sprite[m->sprt[x].index], data.x1, data.y1a, m->sprite[m->sprt[x].index].w * range * ratio, 0);
	}
}

void	swipe_sprite(t_env *w, t_map *m, int x)
{
	if (w->dtime.walk == 0)
		m->ennemy[x].cpt++;
	if (m->ennemy[x].range < 1)
	{
		if (m->ennemy[x].cpt % 3 == 0)
			m->ennemy[x].index = 6;
		if (m->ennemy[x].cpt % 3 == 1)
			m->ennemy[x].index = 7;
		if (m->ennemy[x].cpt % 3 == 2)
			m->ennemy[x].index = 8;
	}
	else
	{
		if (m->ennemy[x].cpt % 2 == 0)
		{
			m->ennemy[x].index = 9;
			m->ennemy[x].die = 1;
		}
		else
		{
			m->ennemy[x].index = 10;
			if (m->ennemy[x].die == 1)
			{
				m->player.hp -= 10;
				m->ennemy[x].die = 0;
			}
		}
	}
	if (m->ennemy[x].touche == 1)
	{
		m->ennemy[x].index = 11;
		if (w->dtime.dead == 0)
			m->ennemy[x].count++;
		if (m->ennemy[x].count % 3 == 2)
		{
			m->ennemy[x].touche = 0;
			m->ennemy[x].count = 0;
		}
	}
	draw_ennemy(w, m, x, 5);
}

void	ft_swap(double *a, double *b)
{
	double		tmp;
	double		tmp2;
	double		tmp3;

	tmp = a[0];
	tmp2 = a[1];
	tmp3 = a[2];
	a[0] = b[0];
	a[1] = b[1];
	a[2] = b[2];
	b[0] = tmp;
	b[1] = tmp2;
	b[2] = tmp3;
}

double	**sort_double_tab(double **tab, int size)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i][0] > tab[i + 1][0])
		{
			ft_swap(tab[i], tab[i + 1]);
			sort_double_tab(tab, size);
		}
		i++;
	}
	return (tab);
}

void	count_sprite(t_env *w, t_map *m)
{
	int 	x;
	int 	i;
	double		**tab;
	double	diffx;
	double	diffy;

	x = 0;
	tab = (double**)malloc(sizeof(double*) * (m->sprite_map_count + m->ennemy_count) + 1);
	while (x < m->sprite_map_count)
	{
		tab[x] = (double*)malloc(sizeof(double) * 3 + 1);
		diffx = fabs(m->player.coor.x - m->sprt[x].sx);
		diffy = fabs(m->player.coor.y - m->sprt[x].sy);
		m->sprt[x].range = 1 / (sqrt((diffx * diffx) + (diffy * diffy)) / 10);
		tab[x][0] = m->sprt[x].range;
		tab[x][1] = x;
		tab[x][2] = 0;
		x++;
	}
	i = 0;
	while (i < m->ennemy_count)
	{
		tab[x + i] = (double*)malloc(sizeof(double) * 3 + 1);
		diffx = fabs(m->player.coor.x - m->ennemy[i].coor.x);
		diffy = fabs(m->player.coor.y - m->ennemy[i].coor.y);
		m->ennemy[i].range = 1 / (sqrt((diffx * diffx) + (diffy * diffy)) / 10);
		tab[x + i][0] = m->ennemy[i].range;
		tab[x + i][1] = i;
		tab[x + i][2] = 1;
		i++;
	}
	tab = sort_double_tab(tab, m->sprite_map_count + m->ennemy_count);
	x = 0;
	while (x < m->sprite_map_count + m->ennemy_count)
	{
		if ((int)tab[x][2] == 0)
		{
			if (m->sprt[(int)tab[x][1]].taken != 1)
				draw_sprite(w, m, (int)tab[x][1], 1);
			if (m->sprt[(int)tab[x][1]].range >= 2 && ft_strcmp(m->sprite[m->sprt[(int)tab[x][1]].index].type, "auto") == 0
				&& m->sprt[(int)tab[x][1]].taken != 1)
			{
				if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\thealth") == 0 && m->player.hp < 100)
				{
					m->player.hp += 30;
					m->sprt[(int)tab[x][1]].taken = 1;
				}
				else if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\tcartouche") == 0)
				{
					m->player.bullet[1] += 6;
					m->sprt[(int)tab[x][1]].taken = 1;
				}
				else if (ft_strcmp(m->sprt[(int)tab[x][1]].name, "\tammo") == 0)
				{
					m->player.bullet[0] += 30;
					m->sprt[(int)tab[x][1]].taken = 1;
				}
			}
		}
		else
		{
			if (m->ennemy[(int)tab[x][1]].vis == 1)
			{
				if (m->ennemy[(int)tab[x][1]].dead == 0)
					swipe_sprite(w, m, (int)tab[x][1]);
				else
				{
					if (w->dtime.dead == 0)
						m->ennemy[(int)tab[x][1]].count++;
					if (m->ennemy[(int)tab[x][1]].count % 3 == 0 && m->ennemy[(int)tab[x][1]].is_dead == 0)
						m->ennemy[(int)tab[x][1]].index = 11;
					else if (m->ennemy[(int)tab[x][1]].count % 3 == 1 && m->ennemy[(int)tab[x][1]].is_dead == 0)
						m->ennemy[(int)tab[x][1]].index = 12;
					else
					{
						m->ennemy[(int)tab[x][1]].index = 13;
						m->ennemy[(int)tab[x][1]].is_dead = 1;
					}
					draw_ennemy(w, m, (int)tab[x][1], 5);
				}
			}
		}
		free(tab[x]);
		x++;
	}
	m->player.firing = 0;
}

void	test_sprite(t_map *m, double xx, double yy)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		if (m->sprt[x].sx == (int)xx && m->sprt[x].sy == (int)yy && m->sprt[x].vis != 1)
			m->sprt[x].vis = 1;
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		if ((int)m->ennemy[x].coor.x == (int)xx && (int)m->ennemy[x].coor.y == (int)yy && m->ennemy[x].vis != 1)
			m->ennemy[x].vis = 1;
		x++;
	}
}

void	test_sprite2(t_map *m, double xx, double yy)
{
	int x2;
	
	x2 = 0;
	while (x2 < m->sprite_map_count)
	{
		if (m->sprt[x2].vis != 1)
		{
			if (m->sprt[x2].sx == (int)xx && m->sprt[x2].sy == (int)yy && m->sprt[x2].vis != 1)
				m->sprt[x2].vis = 1;
		}
		x2++;
	}
	x2 = 0;
	while (x2 < m->ennemy_count)
	{
		if (m->ennemy[x2].vis != 1)
		{
			if ((int)m->ennemy[x2].coor.x == (int)xx && (int)m->ennemy[x2].coor.y == (int)yy && m->ennemy[x2].vis != 1)
				m->ennemy[x2].vis = 1;
		}
		x2++;
	}
}

void	clear_sprite(t_map *m)
{
	int x;

	x = 0;
	while (x < m->sprite_map_count)
	{
		m->sprt[x].vis = 0;
		x++;
	}
	x = 0;
	while (x < m->ennemy_count)
	{
		m->ennemy[x].vis = 0;
		x++;
	}
}
