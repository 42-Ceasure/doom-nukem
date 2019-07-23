
#include "doom.h"

void			interpret_line(t_env *w, t_map *m, int *buffer)
{
	char **tmp;

	if ((tmp = ft_strsplit(m->line, ';')) == NULL)
		ft_putendl("ERREUR SPLIT");
	if (ft_strncmp(m->line, "buffer", 6) == 0)
	{
		*buffer = ft_atoi(tmp[1]);
		ft_memreg(tmp);
		return ;
	}
	else if (ft_strncmp(m->line, "settings", 8) == 0)
		parse_settings_line(w, m, tmp[1]);
	else if (ft_strncmp(m->line, "alloc", 5) == 0)
		parse_allocating_line(w, m, tmp[1]);
	else if (ft_strncmp(m->line, "weapon", 6) == 0)
		parse_weapon_line(m, tmp[1]);
	else if (ft_strncmp(m->line, "texture", 7) == 0)
		parse_texture_line(w, m, tmp[1]);
	else if (ft_strncmp(m->line, "sprite", 6) == 0)
		parse_sprite_line(w, m, tmp[1]);
	if (ft_strncmp(m->line, "texture\t\t;ascii", 15) != 0
		&& ft_strncmp(m->line, "texture\t\t;main_pic", 18) != 0)
		*buffer = 128;
	ft_memreg(tmp);
	w->corenbl++;
}

void			load_core(t_env *w, t_map *m)
{
	int			buffer;
	double		loading;

	buffer = 128;
	w->dtime.start = SDL_GetTicks();
	if ((m->fd = open("core/core.dn3d", O_RDONLY)) != -1)
	{
		while (precise_get_next_line(m->fd, &m->line, buffer))
		{
			interpret_line(w, m, &buffer);
			free(m->line);
		}
		close(m->fd);
		free(m->line);
	}
	else
		set_error(w, m, 5, ft_strdup("core/core.dn3d"));
	if (w->corenbl == 0)
		set_error(w, m, 911, ft_strdup(PAKOMSA));
	w->dtime.end = SDL_GetTicks();
	loading = w->dtime.end - w->dtime.start;
	w->nbmaps = get_nb_maps_in_core(w);
}
