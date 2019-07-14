/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   neighbour.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 10:09:03 by abechet           #+#    #+#             */
/*   Updated: 2019/06/18 10:09:17 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		ret_neighbour_sector(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	// int			headx;	/* unused */
	// int			heady;	/* unused */

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp)
		{
			// headx = tmp->x;	/* unused */
			// heady = tmp->y;	/* unused */
			;
		}
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (tmp->sector);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (tmp->sector);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (-1);
}

int		check_segment(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	// int			headx;	/* unused */
	// int			heady;	/* unused */

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp)
		{
			// headx = tmp->x;	/* unused */
			// heady = tmp->y;	/* unused */
		}
		while (tmp)
		{
			if (tmp->next)
			{
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

int		which_sector_neighbour(t_win *win, int x1, int y1, int x2, int y2, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	// int			headx;	/* unused */
	// int			heady;	/* unused */

	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		if (tmp)
		{
			// headx = tmp->x;	/* unused */
			// heady = tmp->y;	/* unused */
			;
		}
		while (tmp)
		{
			if (tmp->next)
			{
				if ((x1 == tmp->x && y1 == tmp->y)
					&& (x2 == tmp->next->x && y2 == tmp->next->y)
						&& sector != tmp->sector)
					return (tmp->sector);
				if ((y1 == tmp->next->y && x1 == tmp->next->x)
					&& (y2 == tmp->y && x2 == tmp->x)
						&& sector != tmp->sector)
					return (tmp->sector);
			}
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	return (-1);
}

int		check_neighbour(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			sector;
	int			ret;
	int			neighbour;

	int			headx;
	int			heady;

	neighbour = 0;
	if (win->lstlst == NULL)
		return (-1);
	tmp2 = win->lstlst;
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
			ret = 0;
			x1 = tmp->x;
			y1 = tmp->y;
			sector = tmp->sector;
			if (tmp->next)
			{
				x2 = tmp->next->x;
				y2 = tmp->next->y;
			}
			else
			{
				x2 = headx;
				y2 = heady;
			}
			ret = check_segment(win, x1, y1, x2, y2, sector);
			if (ret == 1)
				neighbour += 1;
			tmp = tmp->next;
		}
		tmp2 = tmp2->next;
	}
	//printf("%d neighbours \n", neighbour);
	return (neighbour);
}

int		number_of_neighbours_in_sector(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			ret;
	int			neighbour;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			headx;
	int			heady;

	neighbour = 0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			if (tmp)
			{
				headx = tmp->x;
				heady = tmp->y;
			}

			while (tmp)
			{
				ret = 0;
				x1 = tmp->x;
				y1 = tmp->y;
				//sector = tmp->sector;
				if (tmp->next)
				{
					x2 = tmp->next->x;
					y2 = tmp->next->y;
				}
				else
				{
					x2 = headx;
					y2 = heady;
				}
				ret = check_segment(win, x1, y1, x2, y2, sector);
				if (ret == 1)
					neighbour += 1;
				tmp = tmp->next;
			}
		}
		tmp2 = tmp2->next;
	}
	return (neighbour);
}

int		*get_neighbours(t_win *win, int sector)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;
	int			i;
	int			index;
	int			ret;
	int			*neighbour_tab;
	int			x1;
	int			y1;
	int			x2;
	int			y2;
	int			headx;
	int			heady;

	index = 0;

	neighbour_tab = NULL;
	i = number_of_neighbours_in_sector(win, sector);

	if (i == 0)
		return (neighbour_tab);

	if (!(neighbour_tab = (int *)malloc(sizeof(int) * i)))
		clear_n_exit(win, 1);

	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == sector)
		{
			tmp = tmp2->head;
			if (tmp)
			{
				headx = tmp->x;
				heady = tmp->y;
			}
			while (tmp)
			{
				x1 = tmp->x;
				y1 = tmp->y;
				if (tmp->next)
				{
					x2 = tmp->next->x;
					y2 = tmp->next->y;
				}
				else
				{
					x2 = headx;
					y2 = heady;
				}
				ret = ret_neighbour_sector(win, x1, y1, x2, y2, sector);
				if (ret != -1)
				{
					neighbour_tab[index] = ret;
					index++;
				}
				tmp = tmp->next;
			}
		}
		tmp2 = tmp2->next;
	}
	return (neighbour_tab);
}

/*
void		check2(t_win *win)
{
	int			*tab;
	FILE		*fp;
	const char	*name;
	char		**buf = NULL;
	int			index;

	index = 0;
	name = "editor_map";
	printf("%d neighbours in sector 0 \n",number_of_neighbours_in_sector(win, 0));

	tab = get_neighbours(win, 0);

	fp = fopen(name, "a");

	buf[0] = "dots:10,sector:4,sprite:8,ennemy:4\n";
	buf[1] = "Section:map\n";
	buf[2] = 	"dots:0:40,80\n";
	buf[3] = 	"dots:20:0,40,80\n";
	buf[4] = 	"dots:60:0,40,80\n";
	buf[5] = 	"dots:100:40,80\n";
	buf[6] = 	"sector:0,50:2,3,6,5:x,1,x,x:3,5,3,2,2,0\n";
	buf[7] = 	"sector:0,50:3,4,7,6:2,x,3,0:6,5,3,2,2,0\n";
	buf[8] = 	"sector:0,50:0,1,4,3:x,x,1,x:3,5,3,2,2,0\n";
	buf[9] = 	"sector:0,70:6,7,9,8:1,x,x,x:2,5,2,2,2,7\n";
	buf[10] = "Section:player\n";
	buf[11] = 	"player_location:5,5\n";
	buf[12] = 	"player_direction:90\n";
	buf[13] = 	"player_sector:0\n";
	buf[14] = "Section:sprite\n";
	buf[15] = 	"health:0,3,1,10,30\n";
	buf[16] = 	"health:1,3,0,10,10\n";
	buf[17] = 	"cartouche:2,4,0,15,15\n";
	buf[18] = 	"cartouche:3,4,1,25,35\n";
	buf[19] = 	"M4A1:4,0,2,25,70\n";
	buf[20] = 	"M4A1:5,0,2,20,85\n";
	buf[21] = 	"M9:6,2,0,20,10\n";
	buf[22] = 	"pompe:7,1,1,5,40\n";
	buf[23] = "Section:ennemy\n";
	buf[24] = 	"monstre:0,5,2,20,90\n";
	buf[25] = 	"monstre:1,5,2,25,70\n";
	buf[26] = 	"monstre:2,5,1,12,42\n";
	buf[27] = 	"monstre:3,5,0,30,15\n";

	while (index < 28)
	{
		ft_putstr_fd(buf[index], fp);
		index++;
	}
}*/
