//

#include "doom.h"

void	set_basics(t_env *w, t_map *m, int ac)
{
	w->ac = ac;
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
