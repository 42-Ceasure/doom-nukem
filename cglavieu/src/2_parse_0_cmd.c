//

#include "doom.h"

void		l_f_priority_cmd(t_env *w, char ***cmd)
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
					w->window_mode = 1;
			}
		}
		if (ft_strcmp(cmd[i][0], "-seq") == 0)
			w->sequential_draw = 1;
		else
			w->sequential_draw = 0;

		i++;
	}
}

void		interpret_cmd(t_env *w, t_map *m, char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i][0], "-map") == 0)
		{
			map_cmd(w, m, cmd[i]);
			if (quick_look(m) == -1 || do_parse(m) == -1)
				set_error(w, m, 13);
		}
		if (ft_strcmp(cmd[i][0], "-list") == 0)
			recap_parsing(m, cmd[i]);
		if (ft_strcmp(cmd[i][0], "-exit") == 0)
		{
			ft_memreg(*cmd);
			exit_game(w, m);
		}
		i++;
	}
	ft_memreg3(cmd);
}

char		***assemble_cmd_args(char ***cmd, char **tmp, int cmd_count)
{
	int		j;
	int		i;
	int		i2;
	int		x;

	j = 0;
	i = 0;
	cmd = (char ***)malloc(sizeof(char **) * (cmd_count + 1));
	cmd[cmd_count] = NULL;
	while (j < cmd_count)
	{
		i2 = 1;
		while (ft_strncmp(tmp[i + i2], "-", 1) != 0)
			i2++;
		cmd[j] = (char **)malloc(sizeof(char *) * (i2 + 1));
		cmd[j][i2] = NULL;
		x = 0;
		while (x < i2)
		{
			cmd[j][x] = tmp[i++];
			x++;
		}
		j++;
	}
	return (cmd);
}

char		***lol(char ***cmd, int ac, char **av)
{
	int		i;
	int		cmd_count;
	char	**tmp;

	i = 0;
	cmd_count = 0;
	tmp = (char **)malloc(sizeof(char *) * (ac));
	tmp[ac - 1] = NULL;
	while (ac--)
		tmp[ac] = ft_strtrim(av[ac + 1]);
	if (ft_strncmp(tmp[0], "-", 1) == 0 && ft_strcmp(tmp[0], "-") != 0)
	{
		while (tmp[i])
		{
			if (ft_strncmp(tmp[i], "-", 1) == 0)
				cmd_count++;
			i++;
		}
		cmd = assemble_cmd_args(cmd, tmp, cmd_count);
	}
	free(tmp);
	return (cmd);
}

char		***parse_cmd(int ac, char **av)
{
	char	***cmd;

	cmd = NULL;
	if ((cmd = lol(cmd, ac, av))== NULL)
		return (NULL);
	else
	return (cmd);
}
