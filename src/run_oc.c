/*BIG42HEADER*/

#include "doom.h"

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
	if (m->player.hp < 0)
		m->player.hp = 0;
	else if (m->player.hp > 100)
		m->player.hp = 100;
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
	type_str(w, dot, "HP : ", 0x12FF0000);
	ft_light_itoa(m->player.hp, m->player.strhp);
	type_str(w, w->txtnxtto, m->player.strhp, 0x12FF0000);
	dot.y = HEIGHT - 30;
	type_str(w, dot, "AMMO :   ,", 0x12000000);
	if (PH == 1)
		ft_light_itoa(m->player.bullet[1], m->player.strbullet);
	else
		ft_light_itoa(m->player.bullet[0], m->player.strbullet);
	type_str(w, w->txtnxtto, m->player.strbullet, 0x12000000);
	if (m->player.intactu_ammo != m->weap[PH].actu_ammo && m->player.take[PH] == 1)
	{
		m->player.intactu_ammo = m->weap[PH].actu_ammo;
		ft_light_itoa(m->weap[PH].actu_ammo, m->player.stractu_ammo);
	}
	dot.x = 115;
	type_str(w, dot, m->player.stractu_ammo, 0x12000000);
	if (m->player.take[0] == 1)
		final_sprite_to_screen(w, m->sprite[0], 319, HEIGHT - 58, 64, 48);
	if (m->player.take[1] == 1)
		final_sprite_to_screen(w, m->sprite[1], 399, HEIGHT - 60, 64, 48);
	if (m->player.take[2] == 1)
		final_sprite_to_screen(w, m->sprite[2], 480, HEIGHT - 54, 64, 0);
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
	// skybox2(w, w->texturing[2]);
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
	int		i;

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
			sens = -4 * m->player.movespeed;
		if (m->player.bal < -40)
			sens = 5 * m->player.movespeed;
		if (m->player.display == 0)
			game_img(w, m);
		else if (m->player.display == 1)
			draw_mini_map(w, m);
		img_update(w);
		get_height(m);
		is_falling(m);
		is_moving(m);
		slow_down(w, m);
		i = 0;
		while (i < m->ennemy_count)
		{
			is_fall(m, i);
			//if (m->ennemy[i].range < 1 && m->ennemy[i].dead == 0)
			is_moving_enne(m, i);
			i++;
		}
		get_that_time(w);
	}
}
