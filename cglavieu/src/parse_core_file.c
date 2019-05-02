/*BIG42HEADER*/

#include "doom.h"

void		parse_core_file(t_env *w, t_map *m, char *line)
{
	char	**tmp;
	t_dot	dot;

	dot.x = 600;
	dot.y = 550;
	tmp = ft_strsplit(line, ':');
	if (tmp[0] != NULL)
	{
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
			type_text(w, dot, "loading game...", 0x12FEA800);
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