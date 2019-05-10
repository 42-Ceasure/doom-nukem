/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 00:54:20 by agay              #+#    #+#             */
/*   Updated: 2019/04/09 07:59:39 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_H
# define DRAW_H

# include "doom-nukem.h"

typedef struct		s_draw
{
	t_color color;
	t_color color2;
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
	int ya;
	int yb;
	int cya;
	int cyb;
	double nyceil;
	double nyfloor;
	int network;
	double ny1a;
	double ny1b;
	double ny2a;
	double ny2b;
	int nya;
	int nyb;
	int cnya;
	int cnyb;
	double startx;
	double endx;
	int z;
	int ytop[WIDTH];
	int ybot[WIDTH];
	unsigned int r;
	unsigned int r1;
	unsigned int r2;
	double sx1;
	double sx2;
	double height;
	int		point;
}					t_draw;

#endif
