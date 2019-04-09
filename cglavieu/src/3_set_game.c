//

#include "doom.h"

void	set_basics(t_env *w, t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->map_path = "maps/home_sweet_home.dn3d";
	m->map_name = "Home Sweet Home";
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
	m->yaw = 0;
	m->line = NULL;
	m->gravity = BASE_GRAVITY;
	m->maxrenderedsector = 32;
	w->sequential_draw = 0;
	w->window_mode = RESIZABLE_SCREEN;
}

void	set_basic_run(t_map *m)
{
	if (quick_look(m) == -1 || do_parse(m) == -1)
	{
		write(1, "error on map parsing\n", 22);
		exit(0);
	}
}

void	map_cmd(t_map *m, char **cmd)
{
	char **tmp;
	char **tmp2;

	if (cmd[1] == NULL)
	{
		ft_putendl("Please specify a map");
		exit(0);
	}
	m->map_path = cmd[1];
	tmp = ft_strsplit(cmd[1], '/');
	if (tmp == NULL || tmp[1] == NULL)
	{
		ft_putendl("Incorrect path");
		exit(0);
	}
	tmp2 = ft_strsplit(tmp[1], '.');
	m->map_name = tmp2[0];
	// ft_memreg(tmp);
	// ft_memreg(tmp2);
	if (quick_look(m) == -1 || do_parse(m) == -1)
	{
		ft_putendl("\nerror on map,");
		ft_putendl("that can be due to an incorrect map file or an incorrect path");
		exit(0);
	}
}
