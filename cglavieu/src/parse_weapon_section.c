/**/

#include "doom.h"

int					parse_weapon_section(t_map *m, char **tab)
{
	char			**tmp;

	if (ft_strcmp(tab[0], "\tweapon") == 0)
	{
		if (tab[1])
			m->weapon[m->w].name = ft_strdup(tab[1]);
		tmp = ft_strsplit(tab[2], ',');
		if (tmp != NULL)
		{	
			m->weapon[m->w].range = ft_atoi(tmp[0]);
			if (tmp[1])
				m->weapon[m->w].firerate = ft_atoi(tmp[1]);
			if (tmp[2])
				m->weapon[m->w].accuracy = ft_atoi(tmp[2]);
			if (tmp[3])
				m->weapon[m->w].dispertion = ft_atoi(tmp[3]);
			if (tmp[4])
				m->weapon[m->w].ammo = ft_atoi(tmp[4]);
			if (tmp[5])
				m->weapon[m->w].magazine = ft_atoi(tmp[5]);
		}
		if (tab[3])
			m->weapon[m->w].reloadtime = ft_atof(tab[3]);
		ft_memreg(tmp);
		m->w++;
	}
	return (0);
}