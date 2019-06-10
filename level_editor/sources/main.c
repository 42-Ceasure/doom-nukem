/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:04:11 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 18:12:11 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	free_map(t_win *win)
{
	int		i;

	if (win->map)
	{
		i = 0;
		while (i < win->map_height)
		{
			free(win->map[i]);
			win->map[i] = NULL;
			i++;
		}
		free(win->map);
		win->map = NULL;
	}
}

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
	if (win->theme != NULL)
		Mix_FreeMusic(win->theme);
	if (win->headshot != NULL)
		Mix_FreeChunk(win->headshot);
	if (win->medic != NULL)
		Mix_FreeChunk(win->medic);
	Mix_CloseAudio();
	TTF_Quit();
	SDL_Quit();
	if (win->map != NULL && win->secu == 1)
		free_map(win);
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

	win.map = map(&win);

	init_grid(&win);

	//draw_grid(&win);

	loop_play(&win);

	/*win.secu = 0;
	if (argc != 2)
		clear_n_exit(&win, 1);
	if (!(win.map = get_map(argv[1], &win)))
		clear_n_exit(&win, 2);
	win.secu = 1;
	if (!(check_map(&win)))
		clear_n_exit(&win, 3);
	put_map(win.map);
	if (init(&win) == 1)
		clear_n_exit(&win, 4);
	if (Mix_PlayMusic(win.theme, -1) == -1)
		clear_n_exit(&win, 5);
	loop_intro(&win);
	if (SDL_SetRelativeMouseMode(SDL_TRUE) < 0)
		clear_n_exit(&win, 7);
	loop_play(win);
	clear_n_exit(&win, 0);*/
	return (EXIT_SUCCESS);
}
