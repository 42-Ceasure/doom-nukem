/*BIG42HEADER*/

#include "doom.h"

void	*thread(t_worker_arg *arg)
{
	const t_env	*w = arg->w;
	int			x;

	printf("%d\n", w->i);
	x = arg->start * (WIDTH / NB_THREAD);
	while (x < (arg->start + 1) * (WIDTH / NB_THREAD))
	{
		//draw(w, m);
		x++;
	}
	return (NULL);
}

int		calcul_render(t_env *w, t_map *m)
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
			.start = i
		};
		thr[i] = pthread_create(&calc_thread[i], NULL, (void*)thread, args + i);
		if (thr[i])
			set_error(w, m, 8, "threadon't exist");
		i++;
	}
	while (i--)
		pthread_join(calc_thread[i], NULL);
	img_update(w);
	return (0);
}
