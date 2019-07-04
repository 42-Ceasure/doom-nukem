/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 14:47:14 by abechet           #+#    #+#             */
/*   Updated: 2019/07/01 14:47:31 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	ft_swap(int *a, int *b)
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
			ft_swap(&tab[i], &tab[i + 1]);
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

/*void		sort_sectors(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	t_lstlst	**tab;
	int			i;
	int			index;
	int			nb;
	int			same;
	int			next_i;
	int			still_same;

	nb = 0;
	i = 0;
	index = 0;
	same = -1;
	still_same = -1;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->nb == i)
			{
				tmp2->sector_nb = nb;
				same++;
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}

	if (same > 0)
	{
		if (!(tab = (t_lstlst **)malloc(sizeof(t_lstlst *) * same + 1)))
			clear_n_exit(win, 1);

		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->nb == i)
				{
					tab[index] = tmp2;
					index++;
				}
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}

		next_i = i + 1;

		while (still_same == -1)
		{
			index = 0;
			while (index < same)
			{
				tmp = tab[index]->head;
				while (tmp)
				{
					if (tmp->nb == next_i)
					{
						tab[index]->sector_nb = i;
						still_same++;
					}
					tmp = tmp->next;
				}
				index++;
			}
			if (still_same == -1)
				next_i++;
			if (still_same == 0)
			{
				//attribuer les i suivants aux autres index
			}
			if (still_same > 0)
			{
				next_i++;
		}

}*/

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


void		first_line(t_win *win, FILE *fp)
{
	char		*str;

	str = "dots:";
	fputs(str, fp);
	str = ft_itoa(total_exclusive_points(win));
	fputs(str, fp);
	str = ",sector:";
	fputs(str, fp);
	str = ft_itoa(len_listlist(win->lstlst));
	fputs(str, fp);
	str = ",sprite:";
	fputs(str, fp);
	str = ft_itoa(number_of_sprite(win));;
	fputs(str, fp);
	str = ",ennemy:";
	fputs(str, fp);
	str = ft_itoa(number_of_ennemy(win));
	fputs(str, fp);
	str = "\n";
	fputs(str, fp);
	str = "Section:map\n";
	fputs(str, fp);
}

void		write_dots(t_win *win, FILE *fp)
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
		fputs(str, fp);

		str = ft_itoa(y / 5);
		fputs(str, fp);

		str = ":";
		fputs(str, fp);

		x = x_min_on_line(win, y);
		//printf("%d x min \n", x);
		str = ft_itoa(x / 5);
		fputs(str, fp);

		while (index < i)
		{
			str = ",";
			fputs(str, fp);

			x = next_x_on_line(win, y, x);
			//printf("%d next x \n", x);
			str = ft_itoa(x / 5);
			fputs(str, fp);
			index++;
		}
		str = "\n";
		fputs(str, fp);
		a++;
	}
}

int			*tab_sector2(t_win *win, int sector)
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
	}
	return (dot_tab);
}

void		write_sectors_neighbours(t_win *win, FILE *fp, t_lstlst *tmp2)
{
	char		*str;
	t_lst		*tmp;
	t_lst		*tmp0;
	int			*tab_sector;
	int			ret;
	int			i;
	int			len;

	i = 0;
	tab_sector = tab_sector2(win, tmp2->sector);
	ret = -1;
	tmp = tmp2->head;
	len = len_list(tmp);

	while (i < len - 1)
	{
		tmp = tmp2->head;
		tmp0 = tmp2->head;
		while (tmp->nb != tab_sector[i])
			tmp = tmp->next;
		while (tmp0->nb != tab_sector[i + 1])
			tmp0 = tmp0->next;
		ret = which_sector_neighbour(win, tmp->x, tmp->y, tmp0->x, tmp0->y, tmp2->sector);
		if (ret == -1)
		{
			str = "x";
			fputs(str, fp);
		}
		else
		{
			str = ft_itoa(ret);
			fputs(str, fp);
		}
		if (i < len - 2)
		{
			str = ",";
			fputs(str, fp);
		}
		i++;
	}
}

void		write_sectors_textures(t_win *win, FILE *fp, t_lstlst *tmp2)
{
	char		*str;
	t_lst		*tmp;

	if (win->lstlst)
		tmp = tmp2->head;

	str = ":";
	fputs(str, fp);

	str = "3,5,3,2,2,0";
	fputs(str, fp);
}


void		write_sectors(t_win *win, FILE *fp)
{
	char		*str;
	int			i;
	int			index;
	t_lstlst	*tmp2;
	t_lst		*tmp;


	index = 0;
	i = len_listlist(win->lstlst);
	tmp2 = win->lstlst;
	while (index < i)
	{
		str = "\tsector:0,50:";
		fputs(str, fp);

		tmp = tmp2->head;
		while (tmp->next)
		{
			str = ft_itoa(tmp->nb);
			fputs(str, fp);
			tmp = tmp->next;
			if (tmp->next)
			{
				str = ",";
				fputs(str, fp);
			}
		}
		str = ":";
		fputs(str, fp);

		write_sectors_neighbours(win, fp, tmp2);
		write_sectors_textures(win, fp, tmp2);

		str = "\n";
		fputs(str, fp);
		tmp2 = tmp2->next;
		index++;
	}
}

void		write_player(t_win *win, FILE *fp)
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
	fputs(str, fp);


	str = "\tplayer_location:";
	fputs(str, fp);

	str = ft_itoa(tmp->x / 5); //a verifier
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5); // a verifier
	fputs(str, fp);

	str = "\n";
	fputs(str, fp);

	str = "\tplayer_direction:90\n";
	fputs(str, fp);

	str = "\tplayer_sector:0\n";
	fputs(str, fp);
}

int			*check3(t_win *win, int sector)
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
}

void		check4(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			printf("%d nb \n", tmp->nb);
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
}

void		write_m4(t_win *win, FILE *fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{

		str = "\tM4A1:";
		fputs(str, fp);

	}

	str = ft_itoa(i);
	fputs(str, fp);

	str = ",0,0,";
	fputs(str, fp);

	//str = ft_itoa(sector); sector
	//fputs(str, fp);

	//str = ",";
	//fputs(str, fp);

	str = ft_itoa(tmp->x / 5);
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5);
	fputs(str, fp);
}

void		write_shotgun(t_win *win, FILE *fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tpompe:";
		fputs(str, fp);
	}

	str = ft_itoa(i);
	fputs(str, fp);

	str = ",1,0,";
	fputs(str, fp);

	//str = ft_itoa(sector); sector
	//fputs(str, fp);

	//str = ",";
	//fputs(str, fp);

	str = ft_itoa(tmp->x / 5);
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5);
	fputs(str, fp);
}

void		write_m4_ammo(t_win *win, FILE *fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tammo:";
		fputs(str, fp);
	}

	str = ft_itoa(i);
	fputs(str, fp);

	str = ",5,0,";
	fputs(str, fp);

	//str = ft_itoa(sector); sector
	//fputs(str, fp);

	//str = ",";
	//fputs(str, fp);

	str = ft_itoa(tmp->x / 5);
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5);
	fputs(str, fp);
}

void		write_m9(t_win *win, FILE *fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\tM9:";
		fputs(str, fp);
	}

	str = ft_itoa(i);
	fputs(str, fp);

	str = ",2,0,";
	fputs(str, fp);

	//str = ft_itoa(sector); sector
	//fputs(str, fp);

	//str = ",";
	//fputs(str, fp);

	str = ft_itoa(tmp->x / 5);
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5);
	fputs(str, fp);
}

void		write_health(t_win *win, FILE *fp, t_lstasset *tmp, int i)
{
	char	*str;

	if (win->lstasset)
	{
		str = "\thealth:";
		fputs(str, fp);
	}

	str = ft_itoa(i);
	fputs(str, fp);

	str = ",3,0,";
	fputs(str, fp);

	//str = ft_itoa(sector); sector
	//fputs(str, fp);

	//str = ",";
	//fputs(str, fp);

	str = ft_itoa(tmp->x / 5);
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5);
	fputs(str, fp);
}

void		write_ennemy(t_win *win, FILE *fp, t_lstasset *tmp, int i)
{
	char		*str;

	if (win->lstasset)
	{
		str = "\tmonstre:";
		fputs(str, fp);
	}

	str = ft_itoa(i);
	fputs(str, fp);

	str = ",6,0,";
	fputs(str, fp);

	//str = ft_itoa(sector); sector
	//fputs(str, fp);

	//str = ",";
	//fputs(str, fp);

	str = ft_itoa(tmp->x / 5);
	fputs(str, fp);

	str = ",";
	fputs(str, fp);

	str = ft_itoa(tmp->y / 5);
	fputs(str, fp);
}

void		write_sprites(t_win *win, FILE *fp)
{
	t_lstasset	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstasset;
	str = "Section:sprite\n";
	fputs(str, fp);

	while (tmp)
	{
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
		if (tmp->asset_type != 0 && tmp->asset_type != 3)
		{
			i++;
			str = "\n";
			fputs(str, fp);
		}
		tmp = tmp->next;
	}
}

void		write_ennemies(t_win *win, FILE *fp)
{
	t_lstasset	*tmp;
	char		*str;
	int			i;

	i = 0;
	tmp = win->lstasset;

	str = "Section:ennemy\n";
	fputs(str, fp);

	while (tmp)
	{
		if (tmp->asset_type == 3)
		{
			write_ennemy(win, fp, tmp, i);
			str = "\n";
			fputs(str, fp);
			i++;
		}
		tmp = tmp->next;
	}
}

void		write_in_file(t_win *win)
{
	FILE		*fp;
	const char	*name;
	char		*buf;
	int			index;

	index = 0;
	name = "custom_map.dn3d";
	fp = fopen(name, "w");
	buf = NULL;

	first_line(win, fp);
	write_dots(win, fp);
	write_sectors(win, fp);
	write_player(win, fp);
	write_sprites(win, fp);
	write_ennemies(win, fp);

	fclose(fp);
}


void		fill_buffer(t_win *win)
{
	sort_points(win);

	write_in_file(win);
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
	while (tmp2)
	{
		//printf("%d triangle sector \n", tmp2->sector);
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

int			correct_map(t_win *win)
{
	int			ret;

	ret = 0;

	//check croisements

	//check overlapping sectors and sectors in sectors

	ret = check_player_start(win);
	if (ret == -1)
		printf("map need a player start \n");
	if (ret == -2)
		printf("player start need to be inside a sector \n");

	return (ret);
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
	if (correct_map(win) == 0)
	{
		if (len - 1 == z)
			fill_buffer(win);
		printf("map saved \n");
	}
	win->number = 0;
	win->same_dots = 0;
	win->index_dot = 0;
	win->tab_index = 0;
}
