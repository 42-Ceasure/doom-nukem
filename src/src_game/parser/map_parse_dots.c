
#include "doom.h"

int			parse_map_dots(t_map *m, char *y, char *x)
{
	int		i;
	char	**tmp;

	i = 0;
	tmp = ft_strsplit(x, ',');
	while (tmp[i] != NULL)
	{
		if (m->i < m->dots_count)
		{
			m->dot[m->i].x = ft_atof(tmp[i]);
			m->dot[m->i].y = ft_atof(y);
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
