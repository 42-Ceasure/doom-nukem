
#include "doom.h"

void			parse_settings_line(t_env *w, t_map *m, char *line)
{
	char **tmp;
	int check;

	check = 0;
	tmp = ft_strsplit(line, ':');
	while (tmp[check])
		check++;
	if (check != 5)
		set_error(w, m, 911, ft_strdup("error on core settings"));
	if (w->window_mode == -1)
		w->window_mode = ft_atoi(tmp[0]);
	set_screen_res(w, tmp[1]);
	m->player.field_of_vision_h = ft_atof(tmp[2]) * WIDTH / BASEWIDTH;
	m->player.field_of_vision_v = ft_atof(tmp[3]) * HEIGHT / BASEHEIGHT;
	w->mem_field_of_vision_h = m->player.field_of_vision_h;
	w->mem_field_of_vision_v = m->player.field_of_vision_v;
	m->player.mousesp = ft_atof(tmp[4]);
	ft_memreg(tmp);
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
}
