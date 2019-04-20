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

int			do_parse(t_map *m)
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
			write(1, "error on map collect\n", 22);
			return (-1);
		}
		free(m->line);
	}
	ft_putstr("\rdone                            \r");
	free(m->line);
	close(m->fd);
	return (0);
}

void		first_line(char *dest, t_map *m)
{
	char	**tmp;
	char	**tmp2;

	tmp = ft_strsplit(dest, ',');
	tmp2 = ft_strsplit(tmp[0], ':');
	m->dots_count = ft_atoi(tmp2[1]);
	//printf("dot=%d\n", m->dots_count);
	ft_memreg(tmp2);
	tmp2 = ft_strsplit(tmp[1], ':');
	M_S_C = ft_atoi(tmp2[1]);
	//printf("msc=%d\n", M_S_C);
	ft_memreg(tmp2);
	tmp2 = ft_strsplit(tmp[2], ':');
	m->weapon_count = ft_atoi(tmp2[1]);
	//printf("weapon=%d\n", m->weapon_count);
	ft_memreg(tmp2);
	ft_memreg(tmp);
}

int			quick_look(t_env *w, t_map *m)
{
	int		i;
	char	buff[BUFF_SIZE];
	char	*dest;

	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		set_error(w, m, 5, m->map_path);
	i = 0;
	while (read(m->fd, buff + i, 1) == 1)
    {
    	if (buff[i] == '\n')
        	break;
		if (i >= (BUFF_SIZE - 1))
        {
          write(2, "Buffer Overflow\n", 16);
          return (-1);
		}
    	i++;
	}
	close(m->fd);
	buff[i] = '\0';
	dest = malloc(sizeof(char *) * i + 1);
  	ft_strcpy(dest, buff);
	//printf("%s\n", dest);
	first_line(dest, m);
	free(dest);
	if (m->dots_count == 0)
		return (-1);
	ft_putstr("allocating space                 \r");
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon) * m->weapon_count)) == NULL)
		return (-1);
	// if ((m->sprite = (t_sprite *)malloc(sizeof(t_sprite) * m->sprite_count)) == NULL)
	// 	return (-1);
	ft_putstr("done                             \r");
	return (0);
}

void		parse_map_file(t_env *w, t_map *m)
{
	if (quick_look(w, m) == -1)
		set_error(w, m, 8, ft_strdup("quick_look"));
	if (do_parse(m) == -1)
		set_error(w, m, 8, ft_strdup("do_parse"));
}
