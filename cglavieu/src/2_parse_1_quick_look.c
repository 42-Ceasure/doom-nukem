//

#include "doom.h"

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
			ft_memreg(tmp2);
		}
		if (ft_strcmp(tmp[0], "\tsector") == 0)
			m->sector_count++;
	}
	i = 0;
	ft_memreg(tmp);
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
	free(m->line);
	close(m->fd);
	if (m->dots_count == 0)
		return (-1);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * m->sector_count)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	return (0);
}
