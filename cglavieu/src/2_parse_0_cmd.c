//

#include "doom.h"

void		interpret_cmd(t_env *w, t_map *m, char ***cmd)
{
	int i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i][0], "-map") == 0)
			map_cmd(m, cmd[i]);
		if (ft_strcmp(cmd[i][0], "-seq") == 0)
			w->sequential_draw = 1;
		if (ft_strcmp(cmd[i][0], "-list") == 0)
			recap_parsing(m, cmd[i]);
		i++;
	}
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

char		***parse_cmd(int ac, char **av)
{
	int		i;
	int		cmd_count;
	char	**tmp;
	char	***cmd;

	i = 0;
	cmd_count = 0;
	tmp = (char **)malloc(sizeof(char *) * (ac));
	cmd = NULL;
	tmp[ac - 1] = NULL;
	while (ac--)
		tmp[ac] = ft_strtrim(av[ac + 1]);
	if (ft_strncmp(tmp[0], "-", 1) == 0)
	{
		while (tmp[i])
		{
			if (ft_strncmp(tmp[i], "-", 1) == 0)
				cmd_count++;
			i++;
		}
		cmd = assemble_cmd_args(cmd, tmp, cmd_count);
	}
	else
		ft_putendl("error on command");
	return (cmd);
}
