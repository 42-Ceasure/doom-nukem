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
	dot.y = 200;
	safe_texture_to_screen(w, w->main_pic[1], 0, 0);
	/*type_str(w, dot, "le menu n'est pas encore construit,", 0x12FEA800);
	type_str(w, w->txtnxtline, "vous etes libres d'appuyer sur enter\n", 0x12FEA800);
	type_str(w, w->txtnxtline, "ochaar, on peut desormais cliquer sur la croix pour quitter !", 0x12FEA800);
	type_str(w, w->txtnxtline, "\n\n\n\n", 0x127FFF00);
	type_str(w, w->txtnxtline, "txtnxtline permet d'ecrire du texte a la ligne apres", 0x127FFF00);
	type_str(w, w->txtnxtline, "le dernier texte affiche", 0x127FFF00);
	type_str(w, w->txtnxtline, "j'en fais un usage excessif ici.", 0x127FFF00);
	type_str(w, w->txtnxtline, "p.s. ca, c'est ma couleur preferee 7fff00", 0x127FFF00);
	type_str(w, w->txtnxtline, "\ntest du ", 0x127FFF00);
	type_str(w, w->txtnxtto, "txtnxtto", 0x127FFF00);*/
	if (w->menu.j == 1)
	{
		type_str(w, dot, "  NEW GAME\n\n", 0xFFFF0000);
		type_str(w, w->txtnxtline, "\n\nSETTINGS\n\n", 0xFFFFFFFF);
		type_str(w, w->txtnxtline, "\n\nEXIT", 0xFFFFFFFF);
	}
	else if (w->menu.j == 2)
	{
		type_str(w, dot, "NEW GAME\n\n", 0xFFFFFFFF);
		type_str(w, w->txtnxtline, "\n\n  SETTINGS\n\n", 0xFFFF0000);
		type_str(w, w->txtnxtline, "\n\nEXIT", 0xFFFFFFFF);
	}
	else
	{
		type_str(w, dot, "NEW GAME\n\n", 0xFFFFFFFF);
		type_str(w, w->txtnxtline, "\n\nSETTINGS\n\n", 0xFFFFFFFF);
		type_str(w, w->txtnxtline, "\n\n  EXIT", 0xFFFF0000);
	}
}

void	affichage_set(t_env *w)
{
	t_dot	dot;

	type_str(w, w->txthead, "W\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "S\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "D\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "A\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, ft_itoa(w->m->player.mousesp), 0xFFFFFFFF);
	dot.x = w->txthead.x;
	dot.y = w->txthead.y;
	if (w->menu.k == 0)
		type_str(w, w->txthead, " W\n", 0xFFFFFFFF);
	else if (w->menu.k == 1)
		type_str(w, dot, " S\n", 0xFFFFFFFF);
	else if (w->menu.k == 2)
		type_str(w, dot, " D\n", 0xFFFFFFFF);
	else if (w->menu.k == 3)
		type_str(w, dot, " A\n", 0xFFFFFFFF);
}

void	settings(t_env *w)
{
	t_dot	dot;

	dot.x = 10;
	dot.y = 10;
	safe_texture_to_screen(w, w->main_pic[1], 0, 0);
	type_str(w, dot, "MOVE FORWARD :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "MOVE BACKWARD :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "MOVE RIGHT :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "MOVE LEFT :\n", 0xFFFFFFFF);
	type_str(w, w->txtnxtline, "MOUSE SENSITIVITY :\n", 0xFFFFFFFF);
	dot.x = WIDTH - 60;
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 1);
				if (KEY == SDLK_RETURN)
				{
					printf("k=%d\n", w->menu.k);
				}
				if (KEY == SDLK_UP)
					w->menu.k = vmax(0, w->menu.k - 1);
				if (KEY == SDLK_DOWN)
					w->menu.k = vmin(w->menu.k + 1, 3);
			}
		}
		//affichage_set(w);
		if (w->menu.i != 2)
			break;
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
				if (w->menu.j == 3)
					w->menu.i = -1;
				else if (w->menu.j == 2)
					w->menu.i = 2;
				else if (w->menu.j == 1)
					w->menu.i = 3;
				else
				{
					w->menu.j = 1;
					w->menu.i = vmin(w->menu.i + 1, 2);
				}
			}
			if (KEY == SDLK_UP)
				w->menu.j = vmax(1, w->menu.j - 1);
			if (KEY == SDLK_DOWN)
				w->menu.j = vmin(w->menu.j + 1, 3);
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


void	launch(t_env *w, t_map *m)
{	
	while (1)
	{
		if (w->menu.i < 2)
			main_menu(w, m);
		else if (w->menu.i == 2)
			settings(w);
		else
			run(w, m);
	}
}
