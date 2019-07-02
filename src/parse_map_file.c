/*BIG42HEADER*/

#include "doom.h"

int		first_line(char **tab, t_map *m)
{
	char	**tmp;

	tmp = ft_strsplit(tab[1], ',');
	m->dots_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[2], ',');
	M_S_C = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[3], ',');
	m->sprite_map_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[4], ',');
	m->ennemy_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->sprt = (t_map_sprite *)malloc(sizeof(t_map_sprite) * m->sprite_map_count)) == NULL)
		return (-1);
	if ((m->ennemy = (t_ennemy *)malloc(sizeof(t_ennemy) * m->ennemy_count)) == NULL)
		return (-1);
	return (0);
}

int		parse_sprite_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;
	
	if (ft_strcmp(tab[0], "Section") != 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		nb = ft_atoi(tmp[0]);
		m->sprt[nb].name = ft_strdup(tab[0]);
		m->sprt[nb].index = ft_atoi(tmp[1]);
		m->sprt[nb].sector = ft_atoi(tmp[2]);
		m->sprt[nb].sx = ft_atof(tmp[3]);
		m->sprt[nb].sy = ft_atof(tmp[4]);
		m->sprt[nb].vis = 1;
		m->sprt[nb].range = 0.5;
	}
	return (0);
}

int		parse_ennemy_map(t_map *m, char **tab)
{
	char	**tmp;
	int		nb;
	
	if (ft_strcmp(tab[0], "Section") != 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		nb = ft_atoi(tmp[0]);
		//m->sprt[nb].name = ft_strdup(tab[0]);
		m->ennemy[nb].index = ft_atoi(tmp[1]);
		m->ennemy[nb].sector = ft_atoi(tmp[2]);
		m->ennemy[nb].coor.x = ft_atof(tmp[3]);
		m->ennemy[nb].coor.y = ft_atof(tmp[4]);
		m->ennemy[nb].coor.z = m->sector[m->ennemy[nb].sector].floor + STAND;
		m->ennemy[nb].range = 0.5;
		m->ennemy[nb].dead = 0;
		m->ennemy[nb].is_dead = 0;
		m->ennemy[nb].die = 1;
		m->ennemy[nb].count = 0;
		m->ennemy[nb].cpt = 0;
		m->ennemy[nb].nb_ammo = 0;
		m->ennemy[nb].touche = 0;
		if (!(m->ennemy[nb].dammage = Mix_LoadWAV("./sounds/oof.wav")))
			return (-1);
		Mix_VolumeChunk(m->ennemy[nb].dammage, 110);
		m->ennemy[nb].move_speed.x = 0;
		m->ennemy[nb].move_speed.y = 0;
		m->ennemy[nb].move_speed.z = 0;
		m->ennemy[nb].move_speedless.x = 0;
		m->ennemy[nb].move_speedless.y = 0;
		m->ennemy[nb].move_speedless.z = 0;
		m->ennemy[nb].fall = 1;
		m->ennemy[nb].ground = 0;
		m->ennemy[nb].moving = 0;
		m->ennemy[nb].height = 0;
		m->ennemy[nb].hole_low = 0;
		m->ennemy[nb].hole_high = 0;
	}
	return (0);
}

int		parse_line(t_env *w, t_map *m)
{
	char	**tmp;

	tmp = ft_strsplit(m->line, ':');
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 0)
	{
		if (first_line(tmp, m) == -1)
			return (-1);
	}
	if (m->section_number == 1)
	{
		process_hint_w(w, 4, "map");
		if (parse_map_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	else if (m->section_number == 2)
	{
		process_hint_w(w, 4, "player");
		if (parse_player_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_player_section");
			return (-1);
		}
	}
	else if (m->section_number == 3)
	{
		if (parse_sprite_map(m, tmp) == -1)
		{
			ft_putendl("error in parse_sprite_map");
			return (-1);
		}
	}
	else if (m->section_number == 4)
	{
		if (parse_ennemy_map(m, tmp) == -1)
		{
			ft_putendl("error in parse_sprite_map");
			return (-1);
		}
	}
	ft_memreg(tmp);
	return (0);
}

int		do_parse(t_env *w, t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->w = 0;
	m->section_number = 0;
	process_hint_w(w, 6, "map file");
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	process_hint_w(w, 0, " ");
	process_hint_w(w, 6, " ");
	while (get_next_line(m->fd, &m->line) && w->stopread == 0)
	{
		if ((parse_line(w, m)) == -1)
		{
			write(2, "error on map collect\n", 22);
			return (-1);
		}
		free(m->line);
	}
	process_hint_w(w, 0, " ");
	free(m->line);
	close(m->fd);
	return (0);
}

void	parse_map_file(t_env *w, t_map *m)
{
	double	loading;

	w->dtime.start = SDL_GetTicks();
	if (do_parse(w, m) == -1)
		set_error(w, m, 8, ft_strdup("do_parse"));
	w->dtime.end = SDL_GetTicks();
	loading = w->dtime.end - w->dtime.start;
	printf("map      loaded in %f seconds !\n", loading / 1000);
}
