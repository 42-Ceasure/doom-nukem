/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   w3d_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:30 by abechet           #+#    #+#             */
/*   Updated: 2019/07/13 21:28:54 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef W3D_STRUCTS_H
# define W3D_STRUCTS_H

typedef struct s_win	t_win;
typedef struct s_render	t_render;

typedef struct		s_coor
{
	double			x;
	double			y;
	double			z;
}					t_coor;

typedef struct		s_texture
{
	int				w;
	int				h;
	int				len;
	Uint32			*pix;
	int				trsp;
}					t_texture;

typedef struct		s_sprite
{
	Uint32			*pix;
	char			*name;
	char			*type;
	int				sy;
	int				sx;
	int				w;
	int				h;
	int				len;
	t_coor			coor;
}					t_sprite;

typedef struct		s_dot
{
	double			x;
	double			y;
}					t_dot;

struct					s_win
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	SDL_Texture			**texture;
	t_texture			ceiling;
	t_texture			surface;

	t_texture			map_ui;
	char				*helptxt;
	char				*texturetxt;
	char				*paramtxt;
	char				*paramvaluetxt;

	t_sprite			asset_sprite;
	t_sprite			asset_tmp;
	t_texture			texture_sprite;
	t_texture			player_start;

	t_texture			inventory;
	t_texture			blackbox;
	t_texture			slot0;
	t_texture			slot1;
	t_texture			slot2;
	t_texture			slot3;
	t_texture			slot4;

	t_texture			building_hud;

	Uint32				color_font_r;
	Uint32				color_font_z;
	t_dot				dst;
	t_dot				dst2;
	t_dot				dst3;
	t_dot				dst4;
	t_dot				dst5;
	t_dot				dst6;
	t_dot				dst7;
	t_dot				dst8;
	t_dot				dst9;
	t_dot				dst10;
	t_dot				dst11;
	t_dot				dst12;
	t_dot				dst13;

	SDL_Cursor			*cursor;

	Mix_Music			*theme;
	Mix_Chunk			*headshot;
	Mix_Chunk			*medic;
	// TTF_Font			*police;
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
	int					h_win_tmp;
	int					w_win_tmp;
	int					link;
	int					just_close;
	int					color;
	int					overed_sector;
	int					asset;
	int					drawtriangles;
	int					place;
	int					number;
	int					index_dot;
	int					same_dots;
	int					tab_index;
	int					tab_malloced;
	char				**tab;
	int					triangle_sector;
	int					check_textures;
	int					texture_choice;
	int					put_texture;
	int					texture_overed_sector;
	int					texture_index;
	int					blackbox_x;
	int					txtr_input_type;
	int					param_index;
	int					hp_value;
	double				gravity_value;
	int					god_value;
	int					hud_box;
};

#endif
