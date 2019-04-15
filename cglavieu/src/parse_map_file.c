/*BIG42HEADER*/

#include "doom.h"

int			parse_line(t_map *m)
{
	char	**tmp;

	tmp = ft_strsplit(m->line, ':');
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 1)
	{
		ft_putstr("\rparsing map                 ");
		if (parse_map_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	if (m->section_number == 2)
	{
		ft_putstr("\rparsing player               ");
		if (parse_player_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_player_section");
			return (-1);
		}
	}
	if (m->section_number == 3)
	{
		ft_putstr("\rparsing weapon              ");
		if (parse_weapon_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	if (m->section_number == 4)
	{
		ft_putstr("\rparsing sprites             ");
		if (parse_sprite_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	ft_memreg(tmp);
	return (0);
}

int			do_parse(t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->w = 0;
	m->section_number = 0;
	ft_putstr("\ropening file                    ");
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	ft_putstr("\rfile opened                     ");
	ft_putstr("\rreading                         ");
	while (get_next_line(m->fd, &m->line))
	{
		if ((parse_line(m)) == -1)
		{
			write(1, "error on map collect\n", 22);
			return (-1);
		}
		free(m->line);
	}
	ft_putstr("\rdone                            ");
	free(m->line);
	close(m->fd);
	return (0);
}

void		check_line(t_map *m)
{
	char	**tmp;
	char	**tmp2;
	int		i;

	tmp = ft_strsplit(m->line, ':');
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 1)
	{
		if (ft_strcmp(tmp[0], "\tdots") == 0)
		{
			ft_putstr("\rreading dots            ");
			i = 0;
			tmp2 = ft_strsplit(tmp[2], ',');
			while (tmp2[i++] != NULL)
				m->dots_count++;
			ft_memreg(tmp2);
		}
		if (ft_strcmp(tmp[0], "\tsector") == 0)
		{
			ft_putstr("\rreading sector          ");
			M_S_C++;
		}
	}
	if (m->section_number == 3)
	{
		if (ft_strcmp(tmp[0], "\tweapon") == 0)
		{
			ft_putstr("\rreading weapon          ");
			m->weapon_count++;
		}
	}
	if (m->section_number == 4)
	{
		if (ft_strcmp(tmp[0], "\tweapon_sprite") == 0)
		{
			ft_putstr("\rreading sprite          ");
			m->sprite_count++;
		}
	}
	i = 0;
	ft_memreg(tmp);
}

int			quick_look(t_env *w, t_map *m)
{
	ft_putstr("\ropening file                    ");
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		set_error(w, m, 5, m->map_path);
	ft_putstr("\rfile oppened                    ");
	ft_putstr("\rreading                         ");
	while (get_next_line(m->fd, &m->line))
	{
		check_line(m);
		free(m->line);
	}
	ft_putstr("\rdone                            ");
	free(m->line);
	close(m->fd);
	if (m->dots_count == 0)
		return (-1);
	ft_putstr("\rallocating space                ");
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon) * m->weapon_count)) == NULL)
		return (-1);
	// if ((m->sprite = (t_sprite *)malloc(sizeof(t_sprite) * m->sprite_count)) == NULL)
	// 	return (-1);
	ft_putstr("\rdone                            ");
	return (0);
}

void		parse_map_file(t_env *w, t_map *m)
{
	if (quick_look(w, m) == -1)
		set_error(w, m, 8, ft_strdup("quick_look"));
	if (do_parse(m) == -1)
		set_error(w, m, 8, ft_strdup("do_parse"));
}
