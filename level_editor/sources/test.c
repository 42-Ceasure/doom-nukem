/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/19 12:10:09 by abechet           #+#    #+#             */
/*   Updated: 2019/06/19 12:10:21 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"


double testsign(double a)
{
	return (((a) > 0) - ((a) < 0));
}

double testv_c_p(double x0, double y0, double x1, double y1)
{
	return (x0 * y1 - x1 * y0);
}

double testpointside(t_dot m, double x0, double y0, double x1, double y1)
{
	return(testsign(testv_c_p(x1 - x0, y1 - y0, m.x - x0, m.y - y0)));
}

int		testpoint_in_triangle(t_dot p0, t_dot p1, t_dot p2, t_dot m)
{
	if (testpointside(m, p0.x, p0.y, p1.x, p1.y) > 0
	 	&& testpointside(m, p1.x, p1.y, p2.x, p2.y) > 0
			&& testpointside(m, p2.x, p2.y, p0.x, p0.y) > 0)
		return (1);
	return (0);
}

void	test(t_win *win)
{
	t_dot p0;
	t_dot p1;
	t_dot p2;
	t_dot m;

	p0.x = win->lstlst->head->x;
	p0.y = win->lstlst->head->y;
	p1.x = win->lstlst->head->next->x;
	p1.y = win->lstlst->head->next->y;
	p2.x = win->lstlst->head->next->next->x;
	p2.y = win->lstlst->head->next->next->y;

	m.x = win->x2;
	m.y = win->y2;

	if (win->lstlst)
		printf("%d \n ", testpoint_in_triangle(p0, p1, p2, m));
}
