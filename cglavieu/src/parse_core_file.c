/*BIG42HEADER*/

#include "doom.h"

char		***parse_menu_line(t_env *w, char **tmp)
{
	char	**tmp2;
	char	***menu;
	int		i;
	int		menuc;
	int		entryc;

	i = 0;
	w->i = 0;
	menuc = 0;
	while (tmp[menuc + 1])
		menuc++;
	menu = (char ***)malloc(sizeof(char **) * (menuc + 1));
	menu[menuc] = NULL;
	while (i < menuc)
	{
		entryc = 1;
		tmp2 = ft_strsplit(tmp[i + 1], ',');
		while (tmp2[entryc] != NULL)
			entryc++;
		menu[i] = (char **)malloc(sizeof(char *) * (entryc + 1));
		menu[i][entryc] = NULL;
		entryc--;
		while (entryc >= 0)
		{
			menu[i][entryc] = ft_strdup(tmp2[entryc]);
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
	t_dot	dot;

	dot.x = 800;
	dot.y = 550;
	tmp = ft_strsplit(line, ':');
	if (tmp[0] != NULL)
	{
		if (ft_strcmp(tmp[0], "\tmenu") == 0)
			w->menu.list = parse_menu_line(w, tmp);
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
			type_str(w, dot, "loading game...", 0x12FEA800);
			img_update(w);
		}
		if (ft_strcmp(tmp[0], "\tmain_pic[1]") == 0)
		{
			if (w->main_pic[1].pix != NULL)
				free(w->main_pic[1].pix);
			w->main_pic[1] = parse_texture(w, m, tmp);
		}
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