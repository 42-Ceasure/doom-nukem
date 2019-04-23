/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 10:26:17 by agay              #+#    #+#             */
/*   Updated: 2019/04/23 11:43:25 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_mixer.h"
# include "libft.h"
# include <pthread.h>
# include <fcntl.h>

# define NAME 				"Doom-Numkem3D"
# define WIDTH 				1024
# define HEIGHT 			576
# define RESIZABLE_SCREEN	1
# define FULL_SCREEN		0
# define KEY 				w->event.key.keysym.sym
# define BUTTON				w->event.button.button
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
	int				handed;
	int				aiming;
	int				firing;
	int				sector;
	int				hud;
	t_coor			coor;
	int				memz;
	t_coor			move_speed;
	t_coor			move_speedless;
	double			angle;
	double			anglesin;
	double			anglecos;
	double			yaw;
	double			field_of_vision_h;
	double			field_of_vision_v;
	double			stance;
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
	int				ytop[WIDTH];
	int				ybot[WIDTH];
	unsigned int	r;
	unsigned int	r1;
	unsigned int	r2;
	double			sx1;
	double			sx2;
	double			height;
	int				point;
}					t_draw;


typedef struct		s_sprite
{
	Uint32			*pix;
	char			*name;
	int				sx;
	int				sy;
	int				w;
	int				h;
	int				sector;
	t_coor			coor;
}					t_sprite;

typedef struct		s_texture
{
	int				w;
	int				h;
	Uint32			*pix;
}					t_texture;

typedef struct		s_weapon
{
	char			*name;
	int				range;
	int				firerate;
	int				accuracy;
	int				dispertion;
	int				ammo;
	int				magazine;
	int				reloadtime;
	t_sprite		sprt[5];
	Mix_Chunk 		*shoot;
}					t_weapon;

typedef struct		s_map
{
	int				launchwmap;
	int				trippymod;
	int				i;
	int				s;
	int				w;
	int				fd;
	char			*line;
	int				section_number;
	int				dots_count;
	int				sector_count;
	int				weapon_count;
	int				sprite_count;
	char			*map_name;
	char			*map_path;
	t_dot			*dot;
	t_sector		*sector;
	t_player		player;
	double			yaw;
	double			gravity;
	int				maxrenderedsector;
	t_weapon		*weap;
	t_sprite		*sprite;
	t_texture		*texture;
}					t_map;

typedef struct		s_menu
{
	int				screen;
	int				sel;
}					t_menu;

typedef struct		s_sound
{
	int				volume;
	Mix_Music		*musique;
	Mix_Chunk 		*jump;
	Mix_Chunk 		*ground;
}					t_sound;

typedef struct		s_env
{
	int				i;
	int				ac;
	int				window_mode;
	int				sequential_draw;
	SDL_Window		*win;
	SDL_Renderer	*rdr;
	t_sound			sound;
	Uint32			*pix;
	const Uint8		*inkeys;
	SDL_Texture		*txtr;
	SDL_Event		event;
	t_texture		main_pic[5];
	t_menu			menu;
}					t_env;

typedef struct		s_worker_arg
{
	t_env			*w;
	int				start;
}					t_worker_arg;

char				***parse_cmd(int ac, char **av);
void				l_f_priority_cmd(t_env *w, t_map *m, char ***cmd);
void				interpret_cmd(t_env *w, t_map *m, char ***cmd);
void				map_cmd(t_env *w, t_map *m, char **cmd);
void				not_a_command(t_env *w, t_map *m, char ***cmd, char *s);
void				exit_cmd(t_env *w, t_map *m, char ***cmd);
void				video_mode_cmd(t_env *w, t_map *m, char ***cmd, int i);
void				seq_cmd(t_env *w, char ***cmd, int i);
void				set_error(t_env *w, t_map *m, int errorno, char *s);
void				set_basics(t_env *w, t_map *m, int ac);
void				parse_map_file(t_env *w, t_map *m);
int					parse_map_section(t_map *m, char **tab);
int					parse_player_section(t_map *m, char **tab);
int					parse_weapon_section(t_map *m, char **tab);
int					parse_sprite_section(t_map *m, char **tab);
int					quick_look(t_env *w, t_map *m);
int					do_parse(t_map *m);
void				set_advanced_run(char **av, t_env *w, t_map *m);
void				exit_game(t_env *w, t_map *m);
int					init_sdl(t_env *w);
void				img_update(t_env *w);
void				clean_render(t_env *w, Uint32 color);
int					run(t_env *w, t_map *m);
void				draw(t_env *w, t_map *m);
void				draw_mini_map(t_env *w, t_map *m);
Uint32				color(Uint32 color1);
void				vect_ab(t_coor p1, t_coor p2, t_env *w, Uint32 color);
void				set_txtr_pix(t_env *w, int x, int y, Uint32 color);
double				vect_cross_prod(double x0, double y0, double x1, double y1);
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
int					init_draw(t_draw *d, t_reader *read, t_map *m);
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
void				hand(t_map *m, t_env *w);
void				buttondown_event(t_env *w, t_map *m);
void				buttonup_event(t_env *w, t_map *m);
void				hello_screen(t_env *w, int n);
void				ft_hud(t_env *w);
int					load_sounds(t_env *w, t_map *m);
#endif
