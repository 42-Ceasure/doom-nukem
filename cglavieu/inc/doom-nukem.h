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
	char			**network;
}					t_sector;

typedef struct		s_player
{
	int				sector;
	t_coor			coor;
	t_coor			move_speed;
	double			angle;
	double			anglesin;
	double			anglecos;
	double			yaw;
}					t_player;

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
void		exit_game(t_env *w, t_map *m);
void		recap_parsing(t_map *m, char **str);
void		free_map_struct(t_map *m);

#endif