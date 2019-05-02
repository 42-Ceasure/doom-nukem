/*BIG42HEADER*/

#include "doom.h"

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

void			set_basics(t_env *w, t_map *m, int ac)
{
	set_config(w, m);
	set_w(w, ac);
	set_m(m);
	set_m_player(m);
}

void			simple_start(t_env *w, t_map *m)
{
	process_hint(2, "SDL2");
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
	m->map_path = ft_strdup("maps/home_sweet_home.dn3d");
	m->map_name = ft_strdup("Home Sweet Home");
	process_hint(0, " ");
	process_hint(4, "core file");
	load_core(w, m);
	process_hint(0, " ");
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
	exit_game(w, m, 1);
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
	exit_game(w, m, 0);
	return (0);
}
