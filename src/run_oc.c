/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_oc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/13 14:22:55 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/13 14:35:11 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_cursor(t_env *w, t_map *m)
{
	int i;

	i = 0;
	if (m->player.aiming != 1)
	{
		while (i < 5)
		{
			if (HEIGHT / 2 - i >= 0)
				w->pix[(HEIGHT / 2 - i) * WIDTH + WIDTH / 2] = 0xFF0000;
			if (WIDTH / 2 - i >= 0)
				w->pix[(HEIGHT / 2) * WIDTH + (WIDTH / 2 - i)] = 0xFF0000;
			if (HEIGHT / 2 + i < HEIGHT)
				w->pix[(HEIGHT / 2 + i) * WIDTH + WIDTH / 2] = 0xFF0000;
			if (WIDTH / 2 + i < WIDTH)
				w->pix[(HEIGHT / 2) * WIDTH + (WIDTH / 2 + i)] = 0xFF0000;
			i++;
		}
	}
	if (m->player.hp < 0)
		m->player.hp = 0;
	else if (m->player.hp > m->player.max_hp)
		m->player.hp = m->player.max_hp;
}

void	game_img(t_env *w, t_map *m)
{
	draw(w, m);
	if (m->player.shooting == 1)
		shoot(w, m);
	hand(w, m);
	ft_cursor(w, m);
	if (m->player.hud == 1)
		ft_hud(w, m);
}

void	global_event(t_env *w, t_map *m)
{
	if (w->event.type == SDL_KEYDOWN)
	{
		if (KEY == 27)
		{
			w->menu.i = 1;
			m->stop = 1;
		}
		keydown_events(w, m);
	}
	if (w->event.type == SDL_KEYUP)
		keyup_events(w, m);
	if (w->event.type == SDL_MOUSEMOTION)
		motion_events(w, m);
	if (w->event.type == SDL_MOUSEBUTTONDOWN)
		buttondown_event(w, m);
	if (w->event.type == SDL_MOUSEBUTTONUP)
		buttonup_event(w, m);
}

void	weap_animation(t_env *w, t_map *m)
{
	m->player.bal = m->player.bal + w->sens;
	if (m->player.bal > 80)
		w->sens = -4 * m->player.movespeed;
	if (m->player.bal < -40)
		w->sens = 5 * m->player.movespeed;
	if (m->player.display == 0)
		game_img(w, m);
	else if (m->player.display == 1)
		draw_mini_map(w, m);
	img_update(w);
	get_height(m);
	is_falling(m);
	is_moving(m);
	slow_down(w, m);
	if (m->elevator == 1)
	{
		m->sector[11].floor -= 0.1;
		m->sector[11].ceiling -= 0.1;
		if ((int)m->sector[11].floor == 49)
			m->elevator = 0;
	}
}

void	run(t_env *w, t_map *m)
{
	w->sens = 1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);
	m->stop = 0;
	while (1)
	{
		while (SDL_PollEvent(&w->event))
			global_event(w, m);
		if (m->stop == 1 || m->player.hp == 0 || m->player.sector == m->endsector)
		{
			if (m->player.hp == 0)
				m->game_over = 1;
			if (m->player.sector == m->endsector)
				m->change_lvl = 1;
			break ;
		}
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
		weap_animation(w, m);
		move_all_ennemy(m);
		get_that_time(w);
	}
}
