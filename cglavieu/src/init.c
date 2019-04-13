/*BIG42HEADER*/

#include "doom.h"

void		img_update(t_env *w)
{
	SDL_UpdateTexture(w->txtr, NULL, w->pix, WIDTH * sizeof(Uint32));
	SDL_RenderCopy(w->rdr, w->txtr, NULL, NULL);
	SDL_RenderPresent(w->rdr);
}

SDL_Texture* loadTexture(const char path[], SDL_Renderer *renderer)
{
    SDL_Texture *texture = NULL;
    SDL_Surface *tmp = NULL;
    tmp = SDL_LoadBMP(path);
    if(NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s\n", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);
    SDL_FreeSurface(tmp);
    if(NULL == texture)
    {
        printf("Erreur SDL_CreateTextureFromSurface\n");
        return NULL;
    }
    return (texture);
}

int			init_sdl(t_env *w)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (-1);
	if (w->window_mode == 1)
	{
		w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIDTH, HEIGHT,
										SDL_WINDOW_RESIZABLE);
	}
	else if (w->window_mode == 0)
	{
		w->win = SDL_CreateWindow(NAME, SDL_WINDOWPOS_CENTERED,
										SDL_WINDOWPOS_CENTERED,
										WIDTH, HEIGHT,
										SDL_WINDOW_FULLSCREEN);
	}
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048 ) == -1)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		return (-1);
	}
	if ((w->musique = Mix_LoadMUS("sounds/musique.wav")) == NULL)
	{
		printf("%s\n", Mix_GetError());
		return (-1);
	}
   	Mix_PlayMusic(w->musique, -1); //-1 = jouer en boucle
	/*Mix_AllocateChannels(10);//cree 10 channels max
	Mix_Chunk *son;
	son = Mix_LoadWAV("son.wav");
	Mix_VolumeChunk(son, 128 / 2);
	Mix_PlayChannel(1, son, 0);// 1er arg est le numero du cannal et 3e arg est le nombre de fois repete
	Mix_FreeChunk(son);*/
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIDTH, HEIGHT);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);
	return (0);
}
