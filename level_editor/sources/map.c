/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 10:12:12 by abechet           #+#    #+#             */
/*   Updated: 2019/06/05 10:12:35 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void		malloc_map_case(t_win *win, int nblines, char **map)
{
	int i;

	i = 0;
	while (i < nblines)
	{
		if (!(map[i] = (char*)malloc(sizeof(char) * (nblines))))
			clear_n_exit(win, 2);
		i++;
	}
	win->map_width = nblines;
	win->map_height = nblines;
	map[i] = NULL;
}

char			**map(t_win *win)
{
	char	**map;
	int		nblines;

	map = NULL;
	nblines = 200;
	if (!(map = (char **)malloc(sizeof(char *) * (nblines))))
		clear_n_exit(win, 2);
	malloc_map_case(win, nblines, map);
	return (map);
}
