//

#include "doom.h"

int			parse_player_section(t_map *m, char **tab)
{
	char	**tmp;

	if (ft_strcmp(tab[0], "\tplayer_location") == 0)
	{
		tmp = ft_strsplit(tab[1], ',');
		m->player.coor.x = ft_atof(tmp[0]);
		m->player.coor.y = ft_atof(tmp[1]);
		ft_memreg(tmp);
	}
	else if (ft_strcmp(tab[0], "\tplayer_direction") == 0)
	{
		m->player.angle = (ft_atof(tab[1]) * M_PI / 180);
		m->player.anglecos = cos(m->player.angle);
		m->player.anglesin = sin(m->player.angle);
	}
	else if (ft_strcmp(tab[0], "\tplayer_sector") == 0)
	{
		m->player.sector = ft_atoi(tab[1]);
		m->player.coor.z = m->sector[m->player.sector].floor + STAND;
	}
	else
		return (-1);
	return (0);
}
