/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:44:25 by abechet           #+#    #+#             */
/*   Updated: 2019/07/14 15:01:38 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	init_dst(t_win *win)
{
	win->helptxt = NULL;
	win->dst.x = 250;
	win->dst.y = 20;
	win->dst2.x = 0;
	win->dst2.y = 0;
	//win->dst2.w = WIN_X;
	//win->dst2.h = WIN_Y;
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
	win->dst10.x = 300;
	win->dst10.y = 300;
	win->dst11.x = 120;
	win->dst11.y = 310;
	win->dst12.x = 10;
	win->dst12.y = 10;
	win->dst13.x = 40;
	win->dst13.y = 10;
	win->color_font_r = 0xFF0000;
	win->color_font_z = 0xFFFF00;
	win->h_win_tmp = 0;
	win->w_win_tmp = 0;
	win->w_win = WIN_X;
	win->h_win = WIN_Y;
}

static int	init_assets(t_env *w, t_win *win)
{
	win->map_ui = w->m->fire;

	win->asset_sprite = w->m->sprite[10];
	win->asset_tmp = w->m->fire;
	win->player_start = w->m->fire;

	win->inventory = w->m->hud;
	win->slot0 = w->m->fire;
	win->slot1 = w->m->fire;
	win->slot2 = w->m->fire;
	win->slot3 = w->m->fire;
	win->slot4 = w->m->fire;
	win->blackbox = w->m->fire;

	win->building_hud = w->m->hud;

	//type_str(w->win, dot, "Drawing_mode", 0xFFFFFF);

	// win->helptxt = TTF_RenderText_Blended(win->police,"Drawing Mode", 0xFFFFFF);
	//
	// win->texturetxt = TTF_RenderText_Blended(win->police,
	// 	"Wall", win->color_font_z);
	//
	// win->paramtxt = TTF_RenderText_Blended(win->police,
	// 	"HP", win->color_font_z);
	//
	// win->paramvaluetxt = TTF_RenderText_Blended(win->police,
	// 	"100", win->color_font_z);


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
	win->triangle_sector = 0;
	win->check_textures = 0;
	win->texture_choice = 0;
	win->put_texture = 0;
	win->texture_overed_sector = -1;
	win->texture_index = 0;
	win->blackbox_x = 253;
	win->txtr_input_type = 0;
	win->param_index = 0;
	win->hp_value = 100;
	win->gravity_value = 1;
	win->music_value = 1;

	return (0);
}

int			init2(t_env *w, t_win *win)
{
	if (init_struct(win) != 0)
		clear_n_exit(win, 4);
	if (init_assets(w, win) != 0)
		clear_n_exit(win, 4);
	init_dst(win);
	return (0);
}
