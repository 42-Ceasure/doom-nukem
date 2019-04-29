/*BIG42HEADER*/

#include "doom.h"

void			generate_config_file(int fd)
{
	ft_putendl_fd("/!\\ section en chantier /!\\", fd);
}

void			set_basics(t_env *w, t_map *m, int ac)
{
	int			fd;
	char		*path;

	path = ft_strdup("usrcfg/user_config.dn3d");
	if ((fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0644)) != -1)
	{
		ft_putstr("first launch, creating config file");
		generate_config_file(fd);
		close(fd);
	}
	free(path);
	w->ac = ac;
	m->i = 0;
	m->s = 0;
	m->map_path = NULL;
	m->map_name = NULL;
	m->weap = NULL;
	m->section_number = 0;
	m->sector_count = 0;
	m->sector = NULL;
	m->dots_count = 0;
	m->dot = NULL;
	m->hud.pix = NULL;
	m->player.field_of_vision_h = WIDTH / 2;
	m->player.field_of_vision_v = HEIGHT / 2;
	m->player.fall = 1;
	m->player.stance = 0;
	m->player.display = 0;
	m->player.handed = 0;
	m->weapon_count = 0;
	m->sprite_count = 0;
	m->yaw = 0;
	m->line = NULL;
	m->gravity = BASE_GRAVITY;
	m->maxrenderedsector = 32;
	m->launchwmap = 0;
	w->pix = NULL;
	w->sequential_draw = 0;
	w->window_mode = RESIZABLE_SCREEN;
	w->main_pic[0] = load_img(w, m, "./img/main_screen1.bmp");
	w->main_pic[1] = load_img(w, m, "./img/main_screen2.bmp");
	w->main_pic[2] = load_img(w, m, "./img/main_menu1.bmp");
	w->main_pic[3] = load_img(w, m, "./img/main_menu2.bmp");
	w->main_pic[4] = load_img(w, m, "./img/main_menu3.bmp");
	w->menu.screen = 0;
	w->menu.sel = 0;
	w->sound.volume = 80;
	// initsprite(&m->sprite, 3);
}

void			init_world(t_env **w, t_map **m, int ac)
{
	process_hint(1, "world");
	if ((*w = (t_env *)malloc(sizeof(t_env))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct world"));
	process_hint(0, " ");
	process_hint(1, "map");
	if ((*m = (t_map *)malloc(sizeof(t_map))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct map"));
	process_hint(0, " ");
	process_hint(2, "basics");
	set_basics(*w, *m, ac);
	process_hint(0, " ");
}

void			exec_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int ac;

	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		process_hint(3, "priority cmd");
		l_f_priority_cmd(w, m, cmd);
		process_hint(0, " ");
		process_hint(2, "SDL2");
		if ((init_sdl(w)) == -1)
			set_error(w, m, 4, ft_strdup("SDL Initialisation"));
		process_hint(0, " ");
		process_hint(4, "map");;
		parse_map_file(w, m);
		process_hint(0, " ");
		process_hint(3, "remaining cmd");
		interpret_cmd(w, m, cmd);
		process_hint(0, " ");
	}
	else
		set_error(w, m, 1, ft_strdup(av[1]));
}

void			simple_start(t_env *w, t_map *m)
{
	process_hint(2, "SDL2");
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
	m->map_path = ft_strdup("maps/home_sweet_home.dn3d");
	m->map_name = ft_strdup("Home Sweet Home");
	parse_map_file(w, m);
	process_hint(0, " ");
}

void			draw_sequential(t_env *w, t_map *m)
{
	w->event.motion.x = 0;
	w->event.motion.y = 0;
	clean_render(w, 0x12000000);
	draw(w, m);
	SDL_Delay(5000);
	exit_game(w, m);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;
	char		***cmd;

	w = NULL;
	m = NULL;
	cmd = NULL;
	process_hint(2, "world");
	init_world(&w, &m, ac);
	process_hint(0, " ");
	if (ac > 1)
	{
		process_hint(4, "cmd");
		exec_cmd(w, m, cmd, av);
		process_hint(0, " ");
	}
	else
	{
		process_hint(3, "basic start");
		simple_start(w, m);
		process_hint(0, " ");
	}
	if (w->sequential_draw == 1)
	{
		process_hint(2, "sequential drawing start");
		draw_sequential(w, m);
	}
	ft_putstr("                              \r");
	if (m->launchwmap == 1)
		run(w, m);
	else
		main_menu(w, m);
	return (0);
}
