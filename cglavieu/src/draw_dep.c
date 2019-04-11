/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 05:56:42 by agay              #+#    #+#             */
/*   Updated: 2019/04/09 10:07:16 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	check_invisible(t_draw *d, t_reader read, t_map *m)
{
	d->v1.x = m->sector[read.now.sectorno].dot[d->point + 0].x - PL_X;
	d->v1.y = m->sector[read.now.sectorno].dot[d->point + 0].y - PL_Y;
	d->v2.x = m->sector[read.now.sectorno].dot[d->point + 1].x - PL_X;
	d->v2.y = m->sector[read.now.sectorno].dot[d->point + 1].y - PL_Y;
	d->pcos = PL_AC;
	d->psin = PL_AS;
	d->t1.x = d->v1.x * d->psin - d->v1.y * d->pcos;
	d->t1.z = d->v1.x * d->pcos + d->v1.y * d->psin;
	d->t2.x = d->v2.x * d->psin - d->v2.y * d->pcos;
	d->t2.z = d->v2.x * d->pcos + d->v2.y * d->psin;
	if (d->t1.z <= 0 || d->t2.z <= 0)
	{
		init_verification(d);
		if (d->t1.z < d->nearz)
		{
			d->t1.x = (d->ip1.y > 0) ? d->ip1.x : d->ip2.x;
			d->t1.z = (d->ip1.y > 0) ? d->ip1.y : d->ip2.y;
		}
		if (d->t2.z < d->nearz)
		{
			d->t2.x = (d->ip1.y > 0) ? d->ip1.x : d->ip2.x;
			d->t2.z = (d->ip1.y > 0) ? d->ip1.y : d->ip2.y;
		}
	}
}

int		ceiling_and_floor(t_draw *d, t_map *m, t_reader read, int point)
{
	d->xscale1 = m->player.field_of_vision_h / d->t1.z;
	d->yscale1 = (m->player.field_of_vision_v) / d->t1.z;
	d->xscale2 = m->player.field_of_vision_h / d->t2.z;
	d->yscale2 = (m->player.field_of_vision_v) / d->t2.z;
	d->x1 = WIDTH / 2 - (int)(d->t1.x * d->xscale1);
	d->x2 = WIDTH / 2 - (int)(d->t2.x * d->xscale2);
	if (d->x1 >= d->x2 || d->x2 < read.now.sx1
			|| d->x1 > read.now.sx2)
		return (0);
	d->yceil = m->sector[read.now.sectorno].ceiling - m->player.coor.z;
	d->yfloor = m->sector[read.now.sectorno].floor - m->player.coor.z;
	d->network = m->sector[read.now.sectorno].network[point];
	d->nyceil = 0;
	d->nyfloor = 0;
	if (d->network >= 0)
	{
		d->nyceil = m->sector[d->network].ceiling - m->player.coor.z;
		d->nyfloor = m->sector[d->network].floor - m->player.coor.z;
	}
	return (1);
}

int		moving_head(t_draw *w, t_reader read, t_map *m)
{
	w->y1a = HEIGHT / 2 - (int)(yaw(w->yceil, w->t1.z, m) * w->yscale1);
	w->y2a = HEIGHT / 2 - (int)(yaw(w->yceil, w->t2.z, m) * w->yscale2);
	w->y1b = HEIGHT / 2 - (int)(yaw(w->yfloor, w->t1.z, m) * w->yscale1);
	w->y2b = HEIGHT / 2 - (int)(yaw(w->yfloor, w->t2.z, m) * w->yscale2);
	w->ny1a = HEIGHT / 2 - (int)(yaw(w->nyceil, w->t1.z, m) * w->yscale1);
	w->ny2a = HEIGHT / 2 - (int)(yaw(w->nyceil, w->t2.z, m) * w->yscale2);
	w->ny1b = HEIGHT / 2 - (int)(yaw(w->nyfloor, w->t1.z, m) * w->yscale1);
	w->ny2b = HEIGHT / 2 - (int)(yaw(w->nyfloor, w->t2.z, m) * w->yscale2);
	w->startx = vmax(w->x1, read.now.sx1);
	w->endx = vmin(w->x2, read.now.sx2);
	return (w->startx);
}