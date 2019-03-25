// retirer les printf

#include "doom-nukem.h"

void	recap_player_list_vars(t_map *m)
{
	ft_putstr("player_sector = ");
	ft_putnbrendl((int)m->player.sector);
	ft_putstr("player_coor : x = ");
	ft_putnbr((int)m->player.coor.x);
	ft_putstr(", y = ");
	ft_putnbrendl((int)m->player.coor.y);
	ft_putstr("player_direction = ");
	ft_putnbrendl((int)m->player.angle);
}

void	recap_map_general(t_map *m)
{
	ft_putstr("map_section_number = ");
	ft_putnbrendl(m->section_number);
	ft_putstr("map_dots_count = ");
	ft_putnbrendl(m->dots_count);
	ft_putstr("map_sector_count = ");
	ft_putnbrendl(m->sector_count);
	ft_putstr("map_name = ");
	ft_putendl(m->map_name);
	ft_putstr("map_path = ");
	ft_putendl(m->map_path);
}

void	recap_map_list_dots(t_map *m)
{
	int i;

	i = 0;
	while (i < m->dots_count)
		{
			ft_putstr("point_");
			ft_putnbr(i);
			ft_putstr(" : x = ");
			ft_putnbr((int)m->dot[i].x);
			ft_putstr(", y = ");
			ft_putnbrendl(m->dot[i].y);
			i++;
		}
}

void	recap_map_list_sectors(t_map *m)
{
	int i;
	int j;

	i = 0;
	while (i < m->sector_count)
		{
			j = 0;
			printf("sector %d : wall_count = %d\n", i, m->sector[i].wall_count);
			printf("sector %d : floor_height = %f\n", i, m->sector[i].floor);
			printf("sector %d : ceiling_height = %f\n", i, m->sector[i].ceiling);
			while (j < m->sector[i].wall_count)
			{
				printf("point_%d : x = %f, y = %f\n", j, m->sector[i].dot[j].x, m->sector[i].dot[j].y);
				j++;
			}
			j = 0;
			while (j < m->sector[i].wall_count)
			{
				printf("network_%d : %s\n", j, m->sector[i].network[j]);
				j++;
			}
			i++;
		}
}

void	recap_parsing(t_map *m, char *str)
{
	ft_putstr(str);
	ft_putendl(" :\n");
	if (ft_strcmp(str, "map_general") == 0)
		recap_map_general(m);
	if (ft_strcmp(str, "map_list_dots") == 0)
		recap_map_list_dots(m);
	if (ft_strcmp(str, "map_list_sectors") == 0)
		recap_map_list_sectors(m);
	if (ft_strcmp(str, "player_list_vars") == 0)
		recap_player_list_vars(m);
	ft_putchar('\n');
}
