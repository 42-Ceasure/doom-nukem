#ifndef DOOM_NUKEM_H
# define DOOM_NUKEM_H

# include "SDL2/SDL.h"
# include "libft.h"
# include <fcntl.h>

# define NAME 		"Doom-Numkem3D"
# define WIDTH 		400
# define HEIGHT 	300
# define KEY 		w->event.key.keysym.sym

typedef struct 		s_dot
{
	double			x1;
	double			y1;
}					t_dot;

typedef struct		s_coor
{
	double			x;
	double			y;
	double			z;
}					t_coor;

typedef struct		s_sector
{
	double			floor;
	double			ceiling;
	t_dot			*dot;
	signed char		*nxtroom;
}					t_sector;

typedef struct		s_player
{
	t_coor			coor;
	t_coor			move_speed;
	double			angle;
	double			anglesin;
	double			anglecos;
	double			yaw;
}					t_player;

typedef struct		s_map
{
	int				fd;
	char			*line;
	int				section_number;
	int				dots_count;
	int				sector_count;
	char			*map_name;
	char			*map_path;
	t_sector		*sector;
	t_player		player;
}					t_map;

typedef struct		s_env
{
	int				i;
	SDL_Window		*win;
	SDL_Renderer	*rdr;
	Uint32			*pix;
	SDL_Texture		*txtr;
	SDL_Event		event;
}					t_env;

t_map	set_basic_run(t_env *w);
t_map	set_advanced_run(t_env *w, char **av);
int			init_sdl(t_env *w);
void		run(t_env *w);
void		exit_game(t_env *w);

#endif