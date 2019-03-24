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
				m->dot[m->i].x = atof(tmp2[i]);		// coder ft_atof
				m->dot[m->i].y = atof(tmp[1]);		// coder ft_atof
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
			m->sector[m->s].floor = atof(tmp1[0]);
			m->sector[m->s].ceiling = atof(tmp1[1]);
			while (tmp2[i] != NULL)
				i++;
			m->sector[m->s].wall_count = i;
			if ((m->sector[m->s].dot = (t_dot *)malloc(sizeof(t_dot) * m->sector[m->s].wall_count)) == NULL)
				return (-1);
			i = 0;
			while(i < m->sector[m->s].wall_count)
			{
				mem = ft_atoi(tmp2[i]);
				m->sector[m->s].dot[i].x = m->dot[mem].x;
			 	m->sector[m->s].dot[i].y = m->dot[mem].y;
				i++;
			}
			m->s++;
			free(tmp1);
			free(tmp2);
		}
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
	//write(1, "do_parse(ok)\n", 14);
	// m->section_number = 0;
	// m->dots_count = 0;
	// m->sector_count = 0;
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

void	recap_parsing(t_map *m)
{
	int i;
	int j;

	i = 0;
	printf("map_section_number = %d\n", m->section_number);
	printf("map_dots_count = %d\n", m->dots_count);
	printf("map_sector_count = %d\n", m->sector_count);
	printf("map_name = %s\n", m->map_name);
	printf("map_path = %s\n", m->map_path);
	while (i < m->dots_count)
	{
		printf("point_%d : x = %f, y = %f\n", i, m->dot[i].x, m->dot[i].y);
		i++;
	}
	i = 0;
	while (i < m->sector_count)
	{
		j = 0;
		printf("sector %d : wall_count = %d\n", i, m->sector[i].wall_count);
		printf("sector %d : floor_height = %f\n", i, m->sector[i].floor);
		printf("sector %d : ceiling_height = %f\n", i, m->sector[i].ceiling);
		while (j < m->sector[i].wall_count)
		{
			printf("point_%d : x = %f, y = %f\n", j, m->dot[j].x, m->dot[j].y);
			j++;
		}
		i++;
	}
}

t_map	set_basic_run(t_env *w)
{
	t_map	map;

	w->i = 0;
	map.i = 0;
	map.s = 0;
	map.section_number = 0;
	map.dots_count = 0;
	map.sector_count = 0;
	map.map_name = "test";
	map.map_path = "maps/test.dn3d";
	map.dot = NULL;
	map.sector = NULL;
	if (quick_look(&map) == -1)
		write(1, "error map measure\n", 19);
	if (do_parse(&map) == -1)
		write(1, "error on map collect\n", 22);
	recap_parsing(&map);
	return (map);
}

t_map	set_advanced_run(t_env *w, char **av)
{
	t_map	map;

	(void)av;
	map = set_basic_run(w);
	return (map);
}
