
#include "doom.h"

// test

void		replace_line(char *path, char *balise, char *content, t_env *w)
{
	t_filer f;
	int 	i;
	int		nb;

	i = 0;
	nb = 0;
	f.stop = 0; 
	f.buffer = 256;
	if ((f.fd = open("./tmp", O_RDWR | O_CREAT | O_TRUNC, 0655)) != -1
		&& (f.fd2 = open(path, O_RDONLY)) != -1)
	{
		while (precise_get_next_line(f.fd2, &f.line, f.buffer))
		{
			f.tmp = ft_strsplit(f.line, ';');
			if (w->corenbl != 0)
				nb = vmin(((double)i / (double)(w->corenbl * 2) * (double)100), 99);
			process_hint_w(w, 2, ft_itoa(nb));
			if (ft_strncmp(f.line, "buffer", 6) == 0)
			{
				ft_putendl_fd(f.line, f.fd);
				f.buffer = ft_atoi(f.tmp[1]);
				ft_memreg(f.tmp);
				free(f.line);
				continue;
			}
			else if (ft_strncmp(f.line, balise, ft_strlen(balise)) == 0)
			{
				ft_putstr_fd(balise, f.fd);
				if (ft_strlen(balise) < 8)
					ft_putstr_fd("\t\t;", f.fd);
				else
					ft_putstr_fd("\t;", f.fd);
				ft_putendl_fd(content, f.fd);
			}
			else
				ft_putendl_fd(f.line, f.fd);
			if (ft_strncmp(f.line, "texture\t\t;ascii", 15) != 0
				&& ft_strncmp(f.line, "texture\t\t;main_pic", 18) != 0
					&& ft_strncmp(f.line, "texture\t\t;texturing", 19) != 0)
				f.buffer = 256;
			ft_memreg(f.tmp);
			free(f.line);
			i++;
		}
		ft_putendl_fd("eof", f.fd);
		close(f.fd2);
		close(f.fd);
	}
	if ((f.fd = open("./tmp", O_RDONLY)) != -1
		&& (f.fd2 = open(path, O_WRONLY | O_TRUNC)) != -1)
	{
		while (precise_get_next_line(f.fd, &f.line, f.buffer) && f.stop == 0)
		{
			f.tmp = ft_strsplit(f.line, ';');
			if (w->corenbl != 0)
				nb = vmin(((double)i / (double)(w->corenbl * 2) * (double)100), 99);
			process_hint_w(w, 2, ft_itoa(nb));
			if (ft_strncmp(f.line, "buffer", 6) == 0)
			{
				ft_putendl_fd(f.line, f.fd2);
				f.buffer = ft_atoi(f.tmp[1]);
				ft_memreg(f.tmp);
				free(f.line);
				continue;
			}
			if (ft_strncmp(f.line, "eof", 3) == 0)
				f.stop = 1;
			else
				ft_putendl_fd(f.line, f.fd2);
			if (ft_strncmp(f.line, "texture\t\t;ascii", 15) != 0
				&& ft_strncmp(f.line, "texture\t\t;main_pic", 18) != 0
					&& ft_strncmp(f.line, "texture\t\t;texturing", 19) != 0)
				f.buffer = 256;
			ft_memreg(f.tmp);
			free(f.line);
			i++;
		}
		close(f.fd2);
		close(f.fd);
	}
	unlink("./tmp");
}

void		add_map_to_core(char *path, char *path2)
{
	t_filer f;
	int		fd;
	char	*line;

	f.stop = 0;
	f.buffer = 256;
	if ((f.fd = open("./tmp", O_RDWR | O_CREAT | O_TRUNC, 0655)) != -1
		&& (f.fd2 = open(path, O_RDONLY)) != -1
		&& (fd = open(path2, O_RDONLY)) != -1)
	{
		while (precise_get_next_line(f.fd2, &f.line, f.buffer))
		{
			f.tmp = ft_strsplit(f.line, ';');
			if (ft_strncmp(f.line, "buffer", 6) == 0)
			{
				ft_putendl_fd(f.line, f.fd);
				f.buffer = ft_atoi(f.tmp[1]);
				ft_memreg(f.tmp);
				free(f.line);
				continue;
			}
			else if (ft_strcmp(f.line, "ENDMAPSECTION") == 0)
			{
				while (get_next_line(fd, &line))
				{
					ft_putendl_fd(line, f.fd);
					free(line);
				}
				ft_putendl_fd("\nENDMAPSECTION", f.fd);
				free(line);
			}
			else
				ft_putendl_fd(f.line, f.fd);
			if (ft_strncmp(f.line, "texture\t\t;ascii", 15) != 0
				&& ft_strncmp(f.line, "texture\t\t;main_pic", 18) != 0
					&& ft_strncmp(f.line, "texture\t\t;texturing", 19) != 0)
				f.buffer = 256;
			ft_memreg(f.tmp);
			free(f.line);
		}
		ft_putendl_fd("eof", f.fd);
		close(f.fd2);
		close(f.fd);
		close(fd);
	}
	if ((f.fd = open("./tmp", O_RDONLY)) != -1
		&& (f.fd2 = open(path, O_WRONLY | O_TRUNC)) != -1)
	{
		while (precise_get_next_line(f.fd, &f.line, f.buffer) && f.stop == 0)
		{
			f.tmp = ft_strsplit(f.line, ';');
			if (ft_strncmp(f.line, "buffer", 6) == 0)
			{
				ft_putendl_fd(f.line, f.fd2);
				f.buffer = ft_atoi(f.tmp[1]);
				ft_memreg(f.tmp);
				free(f.line);
				continue;
			}
			if (ft_strncmp(f.line, "eof", 3) == 0)
				f.stop = 1;
			else
				ft_putendl_fd(f.line, f.fd2);
			if (ft_strncmp(f.line, "texture\t\t;ascii", 15) != 0
				&& ft_strncmp(f.line, "texture\t\t;main_pic", 18) != 0
					&& ft_strncmp(f.line, "texture\t\t;texturing", 19) != 0)
				f.buffer = 256;
			ft_memreg(f.tmp);
			free(f.line);
		}
		close(f.fd2);
		close(f.fd);
	}
	unlink("./tmp");
}

void		change_settings(t_env *w, t_map *m)
{
	char	*nb;
	char	*tmp;
	char	*str;

	nb = ft_itoa(w->window_mode);
	str = ft_strjoin(nb, ":");
	free(nb);
	nb = ft_itoa(w->window_res);
	tmp = ft_strjoin(str, nb);
	free(nb);
	free(str);
	nb = ft_itoa(m->player.field_of_vision_h); /* double */
	str = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(str, nb);
	free(nb);
	free(str);
	nb = ft_itoa(m->player.field_of_vision_v); /* double */
	str = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(str, nb);
	free(nb);
	free(str);
	nb = ft_itoa(m->player.mousesp); /* double */
	str = ft_strjoin(tmp, ":");
	free(tmp);
	tmp = ft_strjoin(str, nb);
	replace_line("./core/core.dn3d", "settings", tmp, w);
}
