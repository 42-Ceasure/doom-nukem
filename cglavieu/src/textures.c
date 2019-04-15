/**/

#include "doom.h"

t_texture			load_img(t_env *w, t_map *m, char *s)
{
	t_texture		texture;
	SDL_Surface		*tmp;
	SDL_Surface		*load;

	if ((load = SDL_LoadBMP(s)) == NULL)
		set_error(w, m, 5, s);
	if ((tmp = SDL_ConvertSurfaceFormat(load, SDL_PIXELFORMAT_ARGB8888, 0)) == NULL)
		set_error(w, m, 5, s);
	SDL_FreeSurface(load);
	texture.w = tmp->w;
	texture.h = tmp->h;
	texture.pix = (Uint32 *)malloc(sizeof(Uint32) * tmp->w * tmp->h);
	ft_memcpy(texture.pix, tmp->pixels, (sizeof(Uint32) * tmp->w * tmp->h));
	SDL_FreeSurface(tmp);
	return (texture);
}
