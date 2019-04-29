/*BIG42HEADER*/

#include "doom.h"

void		img_update(t_env *w)
{
	//SDL_QueryTexture(w->ttf.txtr[0], NULL, NULL, &w->ttf.size[0].w, &w->ttf.size[0].h);
	SDL_UpdateTexture(w->txtr, NULL, w->pix, WIDTH * sizeof(Uint32));
	SDL_RenderCopy(w->rdr, w->txtr, NULL, NULL);
	if (w->hud == 1)
	{
		SDL_RenderCopy(w->rdr, w->ttf.txtr[0], NULL, &w->ttf.size[0]);
		SDL_RenderCopy(w->rdr, w->ttf.txtr[1], NULL, &w->ttf.size[1]);
		SDL_RenderCopy(w->rdr, w->ttf.txtr[2], NULL, &w->ttf.size[2]);
	}
	SDL_RenderPresent(w->rdr);
}

// void	initsprite(t_sprite **sprite, int count)
// {
// 	SDL_Surface *tmp;
// 	SDL_Surface *pix;

// 	*sprite = malloc(sizeof(t_sprite) * count);
// 	pix = SDL_LoadBMP("texture/barrel.bmp");
// 	tmp = SDL_ConvertSurfaceFormat(pix, SDL_PIXELFORMAT_ARGB8888, 0);
// 	sprite[0][0].pix = (Uint32 *)malloc(sizeof(Uint32) * tmp->w * tmp->h);
// 	sprite[0][0].w = tmp->w;
// 	sprite[0][0].h = tmp->h;
// 	ft_memcpy(sprite[0][0].pix, tmp->pixels, (sizeof(Uint32) * tmp->w * tmp->h));
// 	SDL_FreeSurface(pix);
// 	SDL_FreeSurface(tmp);
// 	pix = SDL_LoadBMP("texture/aim_traillette.bmp");
// 	tmp = SDL_ConvertSurfaceFormat(pix, SDL_PIXELFORMAT_ARGB8888, 0);
// 	sprite[0][1].pix = (Uint32 *)malloc(sizeof(Uint32) * tmp->w * tmp->h);
// 	sprite[0][1].w = tmp->w;
// 	sprite[0][1].h = tmp->h;
// 	ft_memcpy(sprite[0][1].pix, tmp->pixels, (sizeof(Uint32) * tmp->w * tmp->h));
// 	SDL_FreeSurface(pix);
// 	SDL_FreeSurface(tmp);
// 	pix = SDL_LoadBMP("texture/traillette.bmp");
// 	tmp = SDL_ConvertSurfaceFormat(pix, SDL_PIXELFORMAT_ARGB8888, 0);
// 	sprite[0][2].pix = (Uint32 *)malloc(sizeof(Uint32) * tmp->w * tmp->h);
// 	sprite[0][2].w = tmp->w;
// 	sprite[0][2].h = tmp->h;
// 	ft_memcpy(sprite[0][2].pix, tmp->pixels, (sizeof(Uint32) * tmp->w * tmp->h));
// 	SDL_FreeSurface(pix);
// 	SDL_FreeSurface(tmp);
// }

int			load_sounds(t_env *w, t_map *m)
{
	if (!(w->sound.musique = Mix_LoadMUS("./sounds/bensound-dreams.wav")))
	{
		printf("%s\n", Mix_GetError());
		return (-1);
	}
   	Mix_PlayMusic(w->sound.musique, -1);
	Mix_VolumeMusic(w->sound.volume);
	Mix_AllocateChannels(10);
	if (!(w->sound.jump = Mix_LoadWAV("./sounds/jump2.wav")))
		return (-1);
	if (!(m->weap[0].shoot = Mix_LoadWAV("./sounds/MP5.wav")))
		return (-1);
	if (!(w->sound.ground = Mix_LoadWAV("./sounds/ground.wav")))
		return (-1);
	if (!(m->weap[2].shoot = Mix_LoadWAV("./sounds/magnum.wav")))
		return (-1);
	if (!(m->weap[1].shoot = Mix_LoadWAV("./sounds/shotgun.wav")))
		return (-1);
	/*if (!(m->weap[3].shoot = Mix_LoadWAV("./sounds/sniper.wav")))
		return (-1);*/
	Mix_VolumeChunk(w->sound.jump, 70);
	Mix_VolumeChunk(m->weap[1].shoot, 80);
	//Mix_VolumeChunk(m->weap[3].shoot, 50);
	Mix_VolumeChunk(m->weap[0].shoot, 50);
	Mix_VolumeChunk(m->weap[2].shoot, 50);
	Mix_VolumeChunk(w->sound.ground, 70);
	return (1);
}

int			init_sdl(t_env *w)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
		return (-1);
	ttf_init(w);
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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return (-1);
	w->rdr = SDL_CreateRenderer(w->win, -1, SDL_RENDERER_ACCELERATED |
											SDL_RENDERER_PRESENTVSYNC);
	w->pix = (Uint32 *)malloc(sizeof(Uint32) * WIDTH * HEIGHT);
	w->txtr = SDL_CreateTexture(w->rdr, SDL_PIXELFORMAT_ARGB8888,
										SDL_TEXTUREACCESS_STREAMING,
										WIDTH, HEIGHT);
	w->ttf.txtr[0] = SDL_CreateTextureFromSurface(w->rdr, w->ttf.texte[0]);//proteger
	w->ttf.txtr[1] = SDL_CreateTextureFromSurface(w->rdr, w->ttf.texte[1]);
	w->ttf.txtr[2] = SDL_CreateTextureFromSurface(w->rdr, w->ttf.texte[2]);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_DISABLE);
	hello_screen(w, 0);
	img_update(w);
	SDL_Delay(1500);
	return (0);
}
