// retirer les printf

#include "doom.h"

void	recap_player_list_vars(t_map m, char *str)
{
	ft_putstr(str);
	ft_putendl(" :\n");
	ft_putstr("player_sector = ");
	ft_putnbrendl((int)m.player.sector);
	ft_putstr("player_coor : x = ");
	ft_putnbr((int)m.player.coor.x);
	ft_putstr(", y = ");
	ft_putnbrendl((int)m.player.coor.y);
	ft_putstr("player_direction = ");
	ft_putnbrendl((int)m.player.angle);
	ft_putchar('\n');
}

void	recap_map_list_general(t_map m, char *str)
{
	ft_putstr(str);
	ft_putendl(" :\n");
	ft_putstr("map_section_number = ");
	ft_putnbrendl(m.section_number);
	ft_putstr("map_dots_count = ");
	ft_putnbrendl(m.dots_count);
	ft_putstr("map_sector_count = ");
	ft_putnbrendl(m.sector_count);
	ft_putstr("map_name = ");
	ft_putendl(m.map_name);
	ft_putstr("map_path = ");
	ft_putendl(m.map_path);
	ft_putchar('\n');
}

void	recap_map_list_dots(t_map m, char *str)
{
	int i;

	i = 0;
	ft_putstr(str);
	ft_putendl(" :\n");
	while (i < m.dots_count)
	{
		ft_putstr("dot_");
		ft_putnbr(i);
		ft_putstr(" : x = ");
		ft_putnbr((int)m.dot[i].x);
		ft_putstr(", y = ");
		ft_putnbrendl(m.dot[i].y);
		i++;
	}
	ft_putchar('\n');
}

void	recap_map_list_sectors(t_map m, char *str)
{
	int i;
	int j;

	i = 0;
	ft_putstr(str);
	ft_putendl(" :\n");
	while (i < m.sector_count)
	{
		j = 0;
		printf("sector %d : wall_count = %d\n", i, m.sector[i].wall_count);
		printf("sector %d : floor_height = %f\n", i, m.sector[i].floor);
		printf("sector %d : ceiling_height = %f\n", i, m.sector[i].ceiling);
		while (j < m.sector[i].wall_count)
		{
			printf("dot_%d : x = %f, y = %f\n", j, m.sector[i].dot[j].x, m.sector[i].dot[j].y);
			j++;
		}
		j = 0;
		while (j < m.sector[i].wall_count)
		{
			printf("network_%d : %d\n", j, m.sector[i].network[j]);
			j++;
		}
		i++;
	}
	ft_putchar('\n');
}

void	recap_map_list_sector(t_map m, char **str)
{
	int i;
	int j;

	i = 0;
	if (str[3] != NULL)
	{
		if (ft_strcmp(str[3], "all") == 0)
		{
			if (str[4] == NULL)
				recap_map_list_sectors(m, str[2]);
			else
			{
				while (i < m.sector_count)
				{
					j = 0;
					ft_putstr("sector : ");
					ft_putnbrendl(i);
					if (ft_strcmp(str[4], "general") == 0)
					{
						printf("wall_count = %d\n", m.sector[i].wall_count);
						printf("floor_height = %f\n", m.sector[i].floor);
						printf("ceiling_height = %f\n", m.sector[i].ceiling);
					}
					else if (ft_strcmp(str[4], "dots") == 0)
					{
						while (j < m.sector[i].wall_count)
						{
							printf("dot_%d : x = %f, y = %f\n", j, m.sector[i].dot[j].x, m.sector[i].dot[j].y);
							j++;
						}
					}
					else if (ft_strcmp(str[4], "network") == 0)
					{
						while (j < m.sector[i].wall_count)
						{
							printf("wall_%d : %d\n", j, m.sector[i].network[j]);
							j++;
						}
					}
					else
					{
						ft_putstr("there is no \"");
						ft_putstr(str[4]);
						ft_putstr("\" section in sector ");
						ft_putnbrendl(i);
					}
					i++;
				}
			}
		}
		if (ft_isdigit(str[3][0]) == 1)
		{
			i = ft_atoi(str[3]);
			if (i < m.sector_count)
			{
				if (str[4] == NULL)
				{
					j = 0;
					printf("sector %d : wall_count = %d\n", i, m.sector[i].wall_count);
					printf("sector %d : floor_height = %f\n", i, m.sector[i].floor);
					printf("sector %d : ceiling_height = %f\n", i, m.sector[i].ceiling);
					while (j < m.sector[i].wall_count)
					{
						printf("dot_%d : x = %f, y = %f\n", j, m.sector[i].dot[j].x, m.sector[i].dot[j].y);
						j++;
					}
					j = 0;
					while (j < m.sector[i].wall_count)
					{
						printf("network_%d : %d\n", j, m.sector[i].network[j]);
						j++;
					}
				}
			}
			else
				ft_putendl("this sector don't exist...");
		}
	}
	ft_putchar('\n');
}

void	recap_parsing(t_map *m, char **str)
{
	if (ft_strcmp(str[1], "map_general") == 0)
		recap_map_list_general(*m, str[1]);
	else if (ft_strcmp(str[1], "map_dots") == 0)
		recap_map_list_dots(*m, str[1]);
	else if (ft_strncmp(str[1], "map_sector", 10) == 0)
	{
		if (ft_strcmp(str[1], "map_sectors") == 0)
			recap_map_list_sectors(*m, str[1]);
		else if (ft_strcmp(str[1], "map_sector") == 0)
			recap_map_list_sector(*m, str);
	}
	else if (ft_strcmp(str[1], "player_vars") == 0)
		recap_player_list_vars(*m, str[1]);
	else
		ft_putstr("invalid section");
	set_basic_run(m);
}
