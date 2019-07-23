/*BIG42HEADER*/

#include "doom.h"

t_texture			parse_texture(t_env *w, t_map *m, char **tmp)
{
	t_texture		texture;
	char			**tmp2;

	tmp2 = ft_strsplit(tmp[1], ',');
	texture.w = ft_atoi(tmp2[0]);
	texture.h = ft_atoi(tmp2[1]);
	texture.len = texture.w * texture.h;
	if ((texture.pix = (Uint32 *)malloc(sizeof(Uint32) * texture.len)) == NULL)
		set_error(w, m, 0, ft_strdup("pixels"));
	texture.pix = faster_please(texture.pix, tmp[2], texture.len);
	if (tmp2[2] != NULL)
		texture.trsp = ft_atoi(tmp2[2]);
	else
		texture.trsp = 0;
	ft_memreg(tmp2);
	return (texture);
}

void				parse_texture_next(t_env *w, t_map *m, char **tmp)
{
	if (ft_strcmp(tmp[0], "main_pic[1]") == 0)
		w->main_pic[1] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "main_pic[2]") == 0)
		w->main_pic[2] = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud") == 0)
		m->hud = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "hud2") == 0)
		m->hud2 = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "fire") == 0)
		m->fire = parse_texture(w, m, tmp);
	if (ft_strcmp(tmp[0], "blackbox") == 0)
		m->whitebox = parse_texture(w, m, tmp);
}

void				parse_texture_line(t_env *w, t_map *m, char *line)
{
	char			**tmp;

	w->txthead.x = 800;
	w->txthead.y = 550;
	if ((tmp = ft_strsplit(line, ':')) == NULL)
		ft_putendl("ERREUR SPLIT");
	if (ft_strcmp(tmp[0], "ascii") == 0)
	{
		w->ascii[w->asciichk] = parse_texture(w, m, tmp);
		w->asciichk++;
	}
	if (ft_strcmp(tmp[0], "texturing") == 0)
	{
		w->texturing[w->texturingno] = parse_texture(w, m, tmp);
		w->texturingno++;
	}
	if (ft_strcmp(tmp[0], "main_pic[0]") == 0)
	{
		w->main_pic[0] = parse_texture(w, m, tmp);
		main_pic(w, 0);
		type_str(w, w->txthead, "loading game...", 0x12FEA800);
		img_update(w);
	}
	parse_texture_next(w, m, tmp);
	ft_memreg(tmp);
}
