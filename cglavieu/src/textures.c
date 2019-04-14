/**/

#include "doom.h"

Uint32				*load_img(Uint32 *img, char *s)
{
	SDL_Surface		*tmp;
	SDL_Surface		*load;

	load = SDL_LoadBMP(s);
	tmp = SDL_ConvertSurfaceFormat(load, SDL_PIXELFORMAT_ARGB8888, 0);
	SDL_FreeSurface(load);
	img = (Uint32 *)malloc(sizeof(Uint32) * tmp->w * tmp->h);
	ft_memcpy(img, tmp->pixels, (sizeof(Uint32) * tmp->w * tmp->h));
	SDL_FreeSurface(tmp);
	return (img);
}
