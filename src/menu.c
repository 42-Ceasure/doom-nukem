/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	safe_texture_to_screen(w, w->main_pic[0], 0, 0);
}

void	menu_screen(t_env *w)
{
	t_dot	dot;

	dot.x = WIDTH / 2 - 50;
	dot.y = 140;
	safe_texture_to_screen(w, w->main_pic[1], 0, 0);
	if (w->menu.j == 1)
	{
		type_str(w, dot, "  NEW GAME\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 2)
	{
		type_str(w, dot, "NEW GAME\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n  MAPS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 3)
	{
		type_str(w, dot, "NEW GAME\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n  SETTINGS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 4)
	{
		type_str(w, dot, "NEW GAME\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n  EDITOR\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else
	{
		type_str(w, dot, "NEW GAME\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n  EXIT", 0xFF78F7);
	}
}


void	affichage_set(t_env *w)
{
	t_dot	dot;

	dot.x = WIDTH - 100;
	dot.y = 10;
	ft_light_itoa(w->window_mode, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->window_res, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->m->player.field_of_vision_h, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->m->player.field_of_vision_v, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.y += 50;
	ft_light_itoa(w->m->player.mousesp, w->light_nb);
	type_str(w, dot, w->light_nb, 0x12FEA800);
	dot.x = w->txthead.x;
	dot.y = w->txthead.y;
}

void	change_key(t_env *w)
{
	if (w->menu.k == 0)
		change_settings(w, w->m);
	if (w->menu.k == 1)
		change_settings(w, w->m);
	if (w->menu.k == 2)
		change_settings(w, w->m);
	if (w->menu.k == 3)
		change_settings(w, w->m);
	if (w->menu.k == 4)
		change_settings(w, w->m);
}

void	settings(t_env *w)
{
	t_dot	dot;

	dot.x = 10;
	dot.y = 10;
	safe_texture_to_screen(w, w->main_pic[1], 0, 0);
	type_str(w, dot, "WINDOW MODE :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "WINDOW RESOLUTION :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "FOV HORIZONTAL :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "FOV VERTIAL :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 2);
				if (KEY == SDLK_RETURN)
					change_key(w);
				if (KEY == SDLK_UP)
					w->menu.k = vmax(0, w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = vmin(w->menu.k + 1, 3);
			}
		}
		affichage_set(w);
		if (w->menu.i != 3)
			{printf("menu i = %d\n", w->menu.i);
			break;}
		img_update(w);
	}
}

void	maps(t_env *w)
{
	t_dot	dot;
	int 	nbmaps;
	char	**names;
	int		i;
	int		color;

	i = 0;
	w->menu.k = 0;
	dot.x = 10;
	dot.y = 10;
	nbmaps = get_nb_maps_in_core(w);
	names = (char **)malloc(sizeof(char *) * (nbmaps + 1));
	get_names_maps_in_core(w, names);
	names[nbmaps] = NULL;
	while (1)
	{
		dot.x = 10;
		dot.y = 10;
		safe_texture_to_screen(w, w->main_pic[1], 0, 0);
		type_str(w, dot, "MAPS :\n", 0xFFFFFFFF);
		dot.x = WIDTH / 2 - 50;
		dot.y = 140;
		i = 0;
		if (names[0] != NULL)
		{
			while (names[i])
			{
				if (i == w->menu.k)
					color = 0xFF78F7;
				else
					color = 0x12FEA800;
				if (i == 0)
					type_str(w, dot, names[i], color);
				else
					type_str(w, w->txtnxtline, names[i], color);
				i++;
			}
		}
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 1);
				// if (KEY == SDLK_RETURN)
				if (KEY == SDLK_UP)
					w->menu.k = vmax(0, w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = vmin(w->menu.k + 1, nbmaps - 1);
			}
		}
		if (w->menu.i != 2)
		{
			i = 0;
			while (names[i])
			{
				free(names[i]);
				i++;
			}
			free(names);
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
				w->menu.i = vmax(-1, w->menu.i - 1);
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
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_ENABLE);
	w->txthead.x = 800;
	w->txthead.y = 550;
	while (1)
	{
		event_menu(w);
		if (w->menu.i == -1)
			exit_game(w, m, 1);
		if (w->menu.i == 0)
		{
			hello_screen(w);
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
	safe_texture_to_screen(w, w->main_pic[2], 0, 0);
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
		else
		{
			if (m->game_over == 1)
				loose(w, m);
			else
			{
				if (m->launchwmap == 0)
				{
					if (parse_map_in_core(w, m, "hsh") != 0)
						continue;
				}
				else
					parse_map_file(w, m);
				run(w, m);
			}
		}
	}
}
