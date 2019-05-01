/*BIG42HEADER*/

#include "doom.h"

void			generate_config_file(int fd)
{
	int fd2;
	char *line;
	char *path;

	line = NULL;
	path = ft_strdup("usrcfg/base_cfg.dn3d");
	if ((fd2 = open(path, O_RDONLY)) != -1)
	{
		while (get_next_line(fd2, &line))
		{
			ft_putendl_fd(line, fd);
			free(line);
		}
		free(line);
		close(fd2);
	}
	free(path);
}

void			parse_config_file(t_env *w, t_map *m, char *line)
{
	char **tmp;

	tmp = ft_strsplit(line, ':');
	if (tmp[0] != NULL && tmp[1] != NULL)
	{
		if (ft_strcmp(tmp[0], "\twindow_mode") == 0)
			w->window_mode = ft_atoi(tmp[1]);
		else if (ft_strcmp(tmp[0], "\tHfov") == 0)
			m->player.field_of_vision_h = ft_atof(tmp[1]);
		else if (ft_strcmp(tmp[0], "\tVfov") == 0)
			m->player.field_of_vision_v = ft_atof(tmp[1]);
		else if (ft_strcmp(tmp[0], "\tmouse_speed") == 0)
			m->player.mousesp = ft_atof(tmp[1]);
	}
}

void			set_basics(t_env *w, t_map *m, int ac)
{
	int			fd;
	char		*line;
	char		*path;

	line = NULL;
	path = ft_strdup("usrcfg/user_config.dn3d");
	if ((fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0644)) != -1)
	{
		ft_putstr("first launch, creating config file");
		generate_config_file(fd);
		close(fd);
	}
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line))
		{
			parse_config_file(w, m, line);
			free(line);
		}
		free(line);
		close(fd);
	}
	else
		set_error(w, m, 5, path);
	free(path);
	w->i = 0;
	w->ac = ac;
	w->sequential_draw = 0;
	w->win = NULL;
	w->rdr = NULL;
	w->sound.volume = 80;
	w->sound.musique = NULL;
	w->sound.jump = NULL;
	w->sound.ground = NULL;
	w->pix = NULL;
	w->inkeys = NULL;
	w->txtr = NULL;
	w->main_pic[0] = load_img(w, m, "./img/main_screen1.bmp");
	w->main_pic[1] = load_img(w, m, "./img/main_screen2.bmp");
	w->main_pic[2] = load_img(w, m, "./img/main_menu1.bmp");
	w->main_pic[3] = load_img(w, m, "./img/main_menu2.bmp");
	w->main_pic[4] = load_img(w, m, "./img/main_menu3.bmp");
	w->menu.screen = 0;
	w->menu.sel = 0;

	m->launchwmap = 0;
	m->trippymod = 0;
	m->i = 0;
	m->s = 0;
	m->w = 0;
	m->fd = 0;
	m->section_number = 0;
	m->dots_count = 0;
	m->sector_count = 0;
	m->weapon_count = 0;
	m->sprite_count = 0;
	m->maxrenderedsector = 32;
	m->yaw = 0;
	m->gravity = BASE_GRAVITY;
	m->line = NULL;
	m->map_name = NULL;
	m->map_path = NULL;
	m->dot = NULL;
	m->sector = NULL;
	m->weap = NULL;
	m->sprite = NULL;
	m->texture = NULL;
	m->hud.pix = NULL;

	m->player.handed = 0;
	m->player.aiming = 0;
	m->player.firing = 0;
	m->player.sector = 0;
	m->player.hud = 0;
	m->player.coor.x = 0;
	m->player.coor.y = 0;
	m->player.coor.z = 0;
	m->player.memz = 0;
	m->player.move_speed.x = 0;
	m->player.move_speed.y = 0;
	m->player.move_speed.z = 0;
	m->player.move_speedless.x = 0;
	m->player.move_speedless.y = 0;
	m->player.move_speedless.z = 0;
	m->player.angle = 0;
	m->player.anglecos = 0;
	m->player.anglesin = 0;
	m->player.yaw = 0;
	m->player.stance = 0;
	m->player.fall = 1;
	m->player.ground = 0;
	m->player.moving = 0;
	m->player.height = 0;
	m->player.hole_low = 0;
	m->player.hole_high = 0;
	m->player.press = 0;
	m->player.accel = 0;
	m->player.display = 0;
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
