#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "SDL2/SDL.h"
# include "libft.h"
# include <fcntl.h>

# define NAME 		"Doom-Numkem3D"
# define WIDTH 		800
# define HEIGHT 	600
# define KEY 		w->event.key.keysym.sym
# define MRS		32
# define PL_X		m->player.coor.x
# define PL_Y		m->player.coor.y
# define PL_A		m->player.angle
# define HFOV		(0.73f*HEIGHT)
# define VFOV		(.2f*HEIGHT)
# define STAND		8
# define HEADMARGIN	1
# define CROUCH		2.5
# define KNEEH		2

typedef struct		s_vect
{
	int x1;
	int y1;
	int x2;
	int y2;
	int dx;
	int dy;
}					t_vect;

typedef struct		s_color
{
	Uint32 top;
	Uint32 middle;
	Uint32 bottom;
}					t_color;

typedef struct	s_item
{
	int sectorno;
	int sx1;
	int sx2;
}				t_item;

typedef struct		s_reader
{
	t_item queue[32];
	t_item *start;
	t_item *stop;
}					t_reader;

typedef struct 		s_dot
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
	signed char		*network;
}					t_sector;

typedef struct		s_player
{
	int				sector;
	t_coor			coor;
	t_coor			move_speed;
	t_coor			move_speedless;	
	double			angle;
	double			anglesin;
	double			anglecos;
	double			yaw;
	double			field_of_vision;
	double			stance;
	int				fall;
	int				ground;
	int				moving;
	double			height;
	double			crouch;
	double			hole_low;
	double			hole_high;
	int				press;
	double			accel;
}					t_player;

typedef struct		s_intersect
{
	double x1;
	double x2;
	double x3;
	double x4;
	double y1;
	double y2;
	double y3;
	double y4;
	double xd;
	double yd;
}					t_intersect;

typedef struct		s_work
{
	t_intersect i1;
	t_intersect i2;
	t_coor v1;
	t_coor v2;
	t_coor t1;
	t_coor t2;
	t_coor ip1;
	t_coor ip2;
	t_coor lol1;
	t_coor lol2;
	t_coor lel1;
	t_coor lel2;
	t_coor lul1;
	t_coor lul2;
	t_coor p1;
	t_coor p2;
	double p1yb;
	double p2yb;
	double pcos;
	double psin;
	double nearz;
	double farz;
	double nearside;
	double farside;
	int ya;
	int yb;
	double xscale1;
	double yscale1;
	double xscale2;
	double yscale2;
	double yceil;
	double yfloor;

	double x1;
	double x2;
	double y1a;
	double y1b;
	double y2a;
	double y2b;
	double startx;
	double endx;
	int z;
	int cya;
	int cyb;

	unsigned int r;
	unsigned int r1;
	unsigned int r2;

	double height;
}					t_work;

typedef struct		s_map
{
	int				i;
	int				s;
	int				fd;
	char			*line;
	int				section_number;
	int				dots_count;
	int				sector_count;
	char			*map_name;
	char			*map_path;
	t_dot			*dot;
	t_sector		*sector;
	t_player		player;
	double			yaw;
}					t_map;

typedef struct		s_env
{
	int				i;
	SDL_Window		*win;
	SDL_Renderer	*rdr;
	Uint32			*pix;
	const Uint8		*inkeys;
	SDL_Texture		*txtr;
	SDL_Event		event;
}					t_env;

void		set_basic_run(t_map *m);
void		set_advanced_run(char **av, t_env *w, t_map *m);
int			init_sdl(t_env *w);
int			quick_look(t_map *m);
int			do_parse(t_map *m);
int			run(t_env *w, t_map *m);
void 		draw(t_env *w, t_map m);
void		clean_render(t_env *w, Uint32 color);
void		exit_game(t_env *w, t_map *m);
void		recap_parsing(t_map *m, char **str);
Uint32		color(Uint32 color1);
double vMin(double a, double b);
double vMax(double a, double b);
double vMid(double a, double min, double max);
double vect_cross_prod(double x0, double y0, double x1, double y1);
double isOverlap(double a0, double a1, double b0, double b1);
double intersectBox(t_intersect i);
double pointSide(t_coor p, double x0, double y0, double x1, double y1);
t_coor intersect(t_intersect i);
void vect_ab(t_coor p1, t_coor p2, t_env *w, Uint32 color);
void	set_txtr_pix(t_env *w, int x, int y, Uint32 color);
double yaw(double y, double z, t_map m);
void draw_mini_map(t_env *w, t_map m);

#endif