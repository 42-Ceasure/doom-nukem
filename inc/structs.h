/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:30 by abechet           #+#    #+#             */
/*   Updated: 2019/07/23 11:11:10 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_win	t_win;
typedef struct s_render	t_render;

typedef struct		s_ceiling
{
	double			side;
	double			rot_x;
	double			rot_y;
	double			map_x;
	double			map_y;
	int				x;
	unsigned		x_tex;
	unsigned		y_tex;
	unsigned		tmpix;
}					t_ceiling;

typedef struct		s_scalling
{
	double 			step_x_tex;
	double 			step_y_tex;
	double			x_tex;
	double			y_tex;
	int 			maxx;
	int				maxy;
	int 			x_tmp;
	int 			x_tex_tmp;
	int				text_w;
	int				text_h;
	unsigned int	tmpix;
}					t_scalling;

typedef struct		s_draw
{
	double			wall_height_from_bottom;
	double 			wall_height_scale;
	double 			wall_width_scale;
	double			y_tex_start;
	double			y_tex_pos;
	int				x;
	int				y1;
	int				y2;
	int 			x_tex;
	int				y_tex;
	int 			color;
}					t_draw;

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

typedef struct		s_point
{
	t_dot			p0;
	t_dot			p1;
	t_dot			p2;
}					t_point;

typedef struct		s_count
{
	int				i;
	int				j;
	int				n;
	int				x;
	int				j0;
	int				j1;
	int				j2;
}					t_count;

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
	t_sprite			player_start;

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
	int					neighbour_index;
	int					norme_sector;
};

typedef struct		s_lst
{
	int				x;
	int				y;
	int				sector;
	int				nb;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_lstlst
{
	int				sector;
	int				closed;
	int				sector_nb;
	int				clockwise;
	int				txtr_wall;
	int				txtr_ceiling;
	int				txtr_floor;
	int				txtr_lower_extrude;
	int				txtr_higher_extrude;
	struct s_lst	*head;
	struct s_lstlst	*next;
}					t_lstlst;

typedef struct		s_lstasset
{
	int				x;
	int				y;
	int				sector;
	int				asset_type;
	struct s_lstasset	*next;
}					t_lstasset;

typedef struct		s_filer
{
	int				buffer;
	int				stop;
	int				fd;
	int				fd2;
	char			*buff;
	char			*line;
	char			**tmp;
}					t_filer;

typedef struct		s_vect
{
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	int				dx;
	int				dy;
}					t_vect;

typedef struct		s_color
{
	Uint32			top;
	Uint32			middle;
	Uint32			bottom;
	int				y;
	int				stop;
	int				start;
	Uint8			c_a1;
	Uint8			c_r1;
	Uint8			c_g1;
	Uint8			c_b1;
	Uint8			c_a2;
	Uint8			c_r2;
	Uint8			c_g2;
	Uint8			c_b2;
}					t_color;

typedef struct		s_item
{
	int				sectorno;
	int				sx1;
	int				sx2;
}					t_item;

typedef struct		s_reader
{
	t_item			queue[MRS];
	t_item			*head;
	t_item			*tail;
	t_item			now;
}					t_reader;

typedef struct		s_sector
{
	int				wall_count;
	double			floor;
	double			ceiling;
	t_dot			*dot;
	int				*network;
	int				texturing[6];
}					t_sector;

typedef struct		s_player
{
	int				bal;
	char			*fps;
	char			*stractu_ammo;
	int				intactu_ammo;
	int				bullet[2];
	char			*strbullet;
	int				handed;
	int				aiming;
	int				shooting;
	int				firing;
	int				refresh;
	int				switching;
	int				recoil;
	int				sector;
	int				mousesp;
	int				hud;
	int				hp;
	int				minimap;
	int				max_hp;
	int				take[4];
	char			*strhp;
	t_coor			coor;
	int				memz;
	double			movespeed;
	t_coor			move_speed;
	t_coor			move_speedless;
	double			angle;
	double			anglesin;
	double			anglecos;
	double			yaw;
	double			field_of_vision_h;
	double			field_of_vision_v;
	double			stance;
	int				jump;
	int				fall;
	int				ground;
	int				moving;
	double			height;
	double			hole_low;
	double			hole_high;
	int				press;
	double			accel;
	int				display;
}					t_player;

typedef struct		s_intersect
{
	int				mem;
	double			dx;
	double			dy;
	double			x1;
	double			x2;
	double			x3;
	double			x4;
	double			y1;
	double			y2;
	double			y3;
	double			y4;
	double			xd;
	double			yd;
}					t_intersect;

typedef struct		s_work
{
	int				winwidth;
	int				winheight;
	t_color			color;
	t_color			color2;
	t_intersect		i1;
	t_intersect		i2;
	t_coor			v1;
	t_coor			v2;
	t_coor			t1;
	t_coor			t2;
	t_coor			tt1;
	t_coor			tt2;
	t_coor			ip1;
	t_coor			ip2;
	t_coor			lol1;
	t_coor			lol2;
	t_coor			lel1;
	t_coor			lel2;
	t_coor			lul1;
	t_coor			lul2;
	t_coor			p1;
	t_coor			p2;
	double			p1yb;
	double			p2yb;
	double			pcos;
	double			psin;
	double			nearz;
	double			farz;
	double			nearside;
	double			farside;
	double			xscale1;
	double			yscale1;
	double			xscale2;
	double			yscale2;
	double			yceil;
	double			yfloor;
	double			x1;
	double			x2;
	double			y1a;
	double			y1b;
	double			y2a;
	double			y2b;
	int				ya;
	int				yb;
	int				cya;
	int				cyb;
	double			nyceil;
	double			nyfloor;
	int				network;
	double			ny1a;
	double			ny1b;
	double			ny2a;
	double			ny2b;
	int				nya;
	int				nyb;
	int				cnya;
	int				cnyb;
	double			startx;
	double			endx;
	int				z;
	int				ytop[3840];
	int				ybot[2160];
	unsigned int	r;
	unsigned int	r1;
	unsigned int	r2;
	double			sx1;
	double			sx2;
	double			height;
	int				point;
	double			start_x_tex;
	double			end_x_tex;
	double			wall_width;
	int				nosector;
	int				starty;
	int				stopy;
}					t_work;

typedef	struct		s_ennemy
{
	double			height;
	int				fall;
	int				nb_ammo;
	int				ground;
	int				sector;
	int				moving;
	int				count;
	int				cpt;
	int				die;
	int				is_dead;
	int				dead;
	int				touche;
	int				index;
	int				vis;
	double			range;
	double			hole_low;
	double			hole_high;
	double			movespeed;
	t_coor			coor;
	t_coor			move_speed;
	t_coor			move_speedless;
}					t_ennemy;

typedef struct		s_calc_sprite
{
	double			v1x;
	double			v1y;
	double			t1x;
	double			t1z;
	double			diffx;
	double			diffy;
	double			xscale1;
	double			x1;
	double			y1a;
	double			yscale1;
	double			zoom;
	double			ratio;
}					t_cal_sprt;

typedef struct		s_map_sprite
{
	char			*name;
	int				sx;
	int				sy;
	int				sector;
	int				index;
	int				vis;
	int				taken;
	double			range;
}					t_map_sprite;

typedef struct		s_weapon
{
	char			*name;
	int				range;
	int				firerate;
	int				accuracy;
	double			dispertion;
	int				ammo_type;
	int				actu_ammo;
	int				magazine;
	int				reloadtime;
	int				recoil;
	t_sprite		sprt[5];
	Mix_Chunk 		*shoot;
}					t_weapon;

typedef struct		s_map
{
	void			*world;
	int				stop;
	int				game_over;
	int				god_mod;
	int				launchwmap;
	int				newgame;
	int				trippymod;
	int				elevator;
	int				door;
	int				nb_a;
	int				i;
	int				w;
	int				fd;
	int				fd2;
	int				asc;
	int				section_number;
	int				dotsc;
	int				dots_count;
	int				s;
	int				sector_count;
	int				weapon_count;
	int				sprite_count;
	int				texture_count;
	int				spmc;
	int				sprite_map_count;
	int				ennemyc;
	int				ennemy_count;
	int				maxrenderedsector;
	int				endsector;
	int				change_lvl;
	char			*linklvl;
	double			yaw;
	double			gravity;
	double			**tab;
	char			*line;
	char			*map_name;
	char			*map_path;
	t_dot			*dot;
	t_sector		*sector;
	t_weapon		*weap;
	t_sprite		*sprite;
	t_map_sprite	*sprt;
	t_texture		hud;
	t_texture		hud2;
	t_texture		whitebox;
	t_texture		fire;
	t_player		player;
	t_ennemy		*ennemy;
}					t_map;

typedef struct		s_menu
{
	int				i;
	int				j;
	int				z;
	int				k;
	int				*y;
	char			***list;
}					t_menu;

typedef struct		s_sound
{
	int				volume;
	Mix_Music		*musique;
	Mix_Chunk 		*jump;
	Mix_Chunk 		*ground;
	Mix_Chunk		*reload;
	Mix_Chunk		*clic;
	Mix_Chunk		*dammage;
}					t_sound;

typedef struct		s_img
{
	int				x;
	int				y;
	int				w;
	int				h;
}					t_img;

typedef struct		s_res
{
	int				width;
	int				height;
}					t_res;

typedef struct		s_text
{
	int				x;
	int				y;
	char			*text;
	Uint32			color;
}					t_text;

typedef	struct		s_dtime
{
	int				fps;
	Uint32			start;
	Uint32			end;
	Uint32			ctime;		/* current time */
	Uint32			otime;		/* old time */
	Uint32			etime;		/* elapsed time (from start of program) */
	Uint32			shootime;	/* time between each shot of a given weapon */
	Uint32			stime;		/* second ticker */
	Uint32			walk;		/* time of walk animation */
	Uint32			dead;		/* time of dead animation */
	Uint32			start_lvl;	/* start_lvl time */
	Uint32			end_lvl;	/* end_lvl time */
}					t_dtime;

typedef struct		s_env
{
	t_map			*m;
	char			*light_nb;
	double			loading_time;
	int				i;
	int				ac;
	int				sens;
	int				asciichk;
	int				asciino;
	int				stopread;
	int				invert;
	double			random;
	t_res			res;
	t_res			game_res;
	t_res			editor_res;
	int				window_mode;
	int				window_res;
	int				sequential_draw;
	int				sequential_frame;
	SDL_Window		*win;
	SDL_Renderer	*rdr;
	t_sound			sound;
	Uint32			*pix;
	const Uint8		*inkeys;
	SDL_Texture		*txtr;
	SDL_Event		event;
	t_texture		*ascii;
	t_texture		main_pic[3];
	t_text			txt;
	t_menu			menu;
	t_dot			txthead;
	t_dot			txtnxtline;
	t_dot			txtnxtto;
	t_dtime			dtime;
	t_texture		*texturing;
	int				texturingno;
	int				nbmaps;
	char			**namesmaps;
	char			*currmap;
	int				window_mode_menu;
	int				window_res_menu;
	int				fov_h_menu;
	int				fov_v_menu;
	int				mousesp_menu;
	int				corenbl;
	double			mem_field_of_vision_h;
	double			mem_field_of_vision_v;
}					t_env;


typedef struct		s_worker_arg
{
	t_env			*w;
	int				start;
	t_work			work;
	int				*ybot;
	int				*ytop;
}					t_worker_arg;

#endif