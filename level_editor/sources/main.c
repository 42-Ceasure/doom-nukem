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

#include "editor.h"

int			clear_n_exit(t_win *win, int error)
{
	//put_error(error);
	if (win->surface != NULL)
		SDL_FreeSurface(win->surface);
	if (win->renderer != NULL)
		SDL_DestroyRenderer(win->renderer);
	if (win->window != NULL)
		SDL_DestroyWindow(win->window);
	if (win->police != NULL)
		TTF_CloseFont(win->police);
	TTF_Quit();
	SDL_Quit();
	if (error > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int		main(int argc, char **argv)
{
	t_win	win;

	if (argc != 1)
		clear_n_exit(&win, 1);
	if (argv[1] != NULL)
		return (0);
	init(&win);
	loop_play(&win);
	return (EXIT_SUCCESS);
}
