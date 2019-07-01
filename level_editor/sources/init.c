/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:44:25 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 18:13:13 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	init_dst(t_win *win)
{
	win->dst.x = 250;
	win->dst.y = 20;
	win->dst2.x = 0;
	win->dst2.y = 0;
	win->dst2.w = WIN_X;
	win->dst2.h = WIN_Y;
	win->dst3.x = (WIN_X / 2 - 370 / 8);
	win->dst3.y = (WIN_Y - 305);
	win->dst4.x = 0;
	win->dst4.y = 0;
	win->dst5.x = 500;
	win->dst5.y = 655;
	win->dst6.x = WIN_X - 90;
	win->dst6.y = WIN_Y - 50;
	win->dst7.x = WIN_X - 70;
	win->dst7.y = WIN_Y - 50;
	win->dst8.x = WIN_X - 60;
	win->dst8.y = WIN_Y - 45;
	win->dst9.x = 0;
	win->dst9.y = 0;

	win->color_font_r.r = 119;
	win->color_font_r.g = 136;
	win->color_font_r.b = 153;

	win->w_win = WIN_X;
	win->h_win = WIN_Y;
}

static int	init_assets(t_win *win)
{
	win->police = TTF_OpenFont("resources/fonts/din.ttf", 25);

	win->map_ui = IMG_Load("resources/textures/map_ui.jpg");

	win->asset_sprite = IMG_Load("resources/textures/feather.png");
	win->asset_tmp = NULL;
	win->player_start = IMG_Load("resources/textures/feather.png");
	win->weapon1 = IMG_Load("resources/textures/gun1.png");

	win->helptxt = TTF_RenderText_Blended(win->police,
		"Drawing Mode", win->color_font_r);

	/*win->helptxt = TTF_RenderText_Blended(win->police,
		"test", win->color_font_r);*/

	win->lst = NULL;

	return (0);
}

static int	init_struct(t_win *win)
{
	win->delta_clock = 0;
	win->current_fps = 0;
	win->start_clock = SDL_GetTicks();

	win->drawing = 0;
	win->sector = 0;
	win->link = 0;
	win->left_click = 0;
	win->mode = 0;
	win->moving = 0;
	win->tmp = NULL;
	win->tmpasset = NULL;
	win->lst = NULL;
	win->lstlst = NULL;
	win->lstasset = NULL;
	win->just_close = 0;
	win->color = 255255255;
	win->overed_sector = -1;
	win->triangles = NULL;
	win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
	win->asset = 0;
	win->drawtriangles = 0;
	win->place = 0;
	win->tab = NULL;
	win->changemode = 0;
	win->number = 0;
	win->index_dot = 0;
	win->same_dots = 0;
	win->tab_index = 0;
	win->tab_malloced = 0;

	return (0);
}

static int	init_sdl(t_win *win)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		clear_n_exit(win, 8);
	if (TTF_Init() == -1)
		clear_n_exit(win, 9);
	if ((win->window = SDL_CreateWindow("editor", SDL_WINDOWPOS_CENTERED, \
		SDL_WINDOWPOS_CENTERED, WIN_X, WIN_Y, SDL_WINDOW_SHOWN | \
			SDL_WINDOW_RESIZABLE)) == NULL)
		clear_n_exit(win, 11);
	if ((win->renderer = SDL_CreateRenderer(win->window, -1, \
		SDL_RENDERER_ACCELERATED)) == NULL)
		clear_n_exit(win, 11);
	if ((win->surface = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, \
		32, 0, 0, 0, 0)) == NULL)
		clear_n_exit(win, 6);
	return (0);
}

int			init(t_win *win)
{
	if (init_sdl(win) != 0)
		clear_n_exit(win, 4);
	if (init_struct(win) != 0)
		clear_n_exit(win, 4);
	if (init_assets(win) != 0)
		clear_n_exit(win, 4);
	init_dst(win);
	return (0);
}
