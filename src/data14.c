/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data14.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/17 14:00:45 by abechet           #+#    #+#             */
/*   Updated: 2019/07/17 14:00:55 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		first_line2(t_win *win, int fp)
{
	char		*str;
	t_lstlst	*tmp2;
	int			i;

	i = 0;

	tmp2 = win->triangles;
	while (tmp2)
	{
		if (tmp2->sector != -1)
			i++;
		tmp2 = tmp2->next;
	}

	// str = "map\t\t\t;name\n";
	// ft_putstr_fd(str, fp);

	str = "dots:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(total_exclusive_points(win));
	ft_putstr_fd(str, fp);
	str = ",sector:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(i);
	ft_putstr_fd(str, fp);
	str = ",sprite:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(number_of_sprite(win));;
	ft_putstr_fd(str, fp);
	str = ",ennemy:";
	ft_putstr_fd(str, fp);
	str = ft_itoa(number_of_ennemy(win));
	ft_putstr_fd(str, fp);
	str = "\n";
	ft_putstr_fd(str, fp);
	str = "Section:map\n";
	ft_putstr_fd(str, fp);
}

void		write_dots(t_win *win, int fp)
{
	char		*str;
	int			i;
	int			x;
	int			y;
	int			index;

	int			boole;

	int			a;
	int			b;

	b = number_of_y(win);

	//printf("%d number of y \n", b);

	a = 0;
	boole = 0;
	y  = y_min_point(win);

	//printf("%d y min \n", y);

	while (a < b)
	{

		index = 1;
		if (boole == 0)
			boole = 1;
		else
		{
			y = next_y(win, y);
			//printf("%d next y \n", y);
		}
		i = number_of_dot_per_line(win, y);
		//printf("%d number of dots per lin \n", i);
		str = "\tdots:";
		ft_putstr_fd(str, fp);

		str = ft_itoa(y / 5);
		ft_putstr_fd(str, fp);

		str = ":";
		ft_putstr_fd(str, fp);

		x = x_min_on_line(win, y);
		//printf("%d x min \n", x);
		str = ft_itoa(x / 5);
		ft_putstr_fd(str, fp);

		while (index < i)
		{
			str = ",";
			ft_putstr_fd(str, fp);

			x = next_x_on_line(win, y, x);
			//printf("%d next x \n", x);
			str = ft_itoa(x / 5);
			ft_putstr_fd(str, fp);
			index++;
		}
		str = "\n";
		ft_putstr_fd(str, fp);
		a++;
	}
}

int			*tab_sector3(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			i;
	int			index;

	dot_tab = NULL;
	i = 0;
	index = 0;
	//tmp2 = win->lstlst;
	tmp2 = win->triangles;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			i = len_list(tmp);
			break;
		}
		tmp2 = tmp2->next;
	}
	if (tmp2)
	{
		if (!(dot_tab = (int *)malloc(sizeof(int) * i)))
			clear_n_exit(win, 1);
		tmp = tmp2->head;
		while (tmp)
		{
			dot_tab[index] = tmp->nb;
			index++;
			tmp = tmp->next;
		}
	}
	return (dot_tab);
}
