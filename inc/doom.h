/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:26:17 by agay              #+#    #+#             */
/*   Updated: 2019/06/13 14:17:12 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include <pthread.h>
# include <fcntl.h>

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
# define NB_THREAD			16

typedef struct		s_filer
{
	int	buffer;
	int stop;
	int fd;
	int fd2;
	char *buff;
	char *line;
	char **tmp;
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

typedef struct		s_dot
{
	double			x;
	double			y;
}					t_dot;

typedef struct		s_coor
{
	double			x;
	double			y;
	double			z;
}					t_coor;

typedef struct		s_sector
{
	int				wall_count;
	double			floor;
	double			ceiling;
	t_dot			*dot;
	int				*network;
}					t_sector;

typedef struct		s_player
{
	int				bal;
	char			*fps;
	char			*stractu_ammo;
	int				intactu_ammo;
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

typedef struct		s_draw
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
}					t_draw;

typedef struct		s_calc_sprite
{
	double			v1x;
	double			v1y;
	double			t1x;
	double			t1z;
	double			xscale1;
	double			x1;
	double			y1a;
	double			yscale1;
	double			diffx;
	double			diffy;
}					t_cal_sprt;

typedef struct		s_sprite
{
	Uint32			*pix;
	char			*name;
	char			*type;
	float			sx;
	float			sy;
	int				w;
	int				h;
	int				len;
	int				sector;
	int				take;
	int				vis;
	double			range;
	t_coor			coor;
}					t_sprite;

typedef struct		s_texture
{
	int				w;
	int				h;
	int				len;
	Uint32			*pix;
}					t_texture;

typedef struct		s_weapon
{
	char			*name;
	int				range;
	int				firerate;
	int				accuracy;
	double			dispertion;
	int				ammo;
	int				actu_ammo;
	int				magazine;
	int				reloadtime;
	int				recoil;
	t_sprite		sprt[5];
	Mix_Chunk 		*shoot;
}					t_weapon;

typedef struct		s_visible
{
	int				*wall;
}					t_visible;

typedef struct		s_map
{
	void			*world;
	int				stop;
	int				launchwmap;
	int				trippymod;
	int				i;
	int				k;
	int				s;
	int				w;
	int				fd;
	int				asc;
	int				section_number;
	int				dots_count;
	int				sector_count;
	int				weapon_count;
	int				sprite_count;
	int				maxrenderedsector;
	double			yaw;
	double			gravity;
	char			*line;
	char			*map_name;
	char			*map_path;
	t_dot			*dot;
	t_visible		*visible;
	t_sector		*sector;
	t_weapon		*weap;
	t_sprite		*sprite;
	t_texture		*texture;
	t_texture		hud;
	t_texture		fire;
	t_player		player;
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

typedef struct		s_res
{
	int width;
	int height;
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
}					t_dtime;

typedef struct		s_env
{
	t_map			*m;
	char			*light_nb;
	double			loading_time;
	int				i;
	int				ac;
	int				asciichk;
	int				asciino;
	int				stopread;
	int				invert;
	double			random;
	t_res			res;
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
	t_texture		main_pic[2];
	t_text			txt;
	t_menu			menu;
	t_dot			txthead;
	t_dot			txtnxtline;
	t_dot			txtnxtto;
	t_dtime			dtime;
}					t_env;


typedef struct		s_worker_arg
{
	t_env			*w;
	int				start;
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
void 				replace_line(char *path, char *balise, char *content);
void				change_settings(t_map *m, t_env *w);
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
double				intersectbox(t_intersect i);
t_coor				intersect(t_intersect i);
double				isoverlap(double a0, double a1, double b0, double b1);
double				pointside(t_coor p, double x0,
					double y0, double x1, double y1);
double				yaw(double y, double z, t_map *m);
void				init_verification(t_draw *draw);
int					init_draw(t_env *w, t_draw *d, t_reader *read, t_map *m);
void				vertical_line(int x, int *box, t_env *w, t_color color);
void				ceiling_line(int x, int *box, t_env *w, Uint32 color);
int					moving_head(t_draw *w, t_reader read, t_map *m);
int					ceiling_and_floor(t_draw *d, t_map *m,
					t_reader read, int point);
void				check_invisible(t_draw *d, t_reader read, t_map *m);
void				recap_parsing(t_env *w, t_map *m, char **str);
void				recap_map_list_sector(t_env *w, t_map *m, char **str);
void				recap_map_list_sectors(t_map m, char *str);
void				recap_sector_general(t_map m, int i);
void				recap_sector_dots(t_map m, int i);
void				recap_sector_network(t_map m, int i);
void				recap_sector(t_map m, int i);
int					calcul_render(t_env *w, t_map *m);
void				key_events(t_env *w, t_map *m);
void				keydown_events(t_env *w, t_map *m);
void				keyup_events(t_env *w, t_map *m);
void				motion_events(t_env *w, t_map *m);
void				move_player(double dx, double dy, t_map *m);
void				get_height(t_map *m);
void				is_falling(t_map *m, t_env *w);
void				slow_down(t_env *w, t_map *m);
void				is_moving(t_map *m);
void				main_menu(t_env *w, t_map *m);
t_texture			load_img(t_env *w, t_map *m, char *s);
void				initsprite(t_sprite **sprite, int count);
void				hand(t_env *w, t_map *m);
void				buttondown_event(t_env *w, t_map *m);
void				buttonup_event(t_env *w, t_map *m);
void				hello_screen(t_env *w);
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
void				och_door(t_map *m);
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
void				get_that_time(t_env *w);
void				draw_sprite(t_env *w, t_map *m, int x);
void				draw_ennemy(t_env *w, t_map *m, int x);

#endif
