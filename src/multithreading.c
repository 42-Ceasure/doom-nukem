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
		work->z = vmin(work->z, 255);
		draw_ceiling_n_floor(work, w, x);
		if (work->network >= 0)
		{
			draw_networks(work, w, x);
			arg->ytop[x] = vmid(vmax(work->cya, work->cnya), work->ytop[x], HEIGHT - 1);
			arg->ybot[x] = vmid(vmin(work->cyb, work->cnyb), 0, work->ybot[x]);
		}
		else
			draw_walls(work, w, x);
		x++;
	}
	return (NULL);
}

int		calcul_render_mthrd(t_env *w, t_work work, int *ybot, int *ytop)
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
			set_error(w, w->m, 8, "threadon't exist");
		i++;
	}
	while (i--)
		pthread_join(calc_thread[i], NULL);
	return (0);
}
