/*BIG42HEADER*/

#include "doom.h"



void			set_config(t_env *w, t_map *m)
{
	int			linesc;
	int			buffer;
	char		*path;
	char		**tmp;
	double		loading;

	buffer = 64;
	w->dtime.start = SDL_GetTicks();
	path = ft_strdup("core/core.dn3d");
	if ((m->fd = open(path, O_RDONLY)) != -1)
	{
		while(precise_get_next_line(m->fd, &m->line, buffer))
		{
			tmp = ft_strsplit(m->line, ';');
			if (ft_strncmp(m->line, "buffer", 6) == 0)
				buffer = ft_atoi(tmp[1]);
			else if (ft_strncmp(m->line, "lines", 5) == 0)
				linesc = ft_atoi(tmp[1]);
			else if (ft_strncmp(m->line, "setting", 7) == 0)
				parse_config_line(w, m, tmp[1]);
			else if (ft_strncmp(m->line, "alloc", 5) == 0)
				parse_allocating_line(w, m, tmp[1]);
			else if (ft_strncmp(m->line, "menu", 4) == 0)
				parse_menu_line(w, tmp[1]);
			else if (ft_strncmp(m->line, "weapon", 6) == 0)
				parse_weapon_line(m, tmp[1]);
			else if (ft_strncmp(m->line, "texture", 7) == 0)
				parse_texture_line(w, m, tmp[1]);
			else if (ft_strncmp(m->line, "sprite", 6) == 0)
				parse_sprite_line(w, m, tmp[1]);
			// else if (ft_strncmp(m->line, "", ) == 0)
			// 	;
			ft_memreg(tmp);
			free(m->line);
			w->i++;
		}
		close(m->fd);
	}
	else
		set_error(w, m, 5, path);
	free(path);
	w->dtime.end = SDL_GetTicks();
	loading = w->dtime.end - w->dtime.start;
	printf("settings loaded in %f seconds !\n", loading / 1000);
}

void			set_w(t_env *w, int ac)
{
	w->light_nb = (char *)malloc(sizeof(char) * 12);
	ft_light_itoa(0, w->light_nb);
	w->loading_time = 0;
	w->i = 0;
	w->ac = ac;
	w->asciichk = 0;
	w->asciino = -1;
	w->stopread = 0;
	w->invert = 1;
	w->random = 0;
	w->sequential_draw = 0;
	w->win = NULL;
	w->rdr = NULL;
	w->sound.volume = 80;
	w->sound.musique = NULL;
	w->sound.jump = NULL;
	w->sound.ground = NULL;
	w->sound.reload = NULL;
	w->sound.clic = NULL;
	w->pix = NULL;
	w->inkeys = NULL;
	w->txtr = NULL;
	w->main_pic[0] = pre_init_texture(w->res.width, w->res.height);
	w->main_pic[1] = pre_init_texture(w->res.width, w->res.height);
	w->menu.z = 0;
	w->menu.y = NULL;
	w->menu.i = 0;
	w->menu.j = 0;
	w->menu.list = NULL;
	w->dtime.fps = 0;
	w->dtime.start = 0;
	w->dtime.end = 0;
	w->dtime.ctime = 0;
	w->dtime.otime = 0;
	w->dtime.etime = 0;
	w->dtime.shootime = 0;
	w->dtime.stime = 0;
	w->txthead.x = 0;
	w->txthead.y = 0;
	w->txtnxtline.x = 0;
	w->txtnxtline.y = 0;
	w->txtnxtto.x = 0;
	w->txtnxtto.y = 0;
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
	m->weapon_count = -1;
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
	m->hud = pre_init_texture(0, 0);
}

void			set_m_player(t_map *m)
{
	m->player.bal = 0;
	m->player.fps = (char *)malloc(sizeof(char) * 12);
	ft_light_itoa(0, m->player.fps);
	m->player.stractu_ammo = (char *)malloc(sizeof(char) * 12);
	ft_light_itoa(0, m->player.stractu_ammo);
	m->player.intactu_ammo = 0;
	m->player.handed = 0;
	m->player.aiming = 0;
	m->player.shooting = 0;
	m->player.firing = 0;
	m->player.refresh = 0;
	m->player.switching = 0;
	m->player.recoil = 0;
	m->player.sector = 0;
	m->player.hud = 0;
	m->player.coor.x = 0;
	m->player.coor.y = 0;
	m->player.coor.z = 0;
	m->player.memz = 0;
	m->player.movespeed = 0;
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
	m->player.jump = 0;
	m->player.ground = 0;
	m->player.moving = 0;
	m->player.height = 0;
	m->player.hole_low = 0;
	m->player.hole_high = 0;
	m->player.press = 0;
	m->player.accel = 0;
	m->player.display = 0;
}
