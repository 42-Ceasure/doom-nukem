//

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
			set_error(w, m, 0);
	}
	free(cmd[i][0]);
	cmd[i][0] = ft_strdup("-ok");
}

void	not_a_command(t_env *w, t_map *m, char ***cmd)
{
	ft_memreg3(cmd);
	set_error(w, m, 0);
}

void	exit_cmd(t_env *w, t_map *m, char ***cmd)
{
	ft_memreg3(cmd);
	exit_game(w, m);
}

void	map_cmd(t_env *w, t_map *m, char **cmd)
{
	char **tmp;
	char **tmp2;

	if (cmd[1] == NULL)
		set_error(w, m, 0);
	m->map_path = cmd[1];
	tmp = ft_strsplit(cmd[1], '/');
	if (tmp == NULL || tmp[1] == NULL)
		set_error(w, m, 0);
	tmp2 = ft_strsplit(tmp[1], '.');
	m->map_name = tmp2[0];
	ft_memreg(tmp);
	ft_memreg(tmp2);
	parse_map_file(w, m);
}
