/**/

#include "doom.h"

void				print_load(int i3, int len)
{
	char			*pre;
	char			*nb;
	char			*post;

	nb = ft_itoa((int)((double)i3 / (double)len * 100));
	post = ft_strjoin(nb, "  \r");
	pre = ft_strjoin( "loading texture : ", post);
	ft_putstr(pre);
	free(nb);
	free(post);
	free(pre);
}

Uint32				*faster_please(Uint32 *dst, char *src, int len)
{
	int				i;
	int				i2;
	int				i3;
	char			*current;

	i = 0;
	i3 = 0;
	current = (char *)malloc(sizeof(char) * 11);
	while (i3 < len)
	{
		i2 = 0;
		while (src[i] != ',' && src[i] != '\0')
		{
			current[i2] = src[i];
			i++;
			i2++;
		}
		current[i2] = '\0';
		dst[i3] = ft_atoui_base(current, 16);
		print_load(i3, len);
		i3++;
		i++;
	}
	free(current);
	return (dst);
}

int					parse_weapon_sprite(t_map *m, char *name, char *def, char *pix)
{
	int				i;
	int				wn;
	int				sn;
	char			**tmp;

	tmp = ft_strsplit(def, ',');
	wn = ft_atoi(tmp[0]);
	sn = ft_atoi(tmp[1]);
	m->weap[wn].sprt[sn].name = ft_strdup(name);
	m->weap[wn].sprt[sn].sx = ft_atoi(tmp[2]);
	m->weap[wn].sprt[sn].sy = ft_atoi(tmp[3]);
	m->weap[wn].sprt[sn].w = ft_atoi(tmp[4]);
	m->weap[wn].sprt[sn].h = ft_atoi(tmp[5]);
	i = ft_atoi(tmp[4]) * ft_atoi(tmp[5]);
	ft_putstr("allocating memory for texture             \r");
	m->weap[wn].sprt[sn].pix = (Uint32 *)malloc(sizeof(Uint32) * i);
	ft_putstr("starting sprite extraction : ");
	ft_putstr(name);
	ft_putstr("\r                                                                \r");
	m->weap[wn].sprt[sn].pix = faster_please(m->weap[wn].sprt[sn].pix, pix, i);
	ft_putstr("done                                             \r");
	ft_memreg(tmp);
	return (0);
}

int					parse_sprite_section(t_map *m, char **tab)
{
	if (ft_strcmp(tab[0], "\tweapon_sprite") == 0)
	{
		ft_putstr("parsing weapon sprite      \r");
		if (parse_weapon_sprite(m, tab[1], tab[2], tab[3]) == -1)
		{
			ft_putendl("error on parsing of the weapon_sprite section");
			return (-1);
		}	
	}
	return (0);
}