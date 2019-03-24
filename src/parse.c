//

#include "doom-nukem.h"

void	check_line(t_map *m)
{
	//write(1, "check_line(ok)\n", 16);
	//write(1, "test_check_line(ok)\n", 21);
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
		// if (ft_strcmp(tmp[0], "\tsector") == 0)
		// {
		// 	m->sector_count++;
		// 	i = 0;
		// 	tmp2 = ft_strsplit(tmp[2], ',');
		// 	while (tmp2[i++] != NULL)
		// 		m->sector_wall_count++;
		// }
	}
	free(tmp);
}

int		do_parse(t_map *m)
{
	//write(1, "do_parse(ok)\n", 14);
	m->section_number = 0;
	m->dots_count = 1;
	m->sector_count = 1;
	// m->sector_wall_count = 1;
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	while (get_next_line(m->fd, &m->line))
	{
		check_line(m);
		free(m->line);
	}
	printf("section_number = %d\n", m->section_number);
	printf("dots_count     = %d\n", m->dots_count);
	printf("sector_count   = %d\n", m->sector_count);
	return (0);
}

t_map	set_basic_run(t_env *w)
{
	t_map	map;

	w->i = 0;
	map.map_name = "test";
	map.map_path = "maps/test.dn3d";
	if (do_parse(&map) == -1)
		write(1, "error on file opening\n", 23);
	return (map);
}

t_map	set_advanced_run(t_env *w, char **av)
{
	t_map	map;

	(void)av;
	map = set_basic_run(w);
	return (map);
}
