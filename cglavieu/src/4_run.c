/*BIG42HEADER*/

#include "doom.h"

void	hello_screen(t_env *w)
{
	safe_texture_to_screen(w, w->main_pic[0], 0, 0);
}

void	menu_screen(t_env *w)
{
	t_dot dot;

	dot.x = 50;
	dot.y = 50;
	safe_texture_to_screen(w, w->main_pic[1], 0, 0);
	type_str(w, dot, "le menu n'est pas encore construit,", 0x12FEA800);
	type_str(w, w->txtnxtline, "vous etes libres d'appuyer sur enter\n", 0x12FEA800);
	type_str(w, w->txtnxtline, "ochaar, on peut desormais cliquer sur la croix pour quitter !", 0x12FEA800);
	type_str(w, w->txtnxtline, "\n\n\n\n", 0x127FFF00);
	type_str(w, w->txtnxtline, "txtnxtline permet d'ecrire du texte a la ligne apres", 0x127FFF00);
	type_str(w, w->txtnxtline, "le dernier texte affiche", 0x127FFF00);
	type_str(w, w->txtnxtline, "j'en fais un usage excessif ici.", 0x127FFF00);
	type_str(w, w->txtnxtline, "p.s. ca, c'est ma couleur preferee 7fff00", 0x127FFF00);
	type_str(w, w->txtnxtline, "\ntest du ", 0x127FFF00);
	type_str(w, w->txtnxtto, "txtnxtto", 0x127FFF00);
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
			if (w->event.type == SDL_WINDOWEVENT)
			{
				if (WINDOW == SDL_WINDOWEVENT_CLOSE)
					exit_game(w, m, 1);
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
		get_that_time(w);
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
	t_dot	dot;
	int		x;
	int		y;

	x = WIDTH / 2 - m->hud.w / 2;
	y = HEIGHT - m->hud.h;
	safe_texture_to_screen(w, m->hud, x, y);
	dot.x = 10;
	dot.y = 10;
	type_str(w, dot, "HP : 100", 0x12FF0000);
	dot.y = HEIGHT - 30;
	type_str(w, dot, "AMMO : ", 0x12000000);
	if (m->player.intactu_ammo != m->weap[PH].actu_ammo)
	{
		m->player.intactu_ammo = m->weap[PH].actu_ammo;
		ft_light_itoa(m->weap[PH].actu_ammo, m->player.stractu_ammo);
	}
	type_str(w, w->txtnxtto, m->player.stractu_ammo, 0x12000000);
	dot.x = WIDTH - 130;
	dot.y = 10;
	type_str(w, dot, "FPS : ", 0x12000000);
	if (w->dtime.stime == 0)
		ft_light_itoa(w->dtime.fps, m->player.fps);
	type_str(w, w->txtnxtto, m->player.fps, 0x12000000);
}

void	is_shooting(t_env *w, t_map *m)
{
	if (m->player.shooting == 1)
		shoot(w, m);
	hand(w, m);
}

void	game_img(t_env *w, t_map *m)
{
	draw(w, m);
	is_shooting(w, m);
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

void	run(t_env *w, t_map *m)
{
	int 	sens;

	sens = 1;
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
		m->player.bal = m->player.bal + sens;
		if (m->player.bal > 80)
			sens = -6 * m->player.movespeed;
		if (m->player.bal < -40)
			sens = 8 * m->player.movespeed;
		if (m->player.display == 0)
			game_img(w, m);
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		img_update(w);
		get_height(m);
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
