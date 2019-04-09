//

#include "doom.h"

void	set_advanced(t_map *m)
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
}

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

void	set_basic_run(t_env *w, t_map *m)
{
	if (quick_look(m) == -1 || do_parse(m) == -1)
		set_error(w, m, 12);
}

void	map_cmd(t_env *w, t_map *m, char **cmd)
{
	char **tmp;
	char **tmp2;

	if (cmd[1] == NULL)
		set_error(w, m, 10);
	m->map_path = cmd[1];
	tmp = ft_strsplit(cmd[1], '/');
	if (tmp == NULL || tmp[1] == NULL)
		set_error(w, m, 11);
	tmp2 = ft_strsplit(tmp[1], '.');
	m->map_name = tmp2[0];
	ft_memreg(tmp);
	ft_memreg(tmp2);
}
