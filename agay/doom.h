/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:35:11 by agay              #+#    #+#             */
/*   Updated: 2019/03/25 19:08:05 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "libft/inc/libft.h"
# include "minilibx_macos/mlx.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# define PI_X 1000
# define PI_Y 500
 
typedef struct		s_mlx
{
	void	*mlx;
	void	*win;
	void	*img;
	int		*data;
	int		size;
	int		bits;
	int		endian;
}					t_mlx;

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

typedef struct		s_doom
{
	double	cx;
	double	cy;
	double	x;
	double	x1;
	double	y;
	double	y1;
	double	a;
	double	ar;
	double	wslope;
	double	diffx;
	double	diffy;
	double	dist;
	double	wallh;
	double	save;
	double	fov;
}					t_doom;

void	draw_utility(t_mlx *mlx, t_doom doom, int color);
int		key(int key, void **tab);
void	draw(t_mlx *mlx, t_doom doom, t_map *m);
void		recap_parsing(t_map *m, char **str);
void		set_basic_run(t_map *m);
void		set_advanced_run(char **av, t_map *m);
int			quick_look(t_map *m);
int			do_parse(t_map *m);

#endif
