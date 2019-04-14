/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	w->i = 0;
	while (w->i < HEIGHT * WIDTH)
	{
		w->pix[w->i] = w->main_pic[w->i];
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
			}
			
		}
		if (w->menu.screen == 0)
			hello_screen(w);
		else
		{
			if (!run(w, m))
				set_error(w, m, 4, ft_strdup("run"));
		}
		img_update(w);
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
		}
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
		if (m->player.display == 0)
		{
			draw(w, m);
			hand(m, w);
		}
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		img_update(w);
		get_height(m);
		is_falling(m);
		is_moving(m);
		slow_down(w, m);
	}
	return (0);
}
