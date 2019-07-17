/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	final_texture_to_screen(w, w->main_pic[0], 0, 0, WIDTH, HEIGHT);
}

void	menu_screen(t_env *w)
{
	t_dot	dot;
	char	*start;

	if (w->m->launchwmap == 0)
		if (w->menu.j == 1)
			start = ft_strdup("> NEW GAME\n");
		else
			start = ft_strdup("NEW GAME\n");
	else
		if (w->menu.j == 1)
			start = ft_strdup("> CONTINUE\n");
		else
			start = ft_strdup("CONTINUE\n");
	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	final_texture_to_screen(w, w->main_pic[1], 0, 0, WIDTH, HEIGHT);
	if (w->menu.j == 1)
	{
		type_str(w, dot, start, 0xFF78F7);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 2)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> MAPS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 3)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> SETTINGS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 4)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EDITOR\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EXIT", 0xFF78F7);
	}
	free(start);
}

void	affichage_set(t_env *w)
{
	t_dot	dot;

	dot.x = WIDTH - 100;
	dot.y = 10;
	ft_light_itoa(w->window_mode_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->window_res_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->fov_h_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->fov_v_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->mousesp_menu, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.x = w->txthead.x;
	dot.y = w->txthead.y;
}

// void	affichage_set(t_env *w)
// {
// 	t_dot	dot;

// 	dot.x = WIDTH - 100;
// 	dot.y = 10;
// 	ft_light_itoa(w->window_mode, w->light_nb);
// 	type_str(w, dot, w->light_nb, 0x12FEA800);
// 	dot.y += 50;
// 	ft_light_itoa(w->window_res, w->light_nb);
// 	type_str(w, dot, w->light_nb, 0x12FEA800);
// 	dot.y += 50;
// 	ft_light_itoa(w->m->player.field_of_vision_h, w->light_nb);
// 	type_str(w, dot, w->light_nb, 0x12FEA800);
// 	dot.y += 50;
// 	ft_light_itoa(w->m->player.field_of_vision_v, w->light_nb);
// 	type_str(w, dot, w->light_nb, 0x12FEA800);
// 	dot.y += 50;
// 	ft_light_itoa(w->m->player.mousesp, w->light_nb);
// 	type_str(w, dot, w->light_nb, 0x12FEA800);
// 	dot.x = w->txthead.x;
// 	dot.y = w->txthead.y;
// }

void	change_value(t_env *w, int direction)
{
	if (w->menu.k == 0)
	{
		if (direction == 1)
			w->window_mode_menu = vmin(w->window_mode_menu + 1, 1);
		else
			w->window_mode_menu = vmax(0, w->window_mode_menu - 1);
	}
	if (w->menu.k == 1)
	{
		if (direction == 1)
			w->window_res_menu = vmin(w->window_res_menu + 1, 2);
		else
			w->window_res_menu = vmax(0, w->window_res_menu - 1);
	}
	if (w->menu.k == 2)
	{
		if (direction == 1)
			w->fov_h_menu = vmin(w->fov_h_menu + 1, 700);
		else
			w->fov_h_menu = vmax(300, w->fov_h_menu - 1);
	}
	if (w->menu.k == 3)
	{
		if (direction == 1)
			w->fov_v_menu = vmin(w->fov_v_menu + 1, 500);
		else
			w->fov_v_menu = vmax(100, w->fov_v_menu - 1);
	}
	// if (w->menu.k == 4)
	// {
	// 	if (direction == 1)
	// 		w->mousesp_menu = vmin(w->mousesp_menu + 0.01, 1.5);
	// 	else
	// 		w->mousesp_menu = vmax(0.5, w->mousesp_menu - 0.01);
	// }
}

void	change_key(t_env *w)
{
	if (w->menu.k == 5)
	{
		w->window_mode = 1;
		w->window_res = 0;
		w->m->player.field_of_vision_h = 512;
		w->m->player.field_of_vision_v = 288;
		w->m->player.mousesp = 1;
	}
	else
	{
		w->window_mode = w->window_mode_menu;
		w->window_res = w->window_res_menu;
		w->m->player.field_of_vision_h = w->fov_h_menu;
		w->m->player.field_of_vision_v = w->fov_v_menu;
		w->m->player.mousesp = w->mousesp_menu;	
	}
	// if (w->menu.k == 0)
	// 	change_settings(w, w->m);
	// if (w->menu.k == 1)
	// 	change_settings(w, w->m);
	// if (w->menu.k == 2)
	// 	change_settings(w, w->m);
	// if (w->menu.k == 3)
	// 	change_settings(w, w->m);
	// if (w->menu.k == 4)
	change_settings(w, w->m);
}

void	settings(t_env *w)
{
	t_dot	dot;

	w->menu.k = 0;
	w->window_mode_menu = w->window_mode;
	w->window_res_menu = w->window_res;
	w->fov_h_menu = w->m->player.field_of_vision_h;
	w->fov_v_menu = w->m->player.field_of_vision_v;
	w->mousesp_menu = w->m->player.mousesp;
	while (1)
	{
		final_texture_to_screen(w, w->main_pic[1], 0, 0, WIDTH, HEIGHT);
		dot.x = 10;
		dot.y = 10;
		if (w->menu.k == 0)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 1)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 2)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 3)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
		}
		else if (w->menu.k == 4)
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0x12FEA800);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0xFFFFFFFF);
		}
		else
		{
			type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "FOV VERTICAL :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
			type_str(w, w->txtnxtline, "RESET TO DEFAULT\n", 0x12FEA800);
		}
		dot.x = WIDTH - 580;
		dot.y = HEIGHT - 55;
		type_str(w, dot, "PRESS ENTER TO SAVE AND APPLY", 0x12FEA800);
		type_str(w, w->txtnxtline, "PLEASE RESTART FOR WINDOW MODE AND RES", 0x12FEA800);
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 2);
				if (KEY == SDLK_RETURN)
				{
					change_key(w);
					w->menu.i = 1;
					break;
				}
				if (KEY == SDLK_UP)
					w->menu.k = vmax(0, w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = vmin(w->menu.k + 1, 5);
				if (KEY == SDLK_RIGHT)
					change_value(w, 1);
				if (KEY == SDLK_LEFT)
					change_value(w, 2);
			}
		}
		affichage_set(w);
		if (w->menu.i != 3)
			break;
		img_update(w);
	} 
}

void	menu_maps_2(t_env *w)
{
	t_dot			dot;
	int 			i;
	int 			j;
	int 			start;
	unsigned int 	color;

	j = 0;
	start = 1;
	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	i = w->menu.k - 5;
	if (i < 0)
		i = w->nbmaps + i;
	while (j < 10)
	{
		if (i >= w->nbmaps)
			i = 0;
		if (i == w->menu.k)
			color = 0xFF78F7;
		else
			color = 0x12FEA800;
		if (start == 1)
			type_str(w, dot, w->namesmaps[i], color);
		else
			type_str(w, w->txtnxtline, w->namesmaps[i], color);
		start = 0;
		i++;
		j++;
	}
}

void	menu_maps_1(t_env *w)
{
	t_dot			dot;
	unsigned int 	color;
	int i;

	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	i = 0;
	while (w->namesmaps[i])
	{
		if (i == w->menu.k)
			color = 0xFF78F7;
		else
			color = 0x12FEA800;
		if (i == 0)
			type_str(w, dot, w->namesmaps[i], color);
		else
			type_str(w, w->txtnxtline, w->namesmaps[i], color);
		i++;
	}
}

void	maps(t_env *w)
{
	t_dot	dot;
	int		i;

	i = 0;
	w->menu.k = 0;
	dot.x = 10;
	dot.y = 10;
	w->nbmaps = get_nb_maps_in_core(w);
	w->namesmaps = (char **)malloc(sizeof(char *) * (w->nbmaps + 1));
	get_names_maps_in_core(w, w->namesmaps);
	w->namesmaps[w->nbmaps] = NULL;
	while (1)
	{
		dot.x = 10;
		dot.y = 10;
		final_texture_to_screen(w, w->main_pic[1], 0, 0, WIDTH, HEIGHT);
		type_str(w, dot, "MAPS :\n", 0xFFFFFFFF);
		if (w->nbmaps > 0 && w->nbmaps <= 10)
			menu_maps_1(w);
		else if (w->nbmaps > 10)
			menu_maps_2(w);
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 1);
				if (KEY == SDLK_RETURN)
				{
					free(w->currmap);
					w->currmap = ft_strdup(w->namesmaps[w->menu.k]);
					w->m->launchwmap = 0;
					// w->menu.i = vmax(-1, w->menu.i - 1);
					w->menu.i = 5;
				}
				if (KEY == SDLK_UP)
					w->menu.k = ((w->menu.k - 1) < 0) ? w->nbmaps - 1 : (w->menu.k - 1);
				// w->menu.k = vmax(0, w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = ((w->menu.k + 1) >= w->nbmaps) ? 0 : (w->menu.k + 1);
				// w->menu.k = vmin(w->menu.k + 1, w->nbmaps - 1);
			}
		}
		if (w->menu.i != 2)
		{
			i = 0;
			while (w->namesmaps[i])
			{
				free(w->namesmaps[i]);
				i++;
			}
			free(w->namesmaps);
			break;
		}
		// si croix pas de fermeture
		img_update(w);
	}
}

void	event_menu(t_env *w)
{
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == SDLK_ESCAPE)
			{
				w->menu.i = vmax(-1, w->menu.i - 1);
				w->m->launchwmap = 0;
			}
			if (KEY == SDLK_RETURN)
			{
				if (w->menu.j == 5)
					w->menu.i = -1;
				else if (w->menu.j == 4)
					w->menu.i = 4;
				else if (w->menu.j == 3)
					w->menu.i = 3;
				else if (w->menu.j == 2)
					w->menu.i = 2;
				else if (w->menu.j == 1)
					w->menu.i = 5;
				else
				{
					w->menu.j = 1;
					w->menu.i = vmin(w->menu.i + 1, 2);
				}
			}
			if (KEY == SDLK_UP)
				w->menu.j = vmax(1, w->menu.j - 1);
			if (KEY == SDLK_DOWN)
				w->menu.j = vmin(w->menu.j + 1, 5);
			if (KEY == SDLK_y)
				fit_to_game(w);
		}
		if (w->event.type == SDL_WINDOWEVENT)
		{
			if (WINDOW == SDL_WINDOWEVENT_CLOSE)
				exit_game(w, w->m, 1);
		}
	}
}

void	main_menu(t_env *w, t_map *m)
{
	t_dot test;

	test.x = 10;
	test.y = 10;
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_ENABLE);
	w->txthead.x = 800;
	w->txthead.y = 550;
	w->menu.j = 1;
	while (1)
	{
		event_menu(w);
		if (w->menu.i == -1)
			exit_game(w, m, 1);
		if (w->menu.i == 0)
		{
			hello_screen(w);
			type_str(w, test, "\" { } @ \\ ^^ <> [] # $ = - () % | + / * ~ \' ; _", 0x12FEA800);
			type_str(w, w->txtnxtline, "si je ne m'abuse vous me demanderez plus de caractere", 0x12FEA800);
			type_str(w, w->txtnxtline, "ascii d'ici un petit moment !", 0x12FEA800);
			type_str(w, w->txtnxtline, "\nc===3", 0x12FEA800);
			type_str(w, w->txthead, "press enter...", 0x12FEA800);
			w->menu.j = -1;
		}
		else if (w->menu.i == 1)
			menu_screen(w);
		else
			break;
		img_update(w);
		get_that_time(w);
	}
}

void	loose(t_env *w, t_map *m)
{
	final_texture_to_screen(w, w->main_pic[2], 0, 0, WIDTH, HEIGHT);
	w->txthead.x = 350;
	w->txthead.y = 400;
	type_str(w, w->txthead, "Press enter to retry", 0x12FFFFFF);
	while (SDL_PollEvent(&w->event))
	{
		if (w->event.type == SDL_KEYDOWN)
		{
			if (KEY == 27)
				exit_game(w, m, 1);
			if (KEY == SDLK_RETURN)
			{
				m->game_over = 0;
				m->player.hp = m->player.max_hp;
			}
		}
	}
	img_update(w);
}

void	launch(t_env *w, t_map *m)
{	
	while (1)
	{
		if (w->menu.i < 2)
			main_menu(w, m);
		else if (w->menu.i == 2)
			maps(w);
		else if (w->menu.i == 3)
			settings(w);
		else if (w->menu.i == 4)
			level_editor_start(w);
		if (w->menu.i > 4)
		{
			if (m->game_over == 1)
				loose(w, m);
			else
			{
				if (m->launchwmap == 0)
				{
					if (parse_map_in_core(w, m, w->currmap) != 0)
						continue;
				}
				printf("no end sector : %d\n", m->endsector);
				printf("linklvl : %s\n", m->linklvl);
				// else
				// 	parse_map_file(w, m);
				run(w, m);
			}
		}
	}
}
