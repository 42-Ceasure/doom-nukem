//

#include "doom.h"

void			init_world(t_env **w, t_map **m, int ac)
{
	if ((*w = (t_env *)malloc(sizeof(t_env))) == NULL)
		set_error(*w, *m, 0);
	if ((*m = (t_map *)malloc(sizeof(t_map))) == NULL)
		set_error(*w, *m, 0);
	set_basics(*w, *m, ac);
}

void			exec_cmd(t_env *w, t_map *m, char ***cmd, char **av)
{
	int ac;

	ac = w->ac;
	if ((cmd = parse_cmd(ac, av)) != NULL)
	{
		l_f_priority_cmd(w, m, cmd);
		interpret_cmd(w, m, cmd);
	}
	else
		set_error(w, m, 0);
}

void			simple_start(t_env *w, t_map *m)
{
	if ((init_sdl(w)) == -1)
		set_error(w, m, 0);
	parse_map_file(w, m);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;
	char		***cmd;

	w = NULL;
	m = NULL;
	cmd = NULL;
	init_world(&w, &m, ac);
	if (ac > 1)
		exec_cmd(w, m, cmd, av);
	else
		simple_start(w, m);
	if (!run(w, m))
		set_error(w, m, 0);
	return (0);
}
