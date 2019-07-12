/*BIG42HEADER*/

#include "doom.h"

int		get_that_map_parsed(t_env *w, t_map *m)
{
	free(m->line);
	m->i = 0;
	m->s = 0;
	m->w = 0;
	m->section_number = 0;
	process_hint_w(w, 6, "map");
	m->weap[0].actu_ammo = m->weap[0].magazine;
	m->weap[1].actu_ammo = m->weap[1].magazine;
	m->weap[2].actu_ammo = m->weap[2].magazine;
	while (w->stopread == 0 && get_next_line(m->fd, &m->line))
	{
		if ((parse_line(w, m)) == -1)
		{
			write(2, "error on map collect\n", 22);
			return (-1);
		}
		free(m->line);
	}
	process_hint_w(w, 0, " ");
	// free(m->line);
	return (0);
}

int			parse_map_in_core(t_env *w, t_map *m, char *name)
{
	char	*tmp;
	char	*pre;
	int		i;

	i = 0;
	pre = ft_strdup("map\t\t\t;");
	tmp = ft_strjoin(pre, name);
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (w->stopread == 0 && get_next_line(m->fd, &m->line))
		{
			if (ft_strcmp(m->line, tmp) == 0)
				get_that_map_parsed(w, m);
			else if (ft_strcmp(m->line, "ENDMAPSECTION") == 0)
			{	
				w->menu.i = 1;
				free(m->line);
				return (-1);
			}
			else
				free(m->line);
		}
		close(m->fd);
	}
	else
		set_error(w, m, 5, "core/core.dn3d");
	m->tab = (double**)malloc(sizeof(double*) * (m->sprite_map_count
		+ m->ennemy_count));
	i = 0;
	while (i < m->sprite_map_count + m->ennemy_count)
	{
		m->tab[i] = (double*)malloc(sizeof(double) * 3);
		i++;
	}
	return (0);
}
