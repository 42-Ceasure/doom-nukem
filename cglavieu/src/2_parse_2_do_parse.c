//

#include "doom.h"

int			parse_player_section(t_map *m, char **tab)
{
	char	**tmp;

	if (ft_strcmp(tab[0], "\tplayer_location") == 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		m->player.coor.x = ft_atof(tmp[0]);		// coder ft_atof
		m->player.coor.y = ft_atof(tmp[1]);		// coder ft_atof
		ft_memreg(tmp);
	}
	else if (ft_strcmp(tab[0], "\tplayer_direction") == 0)
	{
		m->player.angle = (ft_atof(tab[1]) * M_PI / 180);		// coder ft_atof
		m->player.anglecos = cos(m->player.angle);
		m->player.anglesin = sin(m->player.angle);
	}
	else if (ft_strcmp(tab[0], "\tplayer_sector") == 0)
	{
		m->player.sector = ft_atoi(tab[1]);
		m->player.coor.z = m->sector[m->player.sector].floor + STAND;
	}
	else
		return (-1);
	return (0);
}

int			parse_line(t_map *m)
{
	char	**tmp;

	tmp = ft_strsplit(m->line, ':');
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 1)
		parse_map_section(m, tmp);
	if (m->section_number == 2)
		parse_player_section(m, tmp);
	ft_memreg(tmp);
	return (0);
}

int		do_parse(t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->section_number = 0;
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(m->fd, &m->line))
	{
		if ((parse_line(m)) == -1)
		{
			write(1, "error on map collect\n", 22);
			return (-1);
		}
		free(m->line);
	}
	free(m->line);
	close(m->fd);
	return (0);
}
