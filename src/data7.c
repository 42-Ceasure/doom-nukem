/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data7.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 13:50:58 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 13:51:10 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		write_sectors_neighbours(t_win *win, int fp, t_lstlst *tmp2)
{
	char		*str;
	t_lst		*tmp;
	// int			*tab_sector;
	int			ret;
	int			i;
	int			len;

	i = 0;
	// tab_sector = tab_sector3(win, tmp2->sector);
	ret = -1;
	tmp = tmp2->head;
	len = len_list(tmp);

	while (i < len)
	{
		ret = triangles_neighbours(win, tmp2, i);
		if (ret == -1)
		{
			str = "x";
			ft_putstr_fd(str, fp);
		}
		else
		{
			str = ft_itoa(ret);
			ft_putstr_fd(str, fp);
		}
		if (i < len - 1)
		{
			str = ",";
			ft_putstr_fd(str, fp);
		}
		i++;
	}
}

void		write_sectors_textures(t_win *win, int fp, t_lstlst *tmp2)
{
	(void)win;
	char		*str;

	str = ":";
	ft_putstr_fd(str, fp);


	str = ft_itoa(tmp2->txtr_floor);
	ft_putstr_fd(str, fp);

	printf("%s str \n", str);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp2->txtr_ceiling);
	ft_putstr_fd(str, fp);

	printf("%s str \n", str);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp2->txtr_wall);
	ft_putstr_fd(str, fp);

	printf("%s str \n", str);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp2->txtr_lower_extrude);
	ft_putstr_fd(str, fp);

	printf("%s str \n", str);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp2->txtr_higher_extrude);
	ft_putstr_fd(str, fp);

	printf("%s str \n", str);

	str = ",0";
	ft_putstr_fd(str, fp);


	/*
		-floor
		-ceiling
		-wall
		-lower extrude
		-higher extrude
		-skybox toujours a 0
	*/
}

void		write_sectors(t_win *win, int fp)
{
	char		*str;
	int			i;
	int			index;
	t_lstlst	*tmp2;
	t_lst		*tmp;

	index = 0;
	i = len_listlist(win->triangles);
	tmp2 = win->triangles;

	while (index < i)
	{
		if (tmp2->sector != -1)
		{
			str = "\tsector:0,30:";
			ft_putstr_fd(str, fp);
			tmp = tmp2->head;
			if (tmp2->clockwise == 1)
			{
				while (tmp)
				{
					str = ft_itoa(tmp->nb);
					ft_putstr_fd(str, fp);
					tmp = tmp->next;
					if (tmp)
					{
						str = ",";
						ft_putstr_fd(str, fp);
					}
				}
			}
			if (tmp2->clockwise == 2)
			{
				str = ft_itoa(tmp->nb);
				ft_putstr_fd(str, fp);

				str = ",";
				ft_putstr_fd(str, fp);

				str = ft_itoa(tmp->next->next->nb);
				ft_putstr_fd(str, fp);

				str = ",";
				ft_putstr_fd(str, fp);

				str = ft_itoa(tmp->next->nb);
				ft_putstr_fd(str, fp);
			}
			str = ":";
			ft_putstr_fd(str, fp);

			write_sectors_neighbours(win, fp, tmp2);
			write_sectors_textures(win, fp, tmp2);

			str = "\n";
			ft_putstr_fd(str, fp);
		}
		index++;

		tmp2 = tmp2->next;
	}
}
