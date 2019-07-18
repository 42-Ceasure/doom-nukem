/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 15:04:59 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/18 10:27:53 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		move_floor_ceiling(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_PAGEUP])
		m->sector[m->player.sector].floor += 0.1;
	if (w->inkeys[SDL_SCANCODE_PAGEDOWN])
		m->sector[m->player.sector].floor -= 0.1;
	if (w->inkeys[SDL_SCANCODE_HOME])
		m->sector[m->player.sector].ceiling += 0.1;
	if (w->inkeys[SDL_SCANCODE_END])
		m->sector[m->player.sector].ceiling -= 0.1;
	if (m->sector[m->player.sector].texturing[2] == 6 && KEY == SDLK_f
		&& m->player.take[3] == 1 && m->elevator == 0)
	{
		m->elevator = 1;
		m->nb_a = m->player.sector;
	}
	if (m->sector[m->player.sector].texturing[2] == 6 && KEY == SDLK_f
		&& m->player.take[3] == 1 && m->elevator == -1)
	{
		m->elevator = 2;
		m->nb_a = m->player.sector;
	}
}

void		key_events(t_env *w, t_map *m)
{
	if (w->inkeys[SDL_SCANCODE_W] && !w->inkeys[SDL_SCANCODE_LSHIFT])
		go_forward(m);
	if (w->inkeys[SDL_SCANCODE_S])
		go_back(m);
	if (w->inkeys[SDL_SCANCODE_A])
		go_left(m);
	if (w->inkeys[SDL_SCANCODE_D])
		go_right(m);
	if (w->inkeys[SDL_SCANCODE_Q])
		look_left(m);
	if (w->inkeys[SDL_SCANCODE_E])
		look_right(m);
	if (w->inkeys[SDL_SCANCODE_SPACE])
		jump(w, m);
	if (w->inkeys[SDL_SCANCODE_LSHIFT] && w->inkeys[SDL_SCANCODE_W])
		sprint(m);
	move_floor_ceiling(w, m);
}
