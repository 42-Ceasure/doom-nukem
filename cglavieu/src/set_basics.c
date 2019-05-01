/*BIG42HEADER*/

#include "doom.h"

void			set_config(t_env *w, t_map *m)
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
}

void			set_w(t_env *w, t_map *m, int ac)
{
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
	w->main_pic[0] = load_img(w, m, "./img/main_screen.bmp");
	w->main_pic[1] = load_img(w, m, "./img/main_menu.bmp");
	w->menu.screen = 0;
	w->menu.sel = 0;
}

void			set_m(t_map *m)
{
	m->stop = 0;
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
}

void			set_m_player(t_map *m)
{
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
}
