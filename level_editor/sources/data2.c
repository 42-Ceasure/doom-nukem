/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 12:58:10 by abechet           #+#    #+#             */
/*   Updated: 2019/06/27 12:58:21 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void		sectors_in_tab(t_win *win)
{
	int		len_sectors;
	int		index;

	len_sectors = len_listlist(win->lstlst);
	index = win->index_dot;
	len_sectors += index;
	while (index < len_sectors)
	{
		printf("sector \n");
		index++;
	}
}
