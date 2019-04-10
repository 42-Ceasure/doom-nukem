//

#include "doom.h"

void		l_f_priority_cmd(t_env *w, t_map *m, char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i][0], "-video_mode") == 0)
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
		if (ft_strcmp(cmd[i][0], "-seq") == 0)
		{
			w->sequential_draw = 1;
			free(cmd[i][0]);
			cmd[i][0] = ft_strdup("-ok");
		}
		i++;
	}
	if ((init_sdl(w)) == -1)
			set_error(w, m, 0);
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
		if (ft_strcmp(cmd[i][0], "-map") == 0)
		{
			map_cmd(w, m, cmd[i]);
			parse_map_file(w, m);
		}
		else if (ft_strcmp(cmd[i][0], "-list") == 0)
			recap_parsing(m, cmd[i]);
		else if (ft_strcmp(cmd[i][0], "-exit") == 0)
		{
			ft_memreg3(cmd);
			exit_game(w, m);
		}
		else
		{
			ft_memreg3(cmd);
			set_error(w, m, 0);
		}
		i++;
	}
	ft_memreg3(cmd);
}
