/*BIG42HEADER*/

#include "doom.h"

void			set_screen_res(t_env *w, char *aspect)
{
	int			n;

	n = ft_atoi(aspect);
	if (n == 0) //			16/9
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
	else if (n == 1)
	{
		w->res.width = 1920;
		w->res.height = 1080;
	}
	else if (n == 2)
	{
		w->res.width = 800;
		w->res.height = 600;
	}
	else
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
}

void			parse_weapon_line(t_map *m, char *line)
{
	char			**tmp;
	char			**tmp2;

	tmp2 = ft_strsplit(line, ':');
	m->weap[m->w].name = ft_strdup(tmp2[0]);
	tmp = ft_strsplit(tmp2[1], ',');
	if (tmp != NULL)
	{	
		m->weap[m->w].range = ft_atoi(tmp[0]);
		if (tmp[1])
			m->weap[m->w].firerate = ft_atoi(tmp[1]);
		if (tmp[2])
			m->weap[m->w].accuracy = ft_atoi(tmp[2]);
		if (tmp[3])
			m->weap[m->w].dispertion = ft_atof(tmp[3]);
		if (tmp[4])
			m->weap[m->w].ammo = ft_atoi(tmp[4]);
		if (tmp[5])
		{
			m->weap[m->w].magazine = ft_atoi(tmp[5]);
			m->weap[m->w].actu_ammo = m->weap[m->w].magazine;
		}
		if (tmp[6])
			m->weap[m->w].recoil = ft_atoi(tmp[6]);
	}
	if (tmp2[2])
		m->weap[m->w].reloadtime = ft_atof(tmp[2]);
	ft_memreg(tmp2);
	ft_memreg(tmp);
	m->w++;
}

void			parse_texture_line(t_env *w, t_map *m, char *line)
{
	char		**tmp;

	w->txthead.x = 800;
	w->txthead.y = 550;
	tmp = ft_strsplit(line, ':');
	if (ft_strcmp(tmp[0], "ascii") == 0)
	{
		w->ascii[w->asciichk] = parse_texture(w, m, tmp);
		w->asciichk++;
	}
	if (ft_strcmp(tmp[0], "main_pic[0]") == 0)
	{
		w->main_pic[0] = parse_texture(w, m, tmp);
		hello_screen(w);
		type_str(w, w->txthead, "loading game...", 0x12FEA800);
		img_update(w);
	}
	if (ft_strcmp(tmp[0], "main_pic[1]") == 0)
			w->main_pic[1] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud") == 0)
		m->hud = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "fire") == 0)
		m->fire = parse_texture(w, m, tmp);
	ft_memreg(tmp);
}

void			parse_sprite_line(t_env *w, t_map *m, char *line)
{
	char 		**tab;

	tab = ft_strsplit(line, ':');
	if (ft_strcmp(tab[0], "weapon_sprite") == 0)
	{
		process_hint_w(m->world, 4, "weapon sprite");
		if (parse_weapon_sprite(m, tab[1], tab[2], tab[3]) == -1)
			set_error(w, m, 8, ft_strdup("weapon sprite"));
	}
}

void			parse_allocating_line(t_env *w, t_map *m, char *line)
{
	char **tmp;

	tmp = ft_strsplit(line, ':');
	if (ft_strcmp(tmp[0], "weapon") == 0)
		m->weapon_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "ascii") == 0)
		w->asciino = ft_atoi(tmp[1]);
	if (w->asciino > 0 && m->weapon_count > 0)
	{
		if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon)
			* m->weapon_count)) == NULL)
				set_error(w, m, 0, ft_strdup("weapon"));
		if ((w->ascii = (t_texture *)malloc(sizeof(t_texture)
			* w->asciino)) == NULL)
				set_error(w, m, 0, ft_strdup("ascii"));
	}
}

void			parse_config_line(t_env *w, t_map *m, char *line)
{
	char **tmp;

	tmp = ft_strsplit(line, ':');
	w->window_mode = ft_atoi(tmp[0]);
	set_screen_res(w, tmp[1]);
	m->player.field_of_vision_h = ft_atof(tmp[2]);
	m->player.field_of_vision_v = ft_atof(tmp[3]);
	m->player.mousesp = ft_atof(tmp[4]);
	ft_memreg(tmp);
	if ((init_sdl(w)) == -1)
		set_error(w, m, 4, ft_strdup("SDL Initialisation"));
}
