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
	m->weapon_count = ft_atoi(tmp[0]);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon)
			* m->weapon_count)) == NULL)
		return (-1);
	ft_memreg(tmp);
	return (0);
}

int		parse_line(t_map *m)
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
		ft_putstr("parsing map                 \r");
		if (parse_map_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	if (m->section_number == 2)
	{
		ft_putstr("parsing player               \r");
		if (parse_player_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_player_section");
			return (-1);
		}
	}
	if (m->section_number == 3)
	{
		ft_putstr("parsing weapon              \r");
		if (parse_weapon_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	if (m->section_number == 4)
	{
		ft_putstr("parsing sprites             \r");
		if (parse_sprite_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	ft_memreg(tmp);
	return (0);
}

int		do_parse(t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->w = 0;
	m->section_number = 0;
	ft_putstr("opening file                    \r");
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	ft_putstr("file opened                     \r");
	ft_putstr("reading                         \r");
	while (get_next_line(m->fd, &m->line))
	{
		if ((parse_line(m)) == -1)
		{
			write(2, "error on map collect\n", 22);
			return (-1);
		}
		free(m->line);
	}
	free(m->line);
	close(m->fd);
	return (0);
}

void	parse_map_file(t_env *w, t_map *m)
{
	if (do_parse(m) == -1)
		set_error(w, m, 8, ft_strdup("do_parse"));
	if (load_sounds(w, m) == -1)
		set_error(w, m, 8, ft_strdup("load_sounds"));
	if (ttf_init(w, m) == -1)
		set_error(w, m, 8, ft_strdup("ttf_init"));
}
