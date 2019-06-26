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

/*struct					s_render
{
	Uint32				color;
	Uint32				color_h;
	Uint32				color_v;
	int					x;
	int					draw_start;
	int					draw_end;
	int					line_height;
	int					hit;
	int					side;
	int					floor_tex_x;
	int					floor_tex_y;
	double				ray_angle;
	double				ray_angle_rad;
	double				alph_angle_rad;
	double				alph_angle;
	double				player_x;
	double				player_y;
	double				hor_x;
	double				hor_y;
	double				ver_x;
	double				ver_y;
	double				final_x;
	double				final_y;
	double				step_x;
	double				step_y;
	double				dist_ver;
	double				dist_wall;
	double				dist_hor;
	double				dist;
	double				current_dist;
	double				dist_player;
	double				dist_floor;
	double				wall_height;
	double				floor_x_wall;
	double				floor_y_wall;
	double				current_floor_x;
	double				current_floor_y;
};*/

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
	char				**tab;
};

#endif
