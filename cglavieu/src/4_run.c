/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	w->i = 0;
	while (w->i < w->main_pic[0].h * w->main_pic[0].w)
	{
		if (w->i < w->res.width * w->res.height)
			w->pix[w->i] = w->main_pic[0].pix[w->i];
		w->i++;
	}
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
	w->txthead.x = 800;
	w->txthead.y = 550;
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == SDLK_ESCAPE)
					w->menu.i = vmax(-1, w->menu.i - 1);
				if (KEY == SDLK_RETURN)
					w->menu.i = vmin(w->menu.i + 1, w->menu.z);
				if (KEY == SDLK_UP)
					w->menu.j = vmax(0, w->menu.j - 1);
				if (KEY == SDLK_DOWN)
					w->menu.j = vmin(w->menu.j + 1, w->menu.y[w->menu.i]);
			}	
		}
		if (w->menu.i == -1)
			exit_game(w, m, 1);
		if (w->menu.i == 0)
		{
			hello_screen(w);
			type_str(w, w->txthead, "press enter...", 0x12FEA800);
		}
		else if (w->menu.i == 1)
			menu_screen(w);
		else
			break;
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

void	ft_hud(t_env *w, t_map *m)
{
	int 	i;
	int 	j;
	char	*s;
	t_dot	dot;

	i = 0;
	while (i < w->hud.h)
	{
		j = 0;
		while (j < w->hud.w)
		{
			if (w->hud.pix[i * w->hud.w + j] != 0xFF00FF00)
				w->pix[(i + HEIGHT - w->hud.h) * WIDTH + (j + HEIGHT / 2)] = w->hud.pix[i * w->hud.w + j];
			j++;
		}
		i++;
		dot.x = 10;
		dot.y = 10;
		type_str(w, dot, "HP : 100", 0x12FF0000);
		dot.x = 10;
		dot.y = HEIGHT - 30;
		type_str(w, dot, "AMMO : ", 0x12000000);
		dot.x = 8 * 14;
		dot.y = HEIGHT - 30;
		s = ft_itoa(m->weap[PH].actu_ammo);
		type_str(w, dot, s, 0x12000000);
		free(s);
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
					w->menu.i = 1;
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
				ft_hud(w, m);
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

void	launch(t_env *w, t_map *m)
{	
	while (1)
	{
		if (w->menu.i != 2)
			main_menu(w, m);
		else
			run(w, m);
	}
}