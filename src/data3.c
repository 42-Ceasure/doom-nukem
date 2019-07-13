/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:47:14 by abechet           #+#    #+#             */
/*   Updated: 2019/07/13 18:02:48 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ft_swap2(int *a, int *b)
{
	int		tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_int_tab(int *tab, int size)
{
	int i;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			ft_swap2(&tab[i], &tab[i + 1]);
			//printf("%d tab i + 1 \n", tab[i+1]);
			sort_int_tab(tab, size);
		}
		i++;
	}
}

int		len_listlist(t_lstlst *lstlst)
{
	int		i;
	t_lstlst *tmp2;

	i = 0;
	tmp2 = lstlst;
	while (tmp2)
	{
		i++;
		tmp2 = tmp2->next;
	}
	return (i);
}

int			number_of_dot_case(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;
	int			i;
	int			boole;

	y = 0;
	i = 0;
	while (y <= WIN_Y)
	{
		boole = 0;
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y && boole == 0)
				{
					i++;
					boole = 1;
				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		y++;
	}
	return (i);
}

int			total_number_of_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			len_dots;

	i = 0;
	len_dots = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		i = len_list(tmp);
		len_dots = len_dots + i;
		tmp2 = tmp2->next;
	}
	return (len_dots);
}

int			y_min_point(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;

	y = WIN_Y;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y < y)
				y = tmp->y;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (y);
}

int			number_of_y(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			y;
	int			i;

	i = 0;
	y = 0;
	while (y <= WIN_Y)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y)
				{
					i++;
					y++;
				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
		y++;
	}
	return (i);
}

int			next_y(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	while (y <= WIN_Y)
	{
		y++;
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->y == y)
					return (y);
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
	}
	return (-1);
}

int			x_min_on_line(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x;

	x = WIN_X;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				if (tmp->x < x)
					x = tmp->x;
			}
				tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (x);
}

int			next_x_on_line(t_win *win, int y, int x)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;

	i = WIN_X;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				if (tmp->x > x && tmp->x < i)
					i = tmp->x;
			}
				tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (i);
}

int			number_of_dot_per_line_with_same(t_win *win, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;

	i = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
				i++;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (i);
}

int			*create_y_dot_tab(t_win *win, int y, int i)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			index;

	index = 0;
	if (!(dot_tab = (int *)malloc(sizeof(int) * i)))
		clear_n_exit(win, 1);

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->y == y)
			{
				dot_tab[index] = tmp->x;
				index++;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	sort_int_tab(dot_tab, i);
	return (dot_tab);
}

int			number_of_dot_per_line(t_win *win, int y)
{
	int			*dot_tab;
	int			i;
	int			same;
	int			index;
	int			x;

	x = 0;
	index = 0;
	same = 0;
	i = number_of_dot_per_line_with_same(win, y);
	dot_tab = create_y_dot_tab(win, y, i);
	if (i > 1)
	{
		while (index < i - 1)
		{
			if (dot_tab[index] == dot_tab[index+1])
				same++;
			index++;
		}
	}
	i -= same;
	//free dot tab
	return (i);
}

int			total_exclusive_points(t_win *win)
{
	int		i;
	int		y;

	i = 0;
	y = 0;
	while (y <= WIN_Y)
	{
		i += number_of_dot_per_line(win, y);
		y++;
	}
	return (i);
}

void		sort_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x;
	int			y;
	int			same;
	int			used;
	int			i;
	int			index;
	int			*dot_tab;

	x = WIN_X;
	y = WIN_Y;
	tmp = NULL;
	same = 0;
	used = 0;
	index = 0;

	y = y_min_point(win);
	while (y < WIN_Y)
	{
		i = number_of_dot_per_line_with_same(win, y);
		//printf("%d i \n", i);
		if (i > 0)
		{
			index = 0;
			dot_tab = create_y_dot_tab(win, y, i);
			while (index < i)
			{
				//printf("%d dot tab \n", dot_tab[index]);
				tmp2 = win->lstlst;
				while (tmp2)
				{
					tmp = tmp2->head;
					while (tmp)
					{
						if (tmp->y == y && tmp->x == dot_tab[index])
						{
							tmp->nb = win->number;
							//printf("%d nb \n", win->number);
						}
						tmp = tmp->next;
					}
					tmp2 = tmp2->next;
				}
				index++;
				if (dot_tab[index] !=  dot_tab[index-1])
					win->number++;
			}
		}
		y++;
	}
}

int			*dot_tab_sector(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			i;
	int			index;

	dot_tab = NULL;
	i = 0;
	index = 0;
	tmp2 = win->lstlst;
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
		sort_int_tab(dot_tab, i);
	}
	return (dot_tab);
}

int			number_of_points_in_sector(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			j;
	int			index;
	int			nb;
	int			*dot_tab;

	index = 0;
	i = 0;
	j = 0;


	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			i = len_list(tmp);
			dot_tab = dot_tab_sector(win, sector);
			nb = dot_tab[index];
			j++;
			while (index < i)
			{
				if (dot_tab[index] > nb)
				{
					j++;
					nb = dot_tab[index];
				}
				index++;
			}
			break;
		}
		tmp2 = tmp2->next;
	}
	return (j);
}

void		check(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			//printf("%d nb \n", tmp->nb);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
}

int			number_of_ennemy(t_win *win)
{
	t_lstasset		*tmp;
	int				i;

	i = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

int			number_of_sprite(t_win *win)
{
	t_lstasset		*tmp;
	int				i;

	i = 0;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
			i++;
		tmp = tmp->next;
	}
	return (i);
}


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

int		check_triangles_segment(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			headx;
	int			heady;

	tmp2 = win->triangles;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp)
		{
			headx = tmp->x;
			heady = tmp->y;
		}
		while (tmp)
		{
			if (tmp->next)
			{
				//printf("%d tmp nb \n", tmp->nb);
				//printf("%d tmp next nb \n", tmp->next->nb);
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (1);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (1);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (0);
}

void		sort_triangles_points(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x;
	int			y;
	int			same;
	int			used;
	int			i;
	int			index;
	int			*dot_tab;

	x = WIN_X;
	y = WIN_Y;
	tmp = NULL;
	same = 0;
	used = 0;
	index = 0;

	y = y_min_point(win);
	while (y < WIN_Y)
	{
		i = number_of_dot_per_line_with_same(win, y);
		//printf("%d i \n", i);
		if (i > 0)
		{
			index = 0;
			dot_tab = create_y_dot_tab(win, y, i);
			while (index < i)
			{
				//printf("%d dot tab \n", dot_tab[index]);
				tmp2 = win->triangles;
				while (tmp2)
				{
					tmp = tmp2->head;
					while (tmp)
					{
						if (tmp->y == y && tmp->x == dot_tab[index])
						{
							tmp->nb = win->number;
							//printf("%d nb \n", win->number);
						}
						tmp = tmp->next;
					}
					tmp2 = tmp2->next;
				}
				index++;
				if (dot_tab[index] !=  dot_tab[index-1])
					win->number++;
			}
		}
		y++;
	}
}

int			triangles_neighbours(t_win *win, t_lstlst *tmp2, int i)
{
	t_lstlst	*tmp3;
	int			*tab_sector1;
	int			*tab_sector2;
	int			index;
	int			swap;


	tab_sector1 = tab_sector3(win, tmp2->sector);
	if (tmp2->clockwise == 2)
	{
		swap = tab_sector1[1];
		tab_sector1[1] = tab_sector1[2];
		tab_sector1[2] = swap;
	}
	tmp3 = win->triangles;
	while (tmp3)
	{
		index = 0;
		if (tmp3->sector != -1 && tmp3->sector != tmp2->sector)
		{
			tab_sector2 = tab_sector3(win, tmp3->sector);
			if (tmp3->clockwise == 2)
			{
				swap = tab_sector2[1];
				tab_sector2[1] = tab_sector2[2];
				tab_sector2[2] = swap;
			}
			if (i == 0)
			{
				if (tab_sector1[0] == tab_sector2[0] || tab_sector1[0] == tab_sector2[1]
					|| tab_sector1[0] == tab_sector2[2])
						index++;
				if (tab_sector1[1] == tab_sector2[0] || tab_sector1[1] == tab_sector2[1]
					|| tab_sector1[1] == tab_sector2[2])
						index++;
			}
			if (i == 1)
			{
				if (tab_sector1[1] == tab_sector2[0] || tab_sector1[1] == tab_sector2[1]
					|| tab_sector1[1] == tab_sector2[2])
					index++;
				if (tab_sector1[2] == tab_sector2[0] || tab_sector1[2] == tab_sector2[1]
					|| tab_sector1[2] == tab_sector2[2])
					index++;
			}

			if (i == 2)
			{
				if (tab_sector1[2] == tab_sector2[0] || tab_sector1[2] == tab_sector2[1]
					|| tab_sector1[2] == tab_sector2[2])
					index++;
				if (tab_sector1[0] == tab_sector2[0] || tab_sector1[0] == tab_sector2[1]
					|| tab_sector1[0] == tab_sector2[2])
					index++;
			}
			if (index == 2)
				return (tmp3->sector);
		}
		tmp3 = tmp3->next;
	}
	return (-1);
}

void		write_sectors_neighbours(t_win *win, int fp, t_lstlst *tmp2)
{
	char		*str;
	t_lst		*tmp;
	int			*tab_sector;
	int			ret;
	int			i;
	int			len;

	i = 0;
	tab_sector = tab_sector3(win, tmp2->sector);
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
	char		*str;
	t_lst		*tmp;

	if	(win->lstlst)
		tmp = tmp2->head;

	str = ":";
	ft_putstr_fd(str, fp);

	str = "0,1,0,0,0,0";
	ft_putstr_fd(str, fp);
}

void		write_sectors(t_win *win, int fp)
{
	char		*str;
	int			i;
	int			index;
	t_lstlst	*tmp2;
	t_lst		*tmp;
	//int			ret;


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

void		write_player(t_win *win, int fp)
{
	char		*str;

	t_lstasset	*tmp;

	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			break;
		tmp = tmp->next;
	}

	str = "Section:player\n";
	ft_putstr_fd(str, fp);

	str = "\tplayer_location:";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);

	str = "\n";
	ft_putstr_fd(str, fp);

	str = "\tplayer_direction:90\n";
	ft_putstr_fd(str, fp);

	str = "\tplayer_sector:";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = "\n";
	ft_putstr_fd(str, fp);

	str = "\tplayer_max_hp:100\n";
	ft_putstr_fd(str, fp);

	str = "\tgravity:0.05\n";
	ft_putstr_fd(str, fp);

	str = "\tgod_mod:0\n";
	ft_putstr_fd(str, fp);
	
	// str = "\n";
	// ft_putstr_fd(str, fp);
}

/*int			*check3(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			*dot_tab;
	int			i;
	int			index;

	dot_tab = NULL;
	i = 0;
	index = 0;
	tmp2 = win->lstlst;
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

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			printf("%d tmp nb \n", tmp->nb);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}

	tmp2 = win->lstlst;
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

		index = 0;
		while (index < i)
		{
			printf("%d pre_sort_dot_tab \n", dot_tab[index]);
			index++;
		}
		sort_int_tab(dot_tab, i);
	}

	index = 0;
	while (index < i)
	{
		printf("%d dot_tab \n", dot_tab[index]);
		index++;
	}
	return (dot_tab);
}*/

void		check4(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->triangles;
	while (tmp2)
	{
		tmp = tmp2->head;

		if (tmp->nb != tmp->next->nb && tmp->next->nb != tmp->next->next->nb
			&& tmp->next->next->nb != tmp->nb)
		{
			tmp2->sector = win->triangle_sector;
			win->triangle_sector += 1;
			//printf("%d sector \n", tmp2->sector);
		}
		else
			tmp2->sector = -1;
		while (tmp)
		{
			tmp->sector = tmp2->sector;
			//printf("%d sector \n", tmp2->sector);
			//printf("%d nb \n", tmp->nb);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
}

void		write_m4(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{

		str = "\tM4A1:";
		ft_putstr_fd(str, fp);

	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",0,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_shotgun(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tpompe:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",1,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_shotgun_ammo(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tcartouche:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",4,0,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_m4_ammo(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tammo:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",5,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_m9(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tM9:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",2,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_health(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\thealth:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",3,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_undertale(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{
		str = "\tundertale:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",14,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_ennemy(t_win *win, int fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{
		str = "\tmonstre:";
		ft_putstr_fd(str, fp);
	}

	str = ft_itoa(i);
	ft_putstr_fd(str, fp);

	str = ",6,";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->sector);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->x / 5);
	ft_putstr_fd(str, fp);

	str = ",";
	ft_putstr_fd(str, fp);

	str = ft_itoa(tmp->y / 5);
	ft_putstr_fd(str, fp);
}

void		write_sprites(t_win *win, int fp)
{
	t_lstasset	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstasset;
	str = "Section:sprite\n";
	ft_putstr_fd(str, fp);

	while (tmp)
	{
		//printf("%d tmp sector \n", tmp->sector);
		if (tmp->asset_type == 1)
			write_m4(win, fp, tmp, i);
		if (tmp->asset_type == 2)
			write_shotgun(win, fp, tmp, i);
		if (tmp->asset_type == 4)
			write_m4_ammo(win, fp, tmp, i);
		if (tmp->asset_type == 5)
			write_m9(win, fp, tmp, i);
		if (tmp->asset_type == 6)
			write_health(win, fp, tmp, i);
		if (tmp->asset_type == 7)
			write_shotgun_ammo(win, fp, tmp, i);
		if (tmp->asset_type == 8)
			write_undertale(win, fp, tmp, i);
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
		{
			i++;
			str = "\n";
			ft_putstr_fd(str, fp);
		}
		tmp = tmp->next;
	}
}

void		write_ennemies(t_win *win, int fp)
{
	t_lstasset	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstasset;

	str = "Section:ennemy\n";
	ft_putstr_fd(str, fp);

	while (tmp)
	{
		if (tmp->asset_type == 3)
		{
			write_ennemy(win, fp, tmp, i);
			str = "\n";
			ft_putstr_fd(str, fp);
			i++;
		}
		tmp = tmp->next;
	}
}

void		write_in_file(t_win *win)
{
	int			fp;
	const char	*name;
	char		*buf;
	int			index;
	char		*str;

	index = 0;
	name = "custom_map.dn3d";
	fp = open(name, O_RDWR | O_CREAT | O_TRUNC, 0655);
	buf = NULL;

	first_line2(win, fp);
	write_dots(win, fp);
	write_sectors(win, fp);
	write_player(win, fp);
	write_sprites(win, fp);
	write_ennemies(win, fp);

	str = "Section:over\n";
	ft_putstr_fd(str, fp);

	close(fp);
}

void		fill_buffer(t_win *win)
{
	win->number = 0;
	sort_points(win);
	write_in_file(win);
}

int			triangulate_a_triangle(t_win *win, t_dot m)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			ret;

	t_dot		p0;
	t_dot		p1;
	t_dot		p2;

	ret = -1;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (len_list(tmp2->head) == 4)
		{
			tmp = tmp2->head;
			p0 = get_point_in_list(tmp, 0);
			p1 = get_point_in_list(tmp, 1);
			p2 = get_point_in_list(tmp, 2);

			ret = point_in_triangle(p0, p1, p2, m);
			if (ret == 1)
				return (tmp2->sector);
		}
		tmp2 = tmp2->next;
	}
	return (ret);
}

int			triangulate_player_start(t_win *win, int x, int y)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	int			ret;

	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	t_dot		m;

	m.x = x;
	m.y = y;

	ret = -2;

	tmp2 = win->triangles;
	ret = triangulate_a_triangle(win, m);
	if (ret != -1)
		return (0);
	while (tmp2)
	{
		tmp = tmp2->head;
		p0 = get_point_in_list(tmp, 0);
		p1 = get_point_in_list(tmp, 1);
		p2 = get_point_in_list(tmp, 2);

		ret = point_in_triangle(p0, p1, p2, m);
		if (ret == 1)
		{
			ret = 0;
			return (ret);
		}
		else
			ret = -2;
		tmp2 = tmp2->next;
	}
	return (ret);
}

int			check_player_start(t_win *win)
{
	t_lstasset	*tmp;
	int			ret;

	ret = -1;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
		{
			ret = 0;
			break;
		}
		tmp = tmp->next;
	}
	if (ret == 0)
		ret = triangulate_player_start(win, tmp->x, tmp->y);
	return (ret);
}

int		sector_intersect_with_itself(t_dot p1, t_dot p2, t_dot p3, t_dot p4)
{
	int	i1;
	int	i2;
	int	i3;
	int	i4;

	i1 = pointside2(p3, p1.x, p1.y, p2.x, p2.y);
	i2 = pointside2(p4, p1.x, p1.y, p2.x, p2.y);
	i3 = pointside2(p1, p3.x, p3.y, p4.x, p4.y);
	i4 = pointside2(p2, p3.x, p3.y, p4.x, p4.y);

	if (i1 >= 0 && i2 <= 0 && i3 >= 0 && i4 <= 0)
		return (1);
	else if (i1 <= 0 && i2 >= 0 && i3 <= 0 && i4 >= 0)
		return (1);
	else if (i1 <= 0 && i2 >= 0 && i3 >= 0 && i4 <= 0)
		return (1);
	else if (i1 >= 0 && i2 <= 0 && i3 <= 0 && i4 >= 0)
		return (1);
	return (0);
}

int			correct_intersections_in_a_sector(t_win *win)
{
	t_lstlst	*tmp3;
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_lst		*tmp0;
	t_dot		p1;
	t_dot		p2;
	t_dot		p3;
	t_dot		p4;
	int			ret;
	int			index3;
	int			index2;
	int			len;
	int			index4;
	int			index5;

	index3 = 0;
	ret = -1;
	tmp3 = win->lstlst;

	while (tmp3)
	{
		tmp = tmp3->head;
		while (tmp)
		{
			if (tmp->next == NULL)
			{
				p2.x = tmp3->head->next->x;
				p2.y = tmp3->head->next->y;
			}
			else
			{
				p2.x = tmp->next->x;
				p2.y = tmp->next->y;
			}

			p1.x = tmp->x;
			p1.y = tmp->y;

			tmp2 = win->lstlst;
			index2 = 0;
			while (tmp2)
			{
				tmp0 = tmp2->head;
				len = len_list(tmp0);
				index4 = index3 + len - 2;
				index5 = index2 + len - 2;
				while (tmp0)
				{
					if (index2 != index3 && index3 + 1 != index2 && index4 != index2
						&& index4 + 1 != index2)
					{
						if (index3 != index2 && index2 + 1 != index3 && index5 != index3
							&& index5 + 1 != index3)
						{
							if (tmp0->next == NULL)
							{
								p4.x = tmp2->head->next->x;
								p4.y = tmp2->head->next->y;
							}
							else
							{
								p4.x = tmp0->next->x;
								p4.y = tmp0->next->y;
							}
							p3.x = tmp0->x;
							p3.y = tmp0->y;

							if ((ret = sector_intersect_with_itself(p1, p2, p3, p4)) == 1)
							{
								if (p1.x != p2.x && p2.x != p3.x && p3.x != p4.x && p4.x != p1.x
									&& p1.x != p3.x && p2.x != p4.x && p1.y != p2.y && p2.y != p3.y && p3.y != p4.y
										&& p4.y != p1.y && p3.y != p1.y && p2.y != p4.y)
								{
									return (-3);
								}
							}
						}
					}
					index2++;
					tmp0 = tmp0->next;
				}
				tmp2 = tmp2->next;
			}
			index3++;
			tmp = tmp->next;
		}
		tmp3 = tmp3->next;
	}
	return (0);
}

int			sector_minimum_needed_point(t_win *win)
{
	t_lstlst	*tmp2;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (len_list(tmp2->head) <= 3)
			return (-4);
		tmp2 = tmp2->next;
	}
	return (0);
}

int			correct_map(t_win *win)
{
	int			ret;

	ret = 0;

	ret = correct_intersections_in_a_sector(win);

	if (ret == -3)
	{
		printf("Crossed segments \n");
		return (ret);
	}

	//check croisements

	//check overlapping sectors and sectors in sectors

	ret = check_player_start(win);
	if (ret == -1)
		printf("Map need a player start \n");
	if (ret == -2)
		printf("Player start need to be inside a sector \n");

	return (ret);
}

void		new_clockwise(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_dot		p0;
	t_dot		p1;
	t_dot		m;
	double		ret;

	tmp2 = win->triangles;
	ret = 0;
	while (tmp2)
	{

		tmp = tmp2->head;

		p0.x = tmp->x;
		p0.y = tmp->y;

		p1.x = tmp->next->x;
		p1.y = tmp->next->y;

		m.x = tmp->next->next->x;
		m.y = tmp->next->next->y;

		ret = pointside2(m, p0.x, p0.y, p1.x, p1.y);

		if (ret >= 0)
			tmp2->clockwise = 1;

		if (ret < 0)
			tmp2->clockwise = 2;

		tmp2 = tmp2->next;
	}
}

void		triangulate_all_assets(t_win *win)
{
	t_lstasset	*tmp3;
	t_lstlst	*tmp2;
	t_lst		*tmp;

	int			ret;

	t_dot		p0;
	t_dot		p1;
	t_dot		p2;
	t_dot		m;

	ret = -1;
	tmp3 = win->lstasset;
	while (tmp3)
	{
		tmp2 = win->triangles;
		if (tmp2->sector != -1)
		{
			while (tmp2)
			{
				tmp = tmp2->head;
				p0 = get_point_in_list(tmp, 0);
				p1 = get_point_in_list(tmp, 1);
				p2 = get_point_in_list(tmp, 2);
				m.x = tmp3->x;
				m.y = tmp3->y;
				ret = triangulate_a_triangle(win, m);
				if (ret != -1)
					tmp3->sector = ret;
				ret = point_in_triangle(p0, p1, p2, m);
				if (ret == 1)
					tmp3->sector = tmp2->sector;
				//printf("%d tmp3 sector \n", tmp3->sector);
				tmp2 = tmp2->next;
			}
		}
		tmp3 = tmp3->next;
	}
}

void		everything_is_a_triangle(t_win *win)
{
	recursive_check(win);
	sort_triangles_points(win);
	check4(win);
	new_clockwise(win);
	triangulate_all_assets(win);
}

void		map_save(t_win *win)
{
	int			len;
	int			z;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	z = -1;
	tmp = NULL;
	tmp2 = win->lstlst;

	if (sector_minimum_needed_point(win) != 0)
	{
		printf("Un secteur est au minimum un triangle \n");
		return ;
	}

	while (tmp2)
	{
		if (tmp2)
			tmp = tmp2->head;
		if (tmp2)
		{
			if (tmp2->closed)
				z = tmp2->sector;
		}
		tmp2 = tmp2->next;
	}
	len = len_listlist(win->lstlst);
	if (len - 1 == z)
	{
		everything_is_a_triangle(win);
		if (correct_map(win) == 0)
		{
			fill_buffer(win);
			printf("Map saved\n");
		}
	}
	win->number = 0;
	win->same_dots = 0;
	win->index_dot = 0;
	win->tab_index = 0;
	win->triangle_sector = 0;

	//win->sector = 0;
}
