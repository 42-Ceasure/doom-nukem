//

#include "doom.h"

void	map_cmd(t_env *w, t_map *m, char **cmd)
{
	char **tmp;
	char **tmp2;

	if (cmd[1] == NULL)
		set_error(w, m, 10);
	m->map_path = cmd[1];
	tmp = ft_strsplit(cmd[1], '/');
	if (tmp == NULL || tmp[1] == NULL)
		set_error(w, m, 11);
	tmp2 = ft_strsplit(tmp[1], '.');
	m->map_name = tmp2[0];
	ft_memreg(tmp);
	ft_memreg(tmp2);
}
