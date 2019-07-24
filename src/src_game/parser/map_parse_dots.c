
#include "doom.h"

int			parse_map_dots(t_map *m, char **tab)
{
	int		i;
	char	**tmp;

	i = 0;
	while (tab[i] != NULL)
		i++;
	if (i != 3)
		return (-1);
	tmp = ft_strsplit(tab[2], ',');
	i = 0;
	while (tmp[i] != NULL)
	{
		if (m->i < m->dots_count)
		{
			m->dot[m->i].x = ft_atof(tmp[i]);
			m->dot[m->i].y = ft_atof(tab[1]);
		}
		i++;
		m->i++;
		m->dotsc++;
	}
	if (m->i > m->dots_count)
		return (-1);
	ft_memreg(tmp);
	return (0);
}
