/**/

#include "doom.h"

Uint32		*faster_please(Uint32 *dst, char *src, int len)
{
	int				i;
	int				i2;
	int				i3;
	char			*current;

	i = 0;
	i3 = 0;
	current = (char *)malloc(sizeof(char) * 9);
	while (i3 < len)
	{
		i2 = 0;
		while (src[i] != ',' && src[i] != '\0')
		{
			current[i2] = src[i];
			i++;
			i2++;
			if (i2 == 9)
			{
				ft_putendl("\n");
				ft_putnbr(i3);
				ft_putendl("\n");
			}
		}
		current[i2] = '\0';
		dst[i3] = ft_atoui_base(current, 16);
		// print_load("loading texture : ", i3, len);
		i3++;
		i++;
	}
	free(current);
	return (dst);
}

int			parse_weapon_sprite(t_map *m, char *name, char *def, char *pix)
{
	int				i;
	int				wn;
	int				sn;
	char			**tmp;

	// printf("name:%s,def:%s\n", name, def);
	tmp = ft_strsplit(def, ',');
	wn = ft_atoi(tmp[0]);
	sn = ft_atoi(tmp[1]);
	// printf("wn:%d,sn:%d\n", wn, sn);
	m->weap[wn].sprt[sn].name = ft_strdup(name);
	m->weap[wn].sprt[sn].sx = ft_atoi(tmp[2]);
	m->weap[wn].sprt[sn].sy = ft_atoi(tmp[3]);
	m->weap[wn].sprt[sn].w = ft_atoi(tmp[4]);
	m->weap[wn].sprt[sn].h = ft_atoi(tmp[5]);
	i = ft_atoi(tmp[4]) * ft_atoi(tmp[5]);
	m->weap[wn].sprt[sn].len = i;
	process_hint_w(m->world, 1, "textures");
	m->weap[wn].sprt[sn].pix = (Uint32 *)malloc(sizeof(Uint32) * i);
	process_hint_w(m->world, 6, name);
	process_hint_w(m->world, 0, " ");
	m->weap[wn].sprt[sn].pix = faster_please(m->weap[wn].sprt[sn].pix, pix, i);
	process_hint_w(m->world, 0, " ");
	// printf("%u\n", m->weap[wn].sprt[sn].pix[0]);
	ft_memreg(tmp);
	return (0);
}

int			parse_sprite_section(t_map *m, char **tab)
{
	if (ft_strcmp(tab[0], "\tweapon_sprite") == 0)
	{
		process_hint_w(m->world, 4, "weapon sprite");
		if (parse_weapon_sprite(m, tab[1], tab[2], tab[3]) == -1)
		{
			ft_putendl("error on parsing of the weapon_sprite section");
			return (-1);
		}
	}
	// if (ft_strcmp(tab[0], "\thp") == 0)
	// 	m->hud = parse_texture(m->world, m, tab);
	return (0);
}