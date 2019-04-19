/*BIG42HEADER*/

#include "doom.h"

void			set_basics(t_env *w, t_map *m, int ac)
{
	w->ac = ac;
	m->i = 0;
	m->s = 0;
	m->map_path = ft_strdup("maps/home_sweet_home.dn3d");
	m->map_name = ft_strdup("Home Sweet Home");
	m->weap = NULL;
	m->section_number = 0;
	m->sector_count = 0;
	m->sector = NULL;
	m->dots_count = 0;
	m->dot = NULL;
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
	w->pix = NULL;
	w->sequential_draw = 0;
	w->window_mode = RESIZABLE_SCREEN;
	w->main_pic[0] = load_img(w, m, "./img/menu.bmp");
	w->main_pic[1] = load_img(w, m, "./img/main1.bmp");
	w->main_pic[2] = load_img(w, m, "./img/hud2.bmp");
	w->menu.screen = 0;
	w->sound.volume = 80;
	// initsprite(&m->sprite, 3);
}

void			init_world(t_env **w, t_map **m, int ac)
{
	ft_putstr("allocate memory for world       \r");
	if ((*w = (t_env *)malloc(sizeof(t_env))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct world"));
	ft_putstr("memory allocated                \r");
	ft_putstr("allocate memory for map         \r");
	if ((*m = (t_map *)malloc(sizeof(t_map))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct map"));
	ft_putstr("memory allocated                \r");
	ft_putstr("setting basics                  \r");
	set_basics(*w, *m, ac);
	ft_putstr("basics set                      \r");
}

void			exec_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int ac;

	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		ft_putstr("pre-processing priority cmd \r");
		l_f_priority_cmd(w, m, cmd);
		ft_putstr("done                        \r");
		ft_putstr("initialisating SDL2         \r");
		if ((init_sdl(w)) == -1)
			set_error(w, m, 4, ft_strdup("SDL Initialisation"));
		ft_putstr("SDL2 initialised            \r");
		ft_putstr("starting pars of map        \r");
		parse_map_file(w, m);
		ft_putstr("map parsed                  \r");
		ft_putstr("processing remaining cmd");
		interpret_cmd(w, m, cmd);
		ft_putstr("done                        \r");
	}
	else
		set_error(w, m, 1, ft_strdup(av[1]));
}

void			simple_start(t_env *w, t_map *m)
{
	ft_putstr("initialisating SDL2             \r");
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
	ft_putstr("SDL2 initialised                \r");
	ft_putstr("starting parse of map           \r");
	parse_map_file(w, m);
	ft_putstr("map parsed                      \r");
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
	ft_putstr("initialisating world              \r");
	init_world(&w, &m, ac);
	ft_putstr("world initialised               \r");
	if (ac > 1)
	{
		ft_putstr("parsing cmd                 \r");
		exec_cmd(w, m, cmd, av);
		ft_putstr("cmd parsed                  \r");
	}
	else
	{
		ft_putstr("basic start                 \r");
		simple_start(w, m);
		ft_putstr("start done                  \r");
	}
	if (w->sequential_draw == 1)
	{
		ft_putstr("sequential drawing start    \r");
		draw_sequential(w, m);
	}
	ft_putstr("                              \r");
	main_menu(w, m);
	return (0);
}
