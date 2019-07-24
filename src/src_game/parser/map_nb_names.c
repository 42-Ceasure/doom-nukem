
#include "doom.h"

int			get_nb_maps_in_core(t_env *w)
{
	int		nbmaps;

	nbmaps = 0;
	w->stopread = 0;
	if ((w->m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (get_next_line_until(w->m->fd, &w->m->line, w->stopread) && w->stopread == 0)
		{
			if (ft_strncmp(w->m->line, "map\t\t\t", 6) == 0)
				nbmaps++;
			else if (ft_strncmp(w->m->line, "ENDMAPSECTION", 13) == 0)
				w->stopread = 1;
			free(w->m->line);
		}
		free(w->m->line);
		close(w->m->fd);
	}
	else
		set_error(w, w->m, 5, "core/core.dn3d");
	return (nbmaps);
}

int			get_names_maps_in_core(t_env *w, t_map *m, char **names)
{
	char	**tmp;
	
	w->i = 0;
	w->stopread = 0;
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (get_next_line_until(m->fd, &m->line, w->stopread) && w->stopread == 0)
		{
			tmp = ft_strsplit(m->line, ';');
			if (ft_strcmp(tmp[0], "map\t\t\t") == 0)
			{
				names[w->i] = ft_strdup(tmp[1]);
				w->i++;
			}
			else if (ft_strcmp(m->line, "ENDMAPSECTION") == 0)
				w->stopread = 1;
			ft_memreg(tmp);
			free(m->line);
		}
		free(m->line);
		close(m->fd);
	}
	else
		set_error(w, w->m, 5, ft_strdup("core/core.dn3d"));
	return (0);
}
