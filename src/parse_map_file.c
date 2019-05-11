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
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	ft_memreg(tmp);
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
	if (load_sounds(w, m) == -1)
		set_error(w, m, 8, ft_strdup("load_sounds"));
	w->dtime.end = SDL_GetTicks();
	loading = w->dtime.end - w->dtime.start;
	printf("map      loaded in %f seconds !\n", loading / 1000);
}
