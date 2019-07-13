/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 10:28:48 by abechet           #+#    #+#             */
/*   Updated: 2019/07/13 17:40:47 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void line(t_env *w, t_win *win, int x0, int y0, int x1, int y1)
{
  t_coor p1;
  t_coor p2;

  p1.x = x0;
  p1.y = y0;
  p2.x = x1;
  p2.y = y1;
  vect_ab(p1, p2, w, win->color);
}
