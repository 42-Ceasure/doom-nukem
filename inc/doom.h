/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:26:17 by agay              #+#    #+#             */
/*   Updated: 2019/07/17 11:21:24 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include "w3d_defines.h"
# include "w3d_structs.h"
# include <pthread.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

# define NAME 				"Doom-Numkem3D"
# define BASEWIDTH 			1024
# define BASEHEIGHT 		576
# define RESIZABLE_SCREEN	1
# define FULL_SCREEN		0
# define WIDTH 				w->res.width
# define HEIGHT 			w->res.height
# define KEY 				w->event.key.keysym.sym
# define BUTTON				w->event.button.button
# define WINDOW				w->event.window.event
# define MRS				32
# define PL_X				m->player.coor.x
# define PL_MSX				m->player.move_speed.x
# define PL_Y				m->player.coor.y
# define PL_MSY				m->player.move_speed.y
# define PL_A				m->player.angle
# define PL_AC				m->player.anglecos
# define PL_AS				m->player.anglesin
# define PH					m->player.handed
# define M_S_C				m->sector_count
# define STAND				16.9
# define CROUCH				9.3
# define CRAWL				2
# define HEADMARGIN			1.1
# define KNEEH				7.9
# define BASE_GRAVITY		0.05
# define NB_THREAD			4
# define TEXT_WALL_HEIGHT	10
# define TEXT_WALL_WIDTH	10
# define PI					3.14159
# define ASCIINB			67
# define WIN_X				720
# define WIN_Y				720
# define GAME				0
# define EDIT				1
# define PAKOMSA			"Your core file seem invalid. You may need to reinstall the game"

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

// typedef struct		s_dot
// {
// 	double			x;
// 	double			y;
// }					t_dot;

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
	Mix_Chunk		*dammage;
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
	int				ratio;
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

// typedef struct		s_texture
// {
// 	int				w;
// 	int				h;
// 	int				len;
// 	Uint32			*pix;
// 	int				trsp;
// }					t_texture;

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
	int				nb_a;
	int				i;
	int				s;
	int				w;
	int				fd;
	int				fd2;
	int				asc;
	int				section_number;
	int				dots_count;
	int				sector_count;
	int				weapon_count;
	int				sprite_count;
	int				texture_count;
	int				sprite_map_count;
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
	t_sprite		*sprite;	//a placer dans t_env
	t_map_sprite	*sprt;
	t_texture		hud;
	t_texture		hud2;
	t_texture		whitebox;
	t_texture		fire;
	t_player		player;
	t_ennemy		*ennemy;
}					t_map;

// typedef struct		s_entry
// {
// 	int				type;
// 	char			*champ;
// 	int				val;
// 	t_menu			menu;
// }					t_entry;

// typedef struct		s_menu
// {
// 	int				id;
// 	t_menu			*menu;
// 	t_entry			*entry;
// }					t_menu;

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

void				interpret_cmd(t_env *w, t_map *m, char ***cmd, char **av);
char				***parse_cmd(int ac, char **av);
t_texture			pre_init_texture(int w, int h);
void				l_f_priority_cmd(t_env *w, t_map *m, char ***cmd);
void				map_cmd(t_env *w, t_map *m, char **cmd);
void				not_a_command(t_env *w, t_map *m, char ***cmd, char *s);
void				exit_cmd(t_env *w, t_map *m, char ***cmd);
void				video_mode_cmd(t_env *w, t_map *m, char ***cmd, int i);
void				seq_cmd(t_env *w, char ***cmd, int i);
void				set_error(t_env *w, t_map *m, int errorno, char *s);
void				set_basics(t_env *w, t_map *m, int ac);
void				parse_config_line(t_env *w, t_map *m, char *line);
void				parse_allocating_line(t_env *w, t_map *m, char *line);
t_menu				parse_menu_line(t_env *w, char *line);
void				parse_weapon_line(t_map *m, char *line);
int					parse_weapon_sprite(t_map *m, char *name, char *def, char *pix);
void				parse_texture_line(t_env *w, t_map *m, char *line);
void				parse_sprite_line(t_env *w, t_map *m, char *line);
// void 				replace_line(char *path, char *balise, char *content);
// test
void				replace_line(char *path, char *balise, char *content, t_env *w);
void				add_map_to_core(char *path, char *path2, t_env *w);
void				change_settings(t_env *w, t_map *m);
void				parse_map_file(t_env *w, t_map *m);
int					parse_map_section(t_map *m, char **tab);
int					parse_player_section(t_map *m, char **tab);
int					parse_weapon_section(t_map *m, char **tab);
int					parse_sprite_section(t_map *m, char *name, char *def, char *pix);
void				parse_core_section(t_env *w, t_map *m, char *line, int mode);
int					quick_look(t_env *w, t_map *m);
int					do_parse(t_env *w, t_map *m);
void				set_advanced_run(char **av, t_env *w, t_map *m);
void				exit_game(t_env *w, t_map *m, int i);
int					init_sdl(t_env *w);
void				img_update(t_env *w);
void				clean_render(t_env *w, Uint32 color);
void				run(t_env *w, t_map *m);
void				draw(t_env *w, t_map *m);
void				draw_mini_map(t_env *w, t_map *m);
Uint32				color(Uint32 color1);
void				vect_ab(t_coor p1, t_coor p2, t_env *w, Uint32 color);
void				set_txtr_pix(t_env *w, int x, int y, Uint32 color);
double				vect_cross_prod(double x0, double y0, double x1, double y1);
double				sign(double a);
double				vabs(double a);
double				vmin(double a, double b);
double				vmax(double a, double b);
double				vmid(double a, double min, double max);
double				v_c_p(double x0, double y0, double x1, double y1);
double				intersectbox(t_intersect i);
t_coor				intersect(t_intersect i);
double				isoverlap(double a0, double a1, double b0, double b1);
double				pointside(t_coor p, double x0,
					double y0, double x1, double y1);
double				yaw(double y, double z, t_map *m);
void				init_verification(t_work *draw);
int					init_draw(t_env *w, t_work *d, t_reader *read, t_map *m);
void				moving_head(t_work *w, t_reader read, t_map *m);
int					ceiling_and_floor(t_work *d, t_map *m,
					t_reader read, int point);
int					check_invisible(t_work *d, t_reader read, t_map *m);
void				recap_parsing(t_env *w, t_map *m, char **str);
void				recap_map_list_sector(t_env *w, t_map *m, char **str);
void				recap_map_list_sectors(t_map m, char *str);
void				recap_sector_general(t_map m, int i);
void				recap_sector_dots(t_map m, int i);
void				recap_sector_network(t_map m, int i);
void				recap_sector(t_map m, int i);
int					calcul_render_mthrd(t_env *w, t_work work, int *ybot, int *ytop);
void				calcul_render_no_mthrd(t_env *w, t_work *work);
void				key_events(t_env *w, t_map *m);
void				keydown_events(t_env *w, t_map *m);
void				keyup_events(t_env *w, t_map *m);
void				motion_events(t_env *w, t_map *m);
void				move_player(double dx, double dy, t_map *m);
void				get_height(t_map *m);
void				is_falling(t_map *m);
void				is_fall(t_map *m, int x);
void				slow_down(t_env *w, t_map *m);
void				is_moving(t_map *m);
void				move_all_ennemy(t_map *m);
void				walk_up_stairs(t_map *m, t_intersect i, int x, int s);
void				main_menu(t_env *w, t_map *m);
t_texture			load_img(t_env *w, t_map *m, char *s);
void				initsprite(t_sprite **sprite, int count);
void				hand(t_env *w, t_map *m);
void				buttondown_event(t_env *w, t_map *m);
void				buttonup_event(t_env *w, t_map *m);
// void				hello_screen(t_env *w);
void				main_pic(t_env *w, int nb);
int					load_sounds(t_env *w, t_map *m);
void				process_hint(int i, char *s);
void				process_hint_w(t_env *w, int i, char *s);
void				print_load(char *s, int i3, int len);
void				set_config(t_env *w, t_map *m);
void				set_w(t_env *w, int ac);
void				set_m(t_map *m);
void				set_m_player(t_map *m);
void				load_core(t_env *w, t_map *m);
t_texture			parse_texture(t_env *w, t_map *m, char **tmp);
Uint32				*faster_please(Uint32 *dst, char *src, int len);
void				type_str(t_env *w, t_dot dot, char *s, Uint32 color);
void				go_forward(t_map *m);
void				go_back(t_map *m);
void				go_left(t_map *m);
void				go_right(t_map *m);
void				look_left(t_map *m);
void				look_right(t_map *m);
void				jump(t_env *w, t_map *m);
void				sprint(t_map *m);
void				hud(t_map *m);
void				minimap(t_map *m);
void				ft_hud(t_env *w, t_map *m);
void				game_img(t_env *w, t_map *m);
void				ramassage(t_map *m);
void				pause_music(void);
void				volume_more(t_env *w);
void				volume_less(t_env *w);
void				crouch(t_map *m);
void				crawl_lock(t_map *m);
void				crouch_lock(t_map *m);
void				switch_weapon(t_map *m, int i);
void				look_around(t_env *w, t_map *m);
void				set_shoot(t_map *m, int i);
void				shoot(t_env *w, t_map *m);
void				stop_aim(t_env *w, t_map *m);
void				aim(t_env *w, t_map *m);
void				reload_weapon(t_env *w, t_map *m);
void				launch(t_env *w, t_map *m);
void				sequential_frame(t_env *w, t_map *m);
void				safe_texture_to_screen(t_env *w, t_texture texture, int x, int y);
void				safe_sprite_to_screen(t_env *w, t_sprite sprite, int x, int y);
void				safe_char_to_screen(t_env *w, t_texture texture, int x, int y);
int					img_to_screen(t_env *w, t_texture texture, t_img img);
int					final_sprite_to_screen(t_env *w, t_sprite sprite, int x, int y, int width, int height);
int					final_texture_to_screen(t_env *w, t_texture texture, int x, int y, int width, int height);
int					final_char_to_screen(t_env *w, t_texture texture, int x, int y, int width, int height);
t_img				fill_t_img(int x, int y, int w, int h);
void				get_that_time(t_env *w);
void				draw_sprite(t_env *w, t_map *m, int x, int ratio);
void				count_sprite(t_env *w, t_map *m);
void				test_sprite(t_map *m, double xx, double yy);
void				clear_sprite(t_map *m);
int					rotate(t_cal_sprt data, int o);
void				draw_ennemy(t_env *w, t_map *m, int x, int ratio);
void				jet_pack(t_map *m);
// int					get_tmpix_scaled(t_sprite sprite, int width, int height, int x, int y);
int					get_tmpix_scaled(t_sprite sprite, t_img img);
void				skybox(int x, t_env *w, t_work *work, t_texture text);
double				pythagore(double a, double b);
void				ennemy_animation(t_env *w, t_map *m, double **tab, int x);
double				**fill_tab_ennemy(t_map *m);
double				**fill_tab_sprite(t_map *m);
double				**sort_double_tab(double **tab, int size);
void				draw_vertical_line_t(int x, t_env *w, t_work *work, t_texture text);
void				draw_ceiling_line_t(int x, t_env *w, t_work *work, t_texture text);
void				draw_extruded_line_t(int x, t_env *w, t_work *work, t_texture text);
void				draw_wall_line_t(int x, t_env *w, t_work *work, t_texture text);
void				ft_free_weap(t_map *m);
void				ft_free_sprite(t_map *m);
void				ft_free_sprt(t_map *m);
void				ft_free_sector(t_map *m);
int					get_that_map_parsed(t_env *w, t_map *m);
int					parse_map_in_core(t_env *w, t_map *m, char *name);
int					parse_line(t_env *w, t_map *m);
void				reset_player(t_map *m);
int					parse_ennemy_map(t_map *m, char **tab);
int					parse_sprite_map(t_map *m, char **tab);
void				fit_to_editor(t_env *w);
void				fit_to_game(t_env *w);
int					level_editor_start(t_env *w);
char		**map(t_win *win);
void		draw_grid(t_env *w, t_win *win);
int			clear_n_exit(t_win *win, int error);
void		loop_play(t_env *w, t_win *win);
void		sdl_event(t_env *w, t_win *win);
t_lst		*lstnew(int x, int y, int sector);
t_lstlst	*lstlstnew(t_win *win);
t_lstasset	*lstassetnew(t_win *win, int sector);
int			check_list(t_win *win, t_lst *lst, int x, int y);
void		ft_draw_line(t_win *win, int x1, int y1, int x2, int y2);
void		put_pixel_to_surface(SDL_Surface *srfc, int x, int y, Uint32 color);
void		print_line(t_win *win, int x1, int y1, int x2, int y2);
void 		line(t_env *w, t_win *win, int x0, int y0, int x1, int y1);
void		undo(t_win *win);
void		delete_sector(t_win *win);
int			check_neighbour(t_win *win);
int			point_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m);
int			len_list(t_lst *lst);
t_lstlst	*recursive_triangulate(t_win *win, t_lstlst *tmp2, t_lst *polygone, t_lstlst *triangles);
void		placing(t_win *win);
void		pick_asset(t_env *, t_win *win);
void		mode(t_env *w, t_win *win);
int			len_listlist(t_lstlst *lstlst);
void		asset_overing(t_env *w, t_win *win);
void		texture_overing(t_win *win);
void		delete_asset(t_win *win);
void		overing(t_win *win);
void		save_map(t_win *win);
void		map_save(t_win *win, t_env *w);



void		check4(t_win *win);
int			triangles_neighbours(t_win *win, t_lstlst *tmp2, int i);
void		sort_triangles_points(t_win *win);
void		triangulate_all_assets(t_win *win);
int			triangulate_a_triangle(t_win *win, t_dot m);
int			correct_map(t_win *win);
void		fill_buffer(t_win *win, t_env *w);
int			sector_minimum_needed_point(t_win *win);
int			triangulate_player_start(t_win *win, int x, int y);
int			sector_intersect_with_itself(t_dot p1, t_dot p2, t_dot p3, t_dot p4);
int			check_player_start(t_win *win);
int			correct_intersections_in_a_sector(t_win *win);
void		write_ennemy(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_sprites(t_win *win, int fp);
void		write_ennemies(t_win *win, int fp);
void		write_shotgun_ammo(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_m4(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_m4_ammo(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_m9(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_shotgun(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_undertale(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_player(t_win *win, int fp);
void		write_sectors(t_win *win, int fp);
void		write_dots(t_win *win, int fp);
void		first_line2(t_win *win, int fp);
void		write_health(t_win *win, int fp, t_lstasset *tmp, int i);
void		write_in_file(t_win *win, t_env *w);

int			y_min_point(t_win *win);
int			next_y(t_win *win, int y);
int			*create_y_dot_tab(t_win *win, int y, int i);
int			*dot_tab_sector(t_win *win, int sector);
int			*tab_sector3(t_win *win, int sector);
int			number_of_dot_per_line_with_same(t_win *win, int y);
int			total_exclusive_points(t_win *win);
int			number_of_dot_per_line(t_win *win, int y);
int			number_of_ennemy(t_win *win);
int			number_of_sprite(t_win *win);
int			number_of_y(t_win *win);
int			x_min_on_line(t_win *win, int y);
int			next_x_on_line(t_win *win, int y, int x);
void		sort_points(t_win *win);
int			correct_three_points(t_win *win);

int			sector_inside_sector(t_win *win);
void		everything_is_a_triangle(t_win *win);







void		img_edit_update(t_env *w);
void		clean_edit_render(t_env *w, Uint32 color);
void		sectors_in_tab(t_win *win);
void		sectors_in_tab2(t_win *win);
void		clear_window(t_win *win);
void		recursive_check(t_win *win);
void		sort_int_tab(int *tab, int size);
void		free_triangles(t_win *win);
int			int_len(int nb);
//int			which_sector_neighbour(t_win *win, int x1, int y1, int x2, int y2, int sector);
t_dot		get_point_in_list(t_lst *polygone, int index);
void		texture_mode(t_env *w, t_win *win);
void		change_texture_index(t_env *w, t_win *win);
int			intersectbox2(t_dot p1, t_dot p2, t_dot p3, t_dot p4);
void		set_params(t_env *w, t_win *win);
void		increase_value(t_win *win);
void		decrease_value(t_win *win);

void		test(t_win *win);
//void		check2(t_win *win);
int			init2(t_env *w, t_win *win);
double		pointside2(t_dot m, double x0, double y0, double x1, double y1);
int			get_nb_maps_in_core(t_env *w);
int			get_names_maps_in_core(t_env *w, char **names);
void		init_sprite_tab(t_map *m);
void		ft_free_tab(t_map *m);
void		process_hint_savemap(t_env *w, int i, int nbmaps, char *s);
int			parse_level_map(t_map *m, char **tab);
void		draw_ceiling_n_floor(t_work *work, t_env *w, int x);
void		draw_networks(t_work *work, t_env *w, int x);
void		draw_walls(t_work *work, t_env *w, int x);

#endif
