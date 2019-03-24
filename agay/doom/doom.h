/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 18:35:11 by agay              #+#    #+#             */
/*   Updated: 2019/03/23 20:44:03 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DOOM_H
# define DOOM_H

# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
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

/*typedef struct		s_doom
{
	double	x;
	double	y;
	double	x1;
	double	y1;
	double	vx1;
	double	vx2;
	double	vy1;
	double	vy2;
	double	dx1;
	double	dx2;
	double	dy1a;
	double	dy1b;
	double	dy2a;
	double	dy2b;
	double	cx;
	double	cy;
	double	a;
	double	tx1;
	double	tx2;
	double	ty1;
	double	ty2;
	double	tz1;
	double	tz2;
}					t_doom;*/

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
}					t_doom;

void	draw_utility(t_mlx *mlx, t_doom doom, int color);
int		key(int key, void **tab);
void	draw(t_mlx *mlx, t_doom doom);

#endif
