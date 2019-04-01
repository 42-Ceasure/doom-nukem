//

#include "doom-nukem.h"

int			parse_line(t_map *m)
{
	char	**tmp;
	char	**tmp1;
	char	**tmp2;
	int		mem;
	int		i;

	tmp = ft_strsplit(m->line, ':');
	if (ft_strcmp(tmp[0], "Section") == 0)
		m->section_number++;
	if (m->section_number == 1)
	{
		if (ft_strcmp(tmp[0], "\tdots") == 0)
		{
			i = 0;
			tmp2 = ft_strsplit(tmp[2], ',');
			while (tmp2[i] != NULL)
			{
				m->dot[m->i].x = ft_atof(tmp2[i]);		// coder ft_atof
				m->dot[m->i].y = ft_atof(tmp[1]);		// coder ft_atof
				m->i++;
				i++;
			}
			free(tmp2);
		}
		if (ft_strcmp(tmp[0], "\tsector") == 0)
		{
			i = 0;
			tmp1 = ft_strsplit(tmp[1], ',');		// floor H, ceiling H
			tmp2 = ft_strsplit(tmp[2], ',');		// walls
			m->sector[m->s].floor = ft_atof(tmp1[0]);
			m->sector[m->s].ceiling = ft_atof(tmp1[1]);
			while (tmp2[i] != NULL)
				i++;
			m->sector[m->s].wall_count = i;
			if ((m->sector[m->s].dot = (t_dot *)malloc(sizeof(t_dot) * m->sector[m->s].wall_count)) == NULL)
				return (-1);
			if ((m->sector[m->s].network = (char **)malloc(sizeof(char *) * m->sector[m->s].wall_count)) == NULL)
				return (-1);
			i = 0;
			while (i < m->sector[m->s].wall_count)
			{
				mem = ft_atoi(tmp2[i]);
				m->sector[m->s].dot[i].x = m->dot[mem].x;
			 	m->sector[m->s].dot[i].y = m->dot[mem].y;
				i++;
			}
			i = 0;
			free(tmp2);
			tmp2 = ft_strsplit(tmp[3], ',');		//connections
			while (i < m->sector[m->s].wall_count)
			{
				m->sector[m->s].network[i] = ft_strnew(ft_strlen(tmp2[i]));
				m->sector[m->s].network[i] = ft_strcpy(m->sector[m->s].network[i], tmp2[i]);
				i++;
			}
			m->s++;
			free(tmp1);
			free(tmp2);
		}
	}
	if (m->section_number == 2)
	{
		if (ft_strcmp(tmp[0], "\tplayer_location") == 0)
		{
			tmp1 = ft_strsplit(tmp[1], ',');
			m->player.coor.x = ft_atof(tmp1[0]);		// coder ft_atof
			m->player.coor.y = ft_atof(tmp1[1]);		// coder ft_atof
		}
		if (ft_strcmp(tmp[0], "\tplayer_direction") == 0)
		{
			m->player.angle = (ft_atof(tmp[1]) * M_PI / 180);		// coder ft_atof
			m->player.anglecos = cos(m->player.angle);
			m->player.anglesin = sin(m->player.angle);
		}
		if (ft_strcmp(tmp[0], "\tplayer_sector") == 0)
		{
			m->player.sector = ft_atoi(tmp[1]);
			m->player.coor.z = m->sector[m->player.sector].floor + STANDH;
		}
		free(tmp1);
	}
	free(tmp);
	return (0);
}

void	check_line(t_map *m)
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
			i = 0;
			tmp2 = ft_strsplit(tmp[2], ',');
			while (tmp2[i++] != NULL)
				m->dots_count++;
			free(tmp2);
		}
		if (ft_strcmp(tmp[0], "\tsector") == 0)
			m->sector_count++;
	}
	free(tmp);
}

int		quick_look(t_map *m)
{
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(m->fd, &m->line))
	{
		check_line(m);
		free(m->line);
	}
	close(m->fd);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * m->sector_count)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
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
			write(1, "error on map collect\n", 22);
		free(m->line);
	}
	close(m->fd);
	return (0);
}
