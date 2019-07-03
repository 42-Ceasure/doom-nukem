/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 16:06:30 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 18:18:21 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include <SDL.h>
# include <SDL_image.h>
# include <SDL_ttf.h>
# include <SDL_mixer.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <fcntl.h>
# include "libft.h"
# include "w3d_defines.h"
# include "w3d_structs.h"

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
	struct s_lst	*head;
	struct s_lstlst	*next;
}					t_lstlst;

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef struct		s_lstasset
{
	int				x;
	int				y;
	int				sector;
	int				asset_type;
	struct s_lstasset	*next;
}					t_lstasset;

char		**map(t_win *win);
int			init(t_win *win);
void		draw_grid(t_win *win);
int			clear_n_exit(t_win *win, int error);
void		loop_play(t_win *win);
void		sdl_event(t_win *win);
t_lst		*lstnew(int x, int y, int sector);
t_lstlst	*lstlstnew(t_win *win);
int			check_list(t_win *win, t_lst *lst, int x, int y);
void		ft_draw_line(t_win *win, int x1, int y1, int x2, int y2);
void		put_pixel_to_surface(SDL_Surface *srfc, int x, int y, Uint32 color);
void		print_line(t_win *win, int x1, int y1, int x2, int y2);
void 		line(t_win *win, int x0, int y0, int x1, int y1);
void		undo(t_win *win);
void		delete_sector(t_win *win);
int			check_neighbour(t_win *win);
int			point_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m);
int			len_list(t_lst *lst);
t_lstlst	*recursive_triangulate(t_win *win, t_lst *polygone, t_lstlst *triangles);
void		placing(t_win *win);
void		pick_asset(t_win *win);
void		mode(t_win *win);
int			len_listlist(t_lstlst *lstlst);
void		asset_overing(t_win *win);
void		delete_asset(t_win *win);
void		overing(t_win *win);

void		save_map(t_win *win);
void		map_save(t_win *win);

int			final_texture_to_screen(SDL_Surface *surface, SDL_Surface *texture, int x, int y, int width, int height);

void		sectors_in_tab(t_win *win);
void		sectors_in_tab2(t_win *win);

void		clear_window(t_win *win);
void		recursive_check(t_win *win);
void		free_triangles(t_win *win);
int			int_len(int nb);
void		sort_int_tab(int *tab, int size);
int		which_sector_neighbour(t_win *win, int x1, int y1, int x2, int y2, int sector);

void		test(t_win *win);
//void		check2(t_win *win);

#endif
