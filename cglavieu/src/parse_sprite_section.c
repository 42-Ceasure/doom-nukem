/**/

#include "doom.h"

int					parse_weapon_sprite(t_map *m, char *name, char *def, char *pix)
{
	int				i;
	int				weapon_number;
	int				sprite_number;
	char			**tmp;
	char			**tmp2;

	i = 0;
	tmp = ft_strsplit(def, ',');
	weapon_number = ft_atoi(tmp[0]);
	sprite_number = ft_atoi(tmp[1]);
	m->weapon[weapon_number].sprite[sprite_number].name = ft_strdup(name);
	m->weapon[weapon_number].sprite[sprite_number].w = ft_atoi(tmp[2]);
	m->weapon[weapon_number].sprite[sprite_number].h = ft_atoi(tmp[3]);
	m->weapon[weapon_number].sprite[sprite_number].pix = (Uint32 *)malloc(sizeof(Uint32) * ft_atoi(tmp[2]) * ft_atoi(tmp[3]));
	ft_putendl("parsing sprite");
	tmp2 = ft_strsplit(pix, ',');
	while (i < ft_atoi(tmp[2]) * ft_atoi(tmp[3]))
	{
		m->weapon[weapon_number].sprite[sprite_number].pix[i] = ft_atounsigned(tmp2[i]);
		i++;
	}
	ft_memreg(tmp);
	ft_memreg(tmp2);
	return (0);
}

int					parse_sprite_section(t_map *m, char **tab)
{
	if (ft_strcmp(tab[0], "\tweapon_sprite") == 0)
	{
		if (parse_weapon_sprite(m, tab[1], tab[2], tab[3]) == -1)
		{
			ft_putendl("error on parsing of the weapon_sprite section");
			return (-1);
		}	
	}
	return (0);
}