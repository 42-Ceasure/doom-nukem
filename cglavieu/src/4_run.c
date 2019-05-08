/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	safe_texture_to_screen(w, w->main_pic[0], 0, 0);
}

void	menu_screen(t_env *w)
{
	safe_texture_to_screen(w, w->main_pic[1], 0, 0);
}

void	main_menu(t_env *w, t_map *m)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_ENABLE);
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
				w->pix[(HEIGHT / 2) * WIDTH + (WIDTH / 2 + i)] = 0xFF0000;
			i++;
		}
	}
}

void	ft_hud(t_env *w, t_map *m)
{
	char	*s;
	t_dot	dot;
	int		x;
	int		y;

	x = WIDTH / 2 - m->hud.w / 2;
	y = HEIGHT - m->hud.h;
	safe_texture_to_screen(w, m->hud, x, y);
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

void	game_img(t_env *w, t_map *m)
{
	draw(w, m);
	hand(w, m);
	ft_cursor(w, m);
	if (m->player.hud == 1)
		ft_hud(w, m);
}

void	sequential_frame(t_env *w, t_map *m)
{
	w->txthead.x = 265;
	w->txthead.y = 236;
	type_str(w, w->txthead, "sequential frame rendering started.", 0xFF000000);
	img_update(w);
	SDL_Delay(1500);
	clean_render(w, 0xFF000000);
	type_str(w, w->txthead, "sequential frame rendering started.", 0xFFFFFFFF);
	img_update(w);
	SDL_Delay(500);
	clean_render(w, 0xFF000000);
	img_update(w);
	game_img(w, m);
	w->sequential_frame = 0;
	w->txthead.x = 313;
	type_str(w, w->txthead, "back to normal in 3 seconds...", 0xFF0000FF);
	img_update(w);
	SDL_Delay(1000);
	game_img(w, m);
	type_str(w, w->txthead, "back to normal in 2 seconds...", 0xFFFFFFFF);
	img_update(w);
	SDL_Delay(1000);
	game_img(w, m);
	type_str(w, w->txthead, "back to normal in 1 seconds...", 0xFFFF0000);
	img_update(w);
	SDL_Delay(1000);
}

void	is_shooting(t_env *w, t_map *m)
{
	if (m->player.shooting == 1)
		shoot(w, m);
}

void	get_that_time(t_env *w)
{
	w->invert = -w->invert;
//--------------------------------------------------------------------------------
	// w->random = 2 * (double)rand() / (double)RAND_MAX - 1;
	// if (w->random == 0)											// rand -1 -> 1  
	// 	w->random = w->invert;						
//--------------------------------------------------------------------------------
	w->random = (double)rand() / (double)RAND_MAX;
	if (w->random == 0)											// rand  0 -> 1  
		w->random = 1;
//--------------------------------------------------------------------------------
	w->dtime.otime = w->dtime.ctime;
	w->dtime.ctime = SDL_GetTicks();
	w->dtime.fps = (w->dtime.ctime - w->dtime.otime) / 1000;
	w->dtime.etime = w->dtime.etime + w->dtime.ctime - w->dtime.otime;
	w->dtime.shootime = w->dtime.shootime + w->dtime.ctime - w->dtime.otime;
}

void	run(t_env *w, t_map *m)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);
	m->stop = 0;
	while (1)
	{
		while (SDL_PollEvent(&w->event))
		{
			if (w->event.type == SDL_KEYDOWN)
			{
				if (KEY == 27)
				{
					if (m->launchwmap == 0)
					{
						w->menu.i = 1;
						m->stop = 1;
					}
					else
						exit_game(w, m, 1);
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
			game_img(w, m);
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		// vect_ab((t_coor){512,0,0},(t_coor){512,575,0},w,0x00000000);
		img_update(w);
		get_height(m);
		is_shooting(w, m);
		is_falling(m, w);
		is_moving(m);
		slow_down(w, m);
		get_that_time(w);
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
