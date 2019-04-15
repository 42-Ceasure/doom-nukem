/*BIG42HEADER*/

#include "doom.h"

void			set_basics(t_env *w, t_map *m, int ac)
{
	w->ac = ac;
	m->i = 0;
	m->s = 0;
	m->map_path = ft_strdup("maps/home_sweet_home.dn3d");
	m->map_name = ft_strdup("Home Sweet Home");
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
	w->main_pic = load_img(w, m, "./img/main.bmp");
	w->menu.screen = 0;
	initsprite(&m->sprite, 3);
}

void			init_world(t_env **w, t_map **m, int ac)
{
	if ((*w = (t_env *)malloc(sizeof(t_env))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct world"));
	if ((*m = (t_map *)malloc(sizeof(t_map))) == NULL)
		set_error(*w, *m, 0, ft_strdup("struct map"));
	set_basics(*w, *m, ac);
}

void			exec_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int ac;

	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		l_f_priority_cmd(w, m, cmd);
		if ((init_sdl(w)) == -1)
			set_error(w, m, 4, ft_strdup("SDL Initialisation"));
		parse_map_file(w, m);
		interpret_cmd(w, m, cmd);
	}
	else
		set_error(w, m, 1, ft_strdup(av[1]));
}

void			simple_start(t_env *w, t_map *m)
{
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
	parse_map_file(w, m);
}

void			draw_sequential(t_env *w, t_map *m)
{
	w->event.motion.x = 0;
	w->event.motion.y = 0;
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
	init_world(&w, &m, ac);
	if (ac > 1)
		exec_cmd(w, m, cmd, av);
	else
		simple_start(w, m);
	if (w->sequential_draw == 1)
		draw_sequential(w, m);
	main_menu(w, m);
	return (0);
}
