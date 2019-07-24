/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sdl_window.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 11:40:41 by abechet           #+#    #+#             */
/*   Updated: 2019/07/23 11:40:45 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	fit_to_editor(t_env *w, t_win *win)
{
	w->res.width = w->editor_res.width;
	w->res.height = w->editor_res.height;
	if (w->window_mode == 0)
		SDL_SetWindowFullscreen(w->win, 0);
	SDL_SetWindowResizable(w->win, SDL_FALSE);
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
	SDL_SetWindowPosition(w->win, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	free(w->pix);
	if (!(w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED)))
		clear_n_exit(w, win);
	if (!(w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT)))
		clear_n_exit(w, win);
	if (!(w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT)))
		clear_n_exit(w, win);
	clean_render(w, 0x12000000);
	img_update(w);
}

void	fit_to_game(t_env *w)
{
	w->res.width = w->game_res.width;
	w->res.height = w->game_res.height;
	if (w->window_mode == 0)
		SDL_SetWindowFullscreen(w->win, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(w->win, 0);
	SDL_SetWindowResizable(w->win, SDL_TRUE);
	SDL_SetWindowSize(w->win, WIDTH, HEIGHT);
	SDL_SetWindowPosition(w->win, SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyTexture(w->txtr);
	free(w->pix);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
		SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
	clean_render(w, 0x12000000);
	img_update(w);
}
