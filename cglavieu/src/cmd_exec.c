/*BIG42HEADER*/

#include "doom.h"

void		extract_bmp(t_env *w, t_map *m, char **cmd)
{
	t_texture	texture;
	int			i;
	char		*str;

	i = 0;
	texture = load_img(w, m, cmd[1]);
	ft_putnbr(texture.w);
	ft_putchar(',');
	ft_putnbr(texture.h);
	ft_putchar(':');
	while (i < texture.w * texture.h)
	{
		str = ft_uitoa_base(texture.pix[i], 16);
		ft_putstr(str);
		i++;
		if (i < texture.w * texture.h)
			ft_putchar(',');
	}
	ft_putchar('\n');
	exit_game(w, m, 1);
}

void		l_f_priority_cmd(t_env *w, t_map *m, char ***cmd)
{
	int		i;

	i = 0;
	while (cmd[i] != NULL)
	{
		if (ft_strcmp(cmd[i][0], "-video_mode") == 0)
			video_mode_cmd(w, m, cmd, i);
		else if (ft_strcmp(cmd[i][0], "-seq") == 0)
			seq_cmd(w, cmd, i);
		else if (ft_strcmp(cmd[i][0], "-map") == 0)
			map_cmd(w, m, cmd[i]);
		else if (ft_strcmp(cmd[i][0], "-extract_bmp") == 0)
			extract_bmp(w, m, cmd[i]);
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
			recap_parsing(w, m, cmd[i]);
		else if (ft_strcmp(cmd[i][0], "-exit") == 0)
			exit_cmd(w, m, cmd);
		else
			not_a_command(w, m, cmd, ft_strdup(cmd[i][0]));
		i++;
	}
	ft_memreg3(cmd);
}

void			exec_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int ac;

	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		process_hint(3, "priority cmd");
		l_f_priority_cmd(w, m, cmd);
		process_hint(0, " ");
		process_hint(2, "SDL2");
		if ((init_sdl(w)) == -1)
			set_error(w, m, 4, ft_strdup("SDL Initialisation"));
		process_hint(0, " ");
		process_hint(4, "map");;
		parse_map_file(w, m);
		process_hint(0, " ");
		process_hint(3, "remaining cmd");
		interpret_cmd(w, m, cmd);
		process_hint(0, " ");
	}
	else
		set_error(w, m, 1, ft_strdup(av[1]));
}
