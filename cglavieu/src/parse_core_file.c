/*BIG42HEADER*/

#include "doom.h"

t_menu		parse_menu_line(t_env *w, char **tmp)
{
	char	**tmp2;
	t_menu	menu;
	int		i;
	int		entryc;

	i = 0;
	w->i = 0;
	menu.z = 0;
	menu.i = 0;
	menu.j = 0;
	while (tmp[menu.z + 1])
		menu.z++;
	menu.y = (int *)malloc(sizeof(int) * (menu.z + 1));
	menu.y[0] = 0;
	menu.list = (char ***)malloc(sizeof(char **) * (menu.z + 1));
	menu.list[menu.z] = NULL;
	while (i < menu.z)
	{
		entryc = 1;
		tmp2 = ft_strsplit(tmp[i + 1], ',');
		while (tmp2[entryc] != NULL)
			entryc++;
		menu.y[i + 1] = entryc -1;
		menu.list[i] = (char **)malloc(sizeof(char *) * (entryc + 1));
		menu.list[i][entryc] = NULL;
		entryc--;
		while (entryc >= 0)
		{
			menu.list[i][entryc] = ft_strdup(tmp2[entryc]);
			entryc--;
		}
		ft_memreg(tmp2);
		i++;
	}
	return (menu);
}

void		parse_core_file(t_env *w, t_map *m, char *line)
{
	char	**tmp;

	w->txthead.x = 800;
	w->txthead.y = 550;
	tmp = ft_strsplit(line, ':');
	if (tmp[0] != NULL)
	{
		if (ft_strcmp(tmp[0], "\tmenu") == 0)
			w->menu = parse_menu_line(w, tmp);
		if (ft_strcmp(tmp[0], "\tascii") == 0 && w->asciino < 42)
		{
			w->ascii[w->asciino] = parse_texture(w, m, tmp);
			w->asciino++;
		}
		if (ft_strcmp(tmp[0], "\tmain_pic[0]") == 0)
		{
			if (w->main_pic[0].pix != NULL)
				free(w->main_pic[0].pix);
			w->main_pic[0] = parse_texture(w, m, tmp);
			hello_screen(w);
			type_str(w, w->txthead, "loading game...", 0x12FEA800);
			img_update(w);
		}
		if (ft_strcmp(tmp[0], "\tmain_pic[1]") == 0)
		{
			if (w->main_pic[1].pix != NULL)
				free(w->main_pic[1].pix);
			w->main_pic[1] = parse_texture(w, m, tmp);
		}
		if (ft_strcmp(tmp[0], "\thud") == 0)
			w->hud = parse_texture(w, m, tmp);
	}
	ft_memreg(tmp);
}

void		load_core(t_env *w, t_map *m)
{
	int 	fd;
	char 	*line;
	char 	*path;

	line = NULL;
	path = ft_strdup("core/core.dn3d");
	if ((fd = open(path, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line))
		{
			parse_core_file(w, m, line);
			free(line);
		}
		free(line);
		close(fd);
		free(path);
	}
	else
		set_error(w, m, 5, path);
}
