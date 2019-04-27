/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w, int n)
{
	w->i = 0;
	while (w->i < HEIGHT * WIDTH)
	{
		w->pix[w->i] = w->main_pic[n].pix[w->i];
		w->i++;
	}
}

void	menu_screen(t_env *w, int menu, int sel)
{
	w->i = 0;
	while (w->i < HEIGHT * WIDTH)
	{
		w->pix[w->i] = w->main_pic[menu + sel].pix[w->i];
		w->i++;
	}
}

void	main_menu(t_env *w, t_map *m)
{
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_RETURN)
				{
					if (w->menu.screen == 0)
						w->menu.screen = 1;
					else if (w->menu.screen == 1 && w->menu.sel == 0)
					{
						// m->map_path = ft_strdup("maps/home_sweet_home.dn3d");
						// m->map_name = ft_strdup("Home Sweet Home");
						// parse_map_file(w, m);
						w->menu.screen = 2;
					}
					else if (w->menu.screen == 1 && w->menu.sel == 2)
						exit_game(w, m);
				}
				if (KEY == SDLK_UP)
				{
					if (w->menu.sel == 0)
						w->menu.sel = 2;
					else
						w->menu.sel--;
				}
				if (KEY == SDLK_DOWN)
				{
					if (w->menu.sel < 2)
						w->menu.sel++;
					else
						w->menu.sel = 0;
				}
				if (KEY == 27)
				{
					if (w->menu.screen == 0)
						exit_game(w, m);
					else if (w->menu.screen == 1)
						w->menu.screen = 0;
				}
			}
			
		}
		if (w->menu.screen == 0)
			hello_screen(w, 1);
		else if (w->menu.screen == 1)
			menu_screen(w, w->menu.screen + 1, w->menu.sel);
		else
		{
			if (!run(w, m))
				set_error(w, m, 4, ft_strdup("run"));
		}
		img_update(w);
	}
}

void	ft_cursor(t_env *w, t_map *m)
{
	int i;

	i = 0;
	if (m->player.aiming != 1)
	{
		while (i < 5)
		{
			if (HEIGHT / 2 - i >= 0)
				w->pix[(HEIGHT / 2 - i) * WIDTH + WIDTH / 2] = 0xFF0000;
			if (WIDTH / 2 - i >= 0)
				w->pix[(HEIGHT / 2) * WIDTH + (WIDTH / 2 - i)] = 0xFF0000;
			if (HEIGHT / 2 + i < HEIGHT)
				w->pix[(HEIGHT / 2 + i) * WIDTH + WIDTH / 2] = 0xFF0000;
			if (WIDTH / 2 + i < WIDTH)
				w->pix[HEIGHT / 2 * WIDTH + (WIDTH / 2 + i)] = 0xFF0000;
			i++;
		}
	}
}

void	ft_hud(t_map *m, t_env *w)
{
	int i;
	int j;

	i = 0;
	while (i < m->hud.h)
	{
		j = 0;
		while (j < m->hud.w)
		{
			if (m->hud.pix[i * m->hud.w + j] != m->hud.pix[0])
				w->pix[i * WIDTH + (WIDTH - (m->hud.w * 2) + j)] = m->hud.pix[i * m->hud.w + j];
			j++;
		}
		i++;
	}
}

int		run(t_env *w, t_map *m)
{
	SDL_QueryTexture(w->txtr2, NULL, NULL, 0, 0);
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
				keydown_events(w, m);
			if (w->event.type == SDL_KEYUP)
				keyup_events(w, m);
			if (w->event.type == SDL_MOUSEMOTION)
				motion_events(w, m);
			if (w->event.type == SDL_MOUSEBUTTONDOWN)
				buttondown_event(w, m);
			if (w->event.type == SDL_MOUSEBUTTONUP)
				buttonup_event(w, m);
		}
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
		if (m->player.display == 0)
		{
			draw(w, m);
			hand(m, w);
			ft_cursor(w, m);
			if (m->player.hud == 1)
			{
				ft_hud(m, w);
				SDL_RenderCopy(w->rdr, w->txtr2, NULL, NULL);
				SDL_RenderPresent(w->rdr);
			}
		}
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		// vect_ab((t_coor){512,0,0},(t_coor){512,575,0},w,0x00000000);
		img_update(w);
		get_height(m);
		is_falling(m, w);
		is_moving(m);
		slow_down(w, m);
	}
	return (0);
}
