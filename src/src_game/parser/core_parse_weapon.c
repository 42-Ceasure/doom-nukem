
#include "doom.h"

int				fill_arg(int *nb, char *number)
{
	int			i;

	i = 0;
	while (number[i] != '\0')
	{
		if (ft_isdigit((int)number[i]) != 1)
			return (-1);
		i++;
	}
	i = ft_atoi(number);
	*nb = i;
	return (0);
}

void			fill_weapon_int(t_map *m, char **tmp)
{
	int			i;

	i = 0;
	while (tmp[i] != NULL)
	{
		if (i == 0 && fill_arg(&m->weap[m->w].range, tmp[i]) != 0)
			set_error(m->world, m, 911, ft_strdup("weapon line"));
		if (i == 1 && fill_arg(&m->weap[m->w].firerate, tmp[i]) != 0)
			set_error(m->world, m, 911, ft_strdup("weapon line"));
		if (i == 2 && fill_arg(&m->weap[m->w].accuracy, tmp[i]) != 0)
			set_error(m->world, m, 911, ft_strdup("weapon line"));
		if (i == 4 && fill_arg(&m->weap[m->w].ammo_type, tmp[i]) != 0)
			set_error(m->world, m, 911, ft_strdup("weapon line"));
		if (i == 5 && fill_arg(&m->weap[m->w].magazine, tmp[i]) != 0)
			set_error(m->world, m, 911, ft_strdup("weapon line"));
		if (i == 6 && fill_arg(&m->weap[m->w].recoil, tmp[i]) != 0)
			set_error(m->world, m, 911, ft_strdup("weapon line"));
		i++;
	}
}

void			parse_weapon_line(t_map *m, char *line)
{
	char		**tmp;
	char		**tmp2;
	int			check;

	check = 0;
	tmp2 = ft_strsplit(line, ':');
	while (tmp2[check] != NULL)
		check++;
	if (check != 3)
		set_error(m->world, m, 911, ft_strdup("weapon line"));
	m->weap[m->w].name = ft_strdup(tmp2[0]);
	tmp = ft_strsplit(tmp2[1], ',');
	check = 0;
	while (tmp[check] != NULL)
		check++;
	if (check != 7)
		set_error(m->world, m, 911, ft_strdup("weapon line"));
	m->weap[m->w].reloadtime = ft_atof(tmp2[2]);
	m->weap[m->w].dispertion = ft_atof(tmp[3]);
	fill_weapon_int(m, tmp);
	ft_memreg(tmp2);
	ft_memreg(tmp);
	m->w++;
}
