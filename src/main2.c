/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:26:31 by abechet           #+#    #+#             */
/*   Updated: 2019/06/12 13:26:44 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int			clear_n_exit(t_win *win, int error)
{
	//put_error(error);
	//if (win->surface != NULL)
	//	SDL_FreeSurface(win->surface);
	//if (win->renderer != NULL)
	//	SDL_DestroyRenderer(win->renderer);
	//if (win->window != NULL)
	//	SDL_DestroyWindow(win->window);
	(void)win;
	if (error > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int		level_editor_start(t_env *w)
{
	t_win	win;

	fit_to_editor(w);
	init2(w, &win);
	loop_play(w, &win);
	return (EXIT_SUCCESS);
}
