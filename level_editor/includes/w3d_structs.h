/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:30 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 17:02:40 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_STRUCTS_H
# define W3D_STRUCTS_H

typedef struct s_win	t_win;
typedef struct s_mthrds	t_mthrds;
typedef struct s_thrd	t_thrd;
typedef struct s_render	t_render;

struct					s_thrd
{
	int					id;
	t_win				*w;
};

struct					s_mthrds
{
	pthread_t			threads[NB_THREADS];
	t_thrd				thrd[NB_THREADS];
};

struct					s_win
{
	t_mthrds			mthrds;
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			*texture;
	SDL_Surface			*surface;
	SDL_Surface			*ceiling;

	SDL_Surface			*map_ui;
	SDL_Surface			*helptxt;

	SDL_Surface			*asset_sprite;
	SDL_Surface			*asset_tmp;
	SDL_Surface			*player_start;
	SDL_Surface			*weapon1;
	SDL_Surface			*weapon2;
	SDL_Surface			*ennemy;
	SDL_Surface			*lamp;

	SDL_Color			color_font_r;
	SDL_Rect			dst;
	SDL_Rect			dst2;
	SDL_Rect			dst3;
	SDL_Rect			dst4;
	SDL_Rect			dst5;
	SDL_Rect			dst6;
	SDL_Rect			dst7;
	SDL_Rect			dst8;
	SDL_Rect			dst9;

	SDL_Cursor			*cursor;

	Mix_Music			*theme;
	Mix_Chunk			*headshot;
	Mix_Chunk			*medic;
	TTF_Font			*police;
	Uint32				start_clock;
	Uint32				delta_clock;
	Uint32				current_fps;
	Uint8				*keystate;

	int					drawing;
	int					left_click;
	int					x0;
	int					y0;
	int					x1;
	int					y1;
	int					x2;
	int					y2;
	int					sector;
	int					mode;
	int					changemode;
	int					moving;
	struct s_lst		*lst;
	struct s_lstlst		*lstlst;
	struct s_lstlst		*triangles;
	struct s_lst		*tmp;
	struct s_lstasset	*lstasset;
	struct s_lstasset	*tmpasset;
	SDL_Event			event;
	int					h_win;
	int					w_win;
	int					link;
	int					just_close;
	int					color;
	int					overed_sector;
	int					asset;
	int					drawtriangles;
	int					place;
	int					number;
	int					index_dot;
	char				**tab;
};

#endif
