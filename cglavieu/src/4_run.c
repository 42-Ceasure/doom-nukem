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

void	main_menu(t_env *w, t_map *m)
{
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_RETURN)
					w->menu.screen = 1;
				if (KEY == 27)
					exit_game(w, m);
			}
			
		}
		if (w->menu.screen == 0)
			hello_screen(w, 1);
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

void	ft_hud(t_env *w)
{
	int i;
	int j;

	i = 0;
	while (i < w->main_pic[2].h)
	{
		j = 0;
		while (j < w->main_pic[2].w)
		{
			w->pix[(i + HEIGHT - w->main_pic[2].h) * WIDTH + (WIDTH / 2 - w->main_pic[2].w / 2 + j)] = w->main_pic[2].pix[i * w->main_pic[2].w + j];
			j++;
		}
		i++;
	}
}

int		run(t_env *w, t_map *m)
{
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
			ft_hud(w);
		}
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		img_update(w);
		get_height(m);
		is_falling(m, w);
		is_moving(m);
		slow_down(w, m);
	}
	return (0);
}
