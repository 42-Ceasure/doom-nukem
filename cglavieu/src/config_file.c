/*BIG42HEADER*/

#include "doom.h"

void			generate_config_file(int fd)
{
	int fd2;
	char *line;
	char *path;

	line = NULL;
	path = ft_strdup("usrcfg/base_cfg.dn3d");
	if ((fd2 = open(path, O_RDONLY)) != -1)
	{
		while (get_next_line(fd2, &line))
		{
			ft_putendl_fd(line, fd);
			free(line);
		}
		free(line);
		close(fd2);
	}
	free(path);
}

void			set_screen_res(t_env *w, char *ratio)
{
	int			n;

	n = ft_atoi(ratio);
	if (n == 0) //			16/9
		w->res.width = w->res.height * 16 / 9;
	else if (n == 1)
		w->res.width = w->res.height * 4 / 3;
	else
	{
		w->res.width = BASEWIDTH;
		w->res.height = BASEHEIGHT;
	}
}

void			parse_config_file(t_env *w, t_map *m, char *line)
{
	char **tmp;

	tmp = ft_strsplit(line, ':');
	if (tmp[0] != NULL && tmp[1] != NULL)
	{
		if (ft_strcmp(tmp[0], "\twindow_mode") == 0)
			w->window_mode = ft_atoi(tmp[1]);
		else if (ft_strcmp(tmp[0], "\twindow_height") == 0)
			w->res.height = ft_atoi(tmp[1]);
		else if (ft_strcmp(tmp[0], "\twindow_ratio") == 0)
			set_screen_res(w, tmp[1]);
		else if (ft_strcmp(tmp[0], "\tHfov") == 0)
			m->player.field_of_vision_h = ft_atof(tmp[1]);
		else if (ft_strcmp(tmp[0], "\tVfov") == 0)
			m->player.field_of_vision_v = ft_atof(tmp[1]);
		else if (ft_strcmp(tmp[0], "\tmouse_speed") == 0)
			m->player.mousesp = ft_atof(tmp[1]);
	}
	ft_memreg(tmp);
}
