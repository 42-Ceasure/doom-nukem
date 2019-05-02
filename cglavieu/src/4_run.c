/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	t_dot	dot;

	w->i = 0;
	dot.x = 50;
	dot.y = 50;
	while (w->i < w->main_pic[0].h * w->main_pic[0].w)
	{
		if (w->i < w->res.width * w->res.height)
			w->pix[w->i] = w->main_pic[0].pix[w->i];
		w->i++;
	}
	type_str(w, dot, "\ttest :\nCe programme a\nete realise par\n\tagay\n\tcglavieu\n\tochaar", 0x12FFFFFF);
}

void	menu_screen(t_env *w)
{
	w->i = 0;
	while (w->i < w->main_pic[1].h * w->main_pic[1].w)
	{
		if (w->i < w->res.width * w->res.height)
			w->pix[w->i] = w->main_pic[1].pix[w->i];
		w->i++;
	}
}

void	main_menu(t_env *w, t_map *m)
{
	int stop;
	t_dot dot;

	dot.x = 800;
	dot.y = 550;
	stop = 0;
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_RETURN)
				{
					if (w->menu.z < 2)
						w->menu.z++;
				}
				if (KEY == SDLK_UP)
				{
					if (w->menu.y == 0)
						w->menu.y = 2;
					else
						w->menu.y--;
				}
				if (KEY == SDLK_DOWN)
				{
					if (w->menu.y < 2)
						w->menu.y++;
					else
						w->menu.y = 0;
				}
				if (KEY == 27)
				{
					if (w->menu.z == 0)
						stop = 1;
					else
						w->menu.z--;
				}
			}
			
		}
		if (stop == 1)
			break;
		if (w->menu.z == 0)
		{
			hello_screen(w);
			type_str(w, dot, "press enter...", 0x12FEA800);
		}
		else if (w->menu.z == 1)
			menu_screen(w);
		else
			run(w, m);
		img_update(w);
	}
	exit_game(w, m, 1);
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
	while (i < w->hud.h)
	{
		j = 0;
		while (j < w->hud.w)
		{
			if (w->hud.pix[i * w->hud.w + j] != 0xFF000000)
				w->pix[(i + HEIGHT - w->hud.h) * WIDTH + (j + HEIGHT / 2)] = w->hud.pix[i * w->hud.w + j];
			j++;
		}
		i++;
	}
}

void	run(t_env *w, t_map *m)
{
	m->stop = 0;
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == 27)
				{
					w->menu.z = 1;
					m->stop = 1;
				}
				keydown_events(w, m);
			}
			if (w->event.type == SDL_KEYUP)
				keyup_events(w, m);
			if (w->event.type == SDL_MOUSEMOTION)
				motion_events(w, m);
			if (w->event.type == SDL_MOUSEBUTTONDOWN)
				buttondown_event(w, m);
			if (w->event.type == SDL_MOUSEBUTTONUP)
				buttonup_event(w, m);
		}
		if (m->stop == 1)
			break;
		w->inkeys = SDL_GetKeyboardState(NULL);
		key_events(w, m);
		if (m->player.display == 0)
		{
			draw(w, m);
			hand(m, w);
			ft_cursor(w, m);
			if (m->player.hud == 1)
				ft_hud(w);
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
}
