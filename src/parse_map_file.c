/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 13:27:27 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/15 18:20:59 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	m->sprite_map_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	tmp = ft_strsplit(tab[4], ',');
	m->ennemy_count = ft_atoi(tmp[0]);
	ft_memreg(tmp);
	if ((m->sector = (t_sector *)malloc(sizeof(t_sector) * M_S_C)) == NULL)
		return (-1);
	if ((m->dot = (t_dot *)malloc(sizeof(t_dot) * m->dots_count)) == NULL)
		return (-1);
	if ((m->sprt = (t_map_sprite *)malloc(sizeof(t_map_sprite)
		* m->sprite_map_count)) == NULL)
		return (-1);
	if ((m->ennemy = (t_ennemy *)malloc(sizeof(t_ennemy) * m->ennemy_count))
		== NULL)
		return (-1);
	return (0);
}

int		second_parse(t_map *m, char **tmp)
{
	if (m->section_number == 2)
	{
		if (parse_player_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_player_section");
			return (-1);
		}
	}
	else if (m->section_number == 3)
	{
		if (parse_sprite_map(m, tmp) == -1)
		{
			ft_putendl("error in parse_sprite_map");
			return (-1);
		}
	}
	else if (m->section_number == 4)
	{
		if (parse_ennemy_map(m, tmp) == -1)
		{
			ft_putendl("error in parse_ennemy_map");
			return (-1);
		}
	}
	else if (m->section_number == 5)
	{
		if (parse_level_map(m, tmp) == -1)
		{
			ft_putendl("error in parse_level_map");
			return (-1);
		}
	}
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
	else if (m->section_number == 1)
	{
		process_hint_w(w, 4, "map");
		if (parse_map_section(m, tmp) == -1)
		{
			ft_putendl("error in parse_map_section");
			return (-1);
		}
	}
	if (second_parse(m, tmp) == -1)
		return (-1);
	if (m->section_number == 6)
		w->stopread = 1;
	ft_memreg(tmp);
	return (0);
}

int		do_parse(t_env *w, t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->w = 0;
	m->section_number = 0;
	if ((m->fd = open(m->map_path, O_RDONLY)) == -1)
		return (-1);
	process_hint_w(w, 6, " ");
	reset_player(m);
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
	if (w->stopread == 0)
		free(m->line);
	close(m->fd);
	return (0);
}

void	parse_map_file(t_env *w, t_map *m)
{
	// a enlever?
	double	loading;

	ft_free_sector(m);
	if (m->dot != NULL)
		free(m->dot);
	ft_free_sprt(m);
	w->dtime.start = SDL_GetTicks();
	if (do_parse(w, m) == -1)
		set_error(w, m, 8, ft_strdup("do_parse"));
	w->dtime.end = SDL_GetTicks();
	loading = w->dtime.end - w->dtime.start;
	printf("map loaded in %f seconds !\n", loading / 1000);
}
