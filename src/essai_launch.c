
int			print_game(t_env *w, t_win *win)
{
	if (win->changemode)
	{
		SDL_SetCursor(win->cursor);
		SDL_BlitSurface(win->helptxt, NULL, win->surface, &win->dst);
	}
	if (win->mode == 4 && win->texture_overed_sector != -1)
		SDL_BlitSurface(win->texturetxt, NULL, win->surface, &win->dst11);
	win->texture = SDL_CreateTextureFromSurface(win->renderer, win->surface);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_GetWindowSize(w->win, &win->w_win, &win->h_win);
	if ((SDL_RenderCopy(win->renderer, win->texture, NULL, &win->dst2)) < 0)
		clear_n_exit(win, 17);
	SDL_RenderPresent(win->renderer);
	SDL_DestroyTexture(win->texture);
	return (0);
}

void		loop_play(t_env *w, t_win *win)
{
	win->surface = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0, 0, 0, 0);
	while (42)
	{
		SDL_WaitEvent(&win->event);
		sdl_event(win);

		on_click(win);
		clear_window(win);
		draw_grid(win);

		if (win->triangles)
			draw_triangulate(win);
		//free_triangles(win);
		if (win->lstlst)
			draw_segments(win);
		if (win->lstasset)
			draw_assets(win);
		mode(win);
		if (win->mode != 2)
			asset_overing(win);
		print_game(w, win);
	}
}

int			init(t_win *win)
{
	if ((win->surface = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, \
		32, 0, 0, 0, 0)) == NULL)
		clear_n_exit(win, 6);
	if (init_struct(win) != 0)
		clear_n_exit(win, 4);
	if (init_assets(win) != 0)
		clear_n_exit(win, 4);
	init_dst(win);
	return (0);
}

int			clear_n_exit(t_win *win, int error)
{
	//put_error(error);
	if (win->surface != NULL)
		SDL_FreeSurface(win->surface);
	if (win->renderer != NULL)
		SDL_DestroyRenderer(win->renderer);
	if (win->police != NULL)
		TTF_CloseFont(win->police);
	SDL_Quit();
	if (error > 0)
		exit(EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

int		level_editor_start(t_env *w)
{
	t_win	win;

	fit_to_editor(w);
	if (argc != 1)
		clear_n_exit(&win, 1);
	if (argv[1] != NULL)
		return (0);
	init(&win);
	loop_play(w, &win);
	return (EXIT_SUCCESS);
}