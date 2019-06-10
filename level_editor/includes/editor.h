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

typedef struct	s_lst
{
	int				x;
	int				y;
	int				sector;
	struct s_lst	*next;
}				t_lst;

char		**map(t_win *win);
int			init(t_win *win);
void		draw_grid(t_win *win);
int			clear_n_exit(t_win *win, int error);
void		loop_play(t_win *win);
void		sdl_event(t_win *win);
void		init_grid(t_win *win);
t_lst		*lstnew(int x, int y, int sector);
int			check_list(t_win *win, t_lst *lst, int x, int y, int sector);
void		ft_draw_line(t_win *win, int x1, int y1, int x2, int y2);
void		put_pixel_to_surface(SDL_Surface *srfc, int x, int y, Uint32 color);
void		print_line(t_win *win, int x1, int y1, int x2, int y2);
void 		line(t_win *win, int x0, int y0, int x1, int y1);

#endif
