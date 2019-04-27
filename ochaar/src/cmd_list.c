/*BIG42HEADER*/

#include "doom.h"

void		seq_cmd(t_env *w, char ***cmd, int i)
{
	w->sequential_draw = 1;
	free(cmd[i][0]);
	cmd[i][0] = ft_strdup("-ok");
}

void		video_mode_cmd(t_env *w, t_map *m, char ***cmd, int i)
{
	if (cmd[i][1] != NULL)
	{
		if (ft_strcmp(cmd[i][1], "FULL_SCREEN") == 0)
			w->window_mode = FULL_SCREEN;
		else if (ft_strcmp(cmd[i][1], "RESIZABLE_SCREN") == 0)
			w->window_mode = RESIZABLE_SCREEN;
		else
			set_error(w, m, 3, ft_strdup(cmd[i][1]));
	}
	free(cmd[i][0]);
	cmd[i][0] = ft_strdup("-ok");
}

void		not_a_command(t_env *w, t_map *m, char ***cmd, char *s)
{
	ft_memreg3(cmd);
	set_error(w, m, 2, ft_strdup(s));
}

void		exit_cmd(t_env *w, t_map *m, char ***cmd)
{
	ft_memreg3(cmd);
	exit_game(w, m);
}

void		map_cmd(t_env *w, t_map *m, char **cmd)
{
	char	**tmp;
	char	**tmp2;

	if (cmd[1] == NULL)
		set_error(w, m, 3, ft_strdup("no map specified"));
	free(m->map_path);
	m->map_path = ft_strdup(cmd[1]);
	tmp = ft_strsplit(cmd[1], '/');
	if (tmp == NULL || tmp[1] == NULL)
		set_error(w, m, 3, ft_strdup("incorrect format"));
	tmp2 = ft_strsplit(tmp[1], '.');
	free(m->map_name);
	m->map_name = ft_strdup(tmp2[0]);
	ft_memreg(tmp);
	ft_memreg(tmp2);
	free(cmd[0]);
	cmd[0] = ft_strdup("-ok");
	m->launchwmap = 1;
}
