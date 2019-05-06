/**/

#include "doom.h"

t_texture			parse_texture(t_env *w, t_map *m, char **tmp)
{
	t_texture		texture;
	char			**tmp2;

	tmp2 = ft_strsplit(tmp[1], ',');
	texture.w = ft_atoi(tmp2[0]);
	texture.h = ft_atoi(tmp2[1]);
	texture.len = texture.w * texture.h;
	if (w->asciino > 35)
		process_hint_w(m->world, 1, "textures");
	else
		process_hint(1, "textures");
	if ((texture.pix = (Uint32 *)malloc(sizeof(Uint32) * texture.len)) == NULL)
		set_error(w, m, 0, ft_strdup("pixels"));
	if (w->asciino > 35)
		process_hint_w(m->world, 7, "texture");
	else
		process_hint(7, "texture");
	texture.pix = faster_please(texture.pix, tmp[2], texture.len);
	if (w->asciino > 35)
		process_hint_w(m->world, 0, " ");
	else
		process_hint(0, " ");
	ft_memreg(tmp2);
	return (texture);
}

t_texture			load_img(t_env *w, t_map *m, char *s)
{
	t_texture		texture;
	SDL_Surface		*tmp;
	SDL_Surface		*load;

	if ((load = SDL_LoadBMP(s)) == NULL)
		set_error(w, m, 5, s);
	if ((tmp = SDL_ConvertSurfaceFormat(load, SDL_PIXELFORMAT_ARGB8888, 0))
			== NULL)
		set_error(w, m, 5, s);
	SDL_FreeSurface(load);
	texture.w = tmp->w;
	texture.h = tmp->h;
	texture.pix = (Uint32 *)malloc(sizeof(Uint32) * tmp->w * tmp->h);
	ft_memcpy(texture.pix, tmp->pixels, (sizeof(Uint32) * tmp->w * tmp->h));
	SDL_FreeSurface(tmp);
	return (texture);
}
