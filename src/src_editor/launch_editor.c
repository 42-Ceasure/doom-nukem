/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/12 13:26:31 by abechet           #+#    #+#             */
/*   Updated: 2019/07/16 17:38:39 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	clear_n_exit(t_env *w, t_win *win)
{
	if (win->helptxt != NULL)
		free(win->helptxt);
	free_listlist(win);
	free_triangles(win);
	free_assets(win);
	w->stopread = 1;
}

int		level_editor_start(t_env *w)
{
	t_win	win;

	fit_to_editor(w);
	init2(w, &win);
	loop_play(w, &win);
	w->menu.i = 1;
	return (EXIT_SUCCESS);
}
