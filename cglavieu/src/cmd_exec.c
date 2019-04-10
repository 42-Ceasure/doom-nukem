/*BIG42HEADER*/

#include "doom.h"

void		l_f_priority_cmd(t_env *w, t_map *m, char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i][0], "-video_mode") == 0)
			video_mode_cmd(w, m, cmd, i);
		if (ft_strcmp(cmd[i][0], "-seq") == 0)
			seq_cmd(w, cmd, i);
		if (ft_strcmp(cmd[i][0], "-map") == 0)
			map_cmd(w, m, cmd[i]);
		i++;
	}
}

void		interpret_cmd(t_env *w, t_map *m, char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i][0], "-ok") == 0)
		{
			i++;
			continue;
		}
		else if (ft_strcmp(cmd[i][0], "-list") == 0)
			recap_parsing(m, cmd[i]);
		else if (ft_strcmp(cmd[i][0], "-exit") == 0)
			exit_cmd(w, m, cmd);
		else
			not_a_command(w, m, cmd, ft_strdup(cmd[i][0]));
		i++;
	}
	ft_memreg3(cmd);
}
