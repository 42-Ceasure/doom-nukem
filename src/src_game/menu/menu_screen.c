/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 22:21:24 by nvienot           #+#    #+#             */
/*   Updated: 2019/07/23 22:22:00 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	aff_menu_screen_2(t_env *w, char *start, t_dot dot)
{
	if (w->menu.j == 4)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EDITOR\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j > 4)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> EXIT", 0xFF78F7);
	}
}

void	aff_menu_screen_1(t_env *w, char *start, t_dot dot)
{
	if (w->menu.j <= 1)
	{
		type_str(w, dot, start, 0xFF78F7);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 2)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> MAPS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nSETTINGS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
	else if (w->menu.j == 3)
	{
		type_str(w, dot, start, 0x12FEA800);
		type_str(w, w->txtnxtline, "\nMAPS\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\n> SETTINGS\n", 0xFF78F7);
		type_str(w, w->txtnxtline, "\nEDITOR\n", 0x12FEA800);
		type_str(w, w->txtnxtline, "\nEXIT", 0x12FEA800);
	}
}

void	menu_screen(t_env *w)
{
	char	*start;
	t_dot	dot;

	dot = fill_t_dot(WIDTH / 2 - 50, 140);
	if (w->m->newgame == 1)
	{
		if (w->menu.j == 1)
			start = ft_strdup("> NEW GAME\n");
		else
			start = ft_strdup("NEW GAME\n");
	}
	else
	{
		if (w->menu.j == 1)
			start = ft_strdup("> CONTINUE\n");
		else
			start = ft_strdup("CONTINUE\n");
	}
	main_pic(w, 1);
	if (w->menu.j < 4)
		aff_menu_screen_1(w, start, dot);
	else
		aff_menu_screen_2(w, start, dot);
	free(start);
}
