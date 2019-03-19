#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "SDL2/SDL.h"
# include "libft.h"

# define NAME 		"Doom-Numkem3D"
# define WIDTH 		400
# define HEIGHT 	300
# define KEY 		w->event.key.keysym.sym

typedef struct		s_env
{
	SDL_Window		*win;
	SDL_Renderer	*rdr;
	Uint32			*pix;
	SDL_Texture		*txtr;
	SDL_Event		event;
}					t_env;

#endif