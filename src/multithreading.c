/*BIG42HEADER*/

#include "doom.h"

void	*thread(t_worker_arg *arg)
{
	t_env		*w = arg->w;
	t_work 		*work = &arg->work;
	int			x;
	int			end_x;

	x = work->startx + arg->start * ((work->endx - work->startx) / NB_THREAD);
	end_x = work->endx - (NB_THREAD - (arg->start + 1)) * ((work->endx - work->startx) / NB_THREAD);
	while (x <= end_x)
	{
		work->z = ((x - work->x1) * (work->t2.z - work->t1.z) / (work->x2 - work->x1) + work->t1.z) * 2;
		if (work->z > 255)
			work->z = 255;
		work->ya = (x - work->x1) * (work->y2a - work->y1a) / (work->x2 - work->x1) + work->y1a;
		work->yb = (x - work->x1) * (work->y2b - work->y1b) / (work->x2 - work->x1) + work->y1b;
		work->cya = vmid(work->ya, work->ytop[x], work->ybot[x]);
		work->cyb = vmid(work->yb, work->ytop[x], work->ybot[x]);
		work->starty = work->ytop[x];
		work->stopy = work->cya - 1;
		if (w->textured == 1 && w->m->sector[work->nosector].texturing[1] != 0 && w->texturing[w->m->sector[work->nosector].texturing[1]].trsp != 1)
			ceiling_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[1]]);
		else if (w->textured == 1)
		{
			skybox(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[5]]);
			if (w->texturing[w->m->sector[work->nosector].texturing[1]].trsp == 1)
				ceiling_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[1]]);
		}
		else
			ceiling_line(x, work, w, 0x12677179);
		work->starty = work->cyb + 1;
		work->stopy = work->ybot[x];
		if (w->textured == 1 && w->texturing[w->m->sector[work->nosector].texturing[0]].trsp == 1)
		{
			skybox(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[5]]);
			ceiling_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[0]]);
		}
		else if (w->textured == 1)
			ceiling_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[0]]);
		else
			vertical_line(x, work, w, work->color2);
		if (work->network >= 0)
		{
			work->nya = (x - work->x1) * (work->ny2a - work->ny1a) / (work->x2 - work->x1) + work->ny1a;
			work->nyb = (x - work->x1) * (work->ny2b - work->ny1b) / (work->x2 - work->x1) + work->ny1b;
			work->cnya = vmid(work->nya, work->ytop[x], work->ybot[x]);
			work->cnyb = vmid(work->nyb, work->ytop[x], work->ybot[x]);
			work->r1 = 0x12010101 * (255 - work->z);
			work->r2 = 0x12040007 * (31 - work->z / 8);
			if (work->z > 255)
				work->z = 255;
			work->color.top = 0;
			work->color.bottom = 0;
			work->color.middle = (x == work->x1 || x == work->x2) ? 0 : work->r1;
			work->starty = work->cya;
			work->stopy = work->cnya - 1;
			if (w->textured == 1 && w->texturing[w->m->sector[work->nosector].texturing[3]].trsp == 1)
			{
				skybox(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[5]]);
				vertical_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[3]]);
			}
			else if (w->textured == 1)
				vertical_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[3]]);
			else
				vertical_line(x, work, w, work->color);
			arg->ytop[x] = vmid(vmax(work->cya, work->cnya), work->ytop[x], HEIGHT - 1);
			work->color.middle = (x == work->x1 || x == work->x2) ? 0 : work->r2;
			work->starty = work->cnyb + 1;
			work->stopy = work->cyb;
			if (w->textured == 1 && w->texturing[w->m->sector[work->nosector].texturing[4]].trsp == 1)
			{
				skybox(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[5]]);
				extruded_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[4]]);
			}
			else if (w->textured == 1)
				extruded_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[4]]);
			else
				vertical_line(x, work, w, work->color);
			arg->ybot[x] = vmid(vmin(work->cyb, work->cnyb), 0, work->ybot[x]);
		}
		else
		{
			work->r = 0x12010101 * (255 - work->z);

			work->color.middle = (x == work->x1 || x == work->x2) ? 0 : work->r;
			work->starty = work->cya;
			work->stopy = work->cyb;
			if (w->textured == 1 && w->texturing[w->m->sector[work->nosector].texturing[2]].trsp == 1)
			{
				skybox(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[5]]);
				wall_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[2]]);
			}
			else if (w->textured == 1)
				wall_line_textured(x, w, work, w->texturing[w->m->sector[work->nosector].texturing[2]]);
			else
				vertical_line(x, work, w, work->color);
		}
		x++;
		// if ((w->sequential_draw == 1 && (x % 3 == 0)) || (w->sequential_frame == 1 && (x % 8 == 0)))
		// 		img_update(w);
	}
	return (NULL);
}

int		calcul_render(t_env *w, t_map *m, t_work work, int *ybot, int *ytop)
{
	pthread_t		calc_thread[NB_THREAD];
	t_worker_arg	args[NB_THREAD];
	int				i;
	int				thr[NB_THREAD];

	i = 0;
	while (i < NB_THREAD)
	{
		args[i] = (t_worker_arg)
		{
			.w = w,
			.start = i,
			.work = work,
			.ybot = ybot,
			.ytop = ytop
		};
		thr[i] = pthread_create(&calc_thread[i], NULL, (void*)thread, args + i);
		if (thr[i])
			set_error(w, m, 8, "threadon't exist");
		i++;
	}
	while (i--)
		pthread_join(calc_thread[i], NULL);
	return (0);
}
