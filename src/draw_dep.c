/*BIG42HEADER*/

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
		m->visible[read.now.sectorno].wall[d->point] = 1;
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
	d->x1 = d->winwidth / 2 - (int)(d->t1.x * d->xscale1);
	d->x2 = d->winwidth / 2 - (int)(d->t2.x * d->xscale2);
	if (d->x1 >= d->x2 || d->x2 < read.now.sx1 || d->x1 > read.now.sx2)
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

int		moving_head(t_draw *d, t_reader read, t_map *m)
{
	d->y1a = d->winheight / 2 - (int)(yaw(d->yceil, d->t1.z, m) * d->yscale1);
	d->y2a = d->winheight / 2 - (int)(yaw(d->yceil, d->t2.z, m) * d->yscale2);
	d->y1b = d->winheight / 2 - (int)(yaw(d->yfloor, d->t1.z, m) * d->yscale1);
	d->y2b = d->winheight / 2 - (int)(yaw(d->yfloor, d->t2.z, m) * d->yscale2);
	d->ny1a = d->winheight / 2 - (int)(yaw(d->nyceil, d->t1.z, m) * d->yscale1);
	d->ny2a = d->winheight / 2 - (int)(yaw(d->nyceil, d->t2.z, m) * d->yscale2);
	d->ny1b = d->winheight / 2 - (int)(yaw(d->nyfloor, d->t1.z, m) * d->yscale1);
	d->ny2b = d->winheight / 2 - (int)(yaw(d->nyfloor, d->t2.z, m) * d->yscale2);
	d->startx = vmax(d->x1, read.now.sx1);
	d->endx = vmin(d->x2, read.now.sx2);
	return (d->startx);
}
