// gros taf de free sur le exit_game

#include "doom-nukem.h"

void			set_error(t_env *w, t_map *m, int errorno)
{
	(void)w;
	(void)m;
	(void)errorno;

	ft_putendl("Error, program closing now.");
	exit(0);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;
	char		***cmd;

	if (((w = malloc(sizeof(t_env))) == NULL) || ((m = malloc(sizeof(t_map))) == NULL))
		return (0);
	set_basics(w, m);
	if (ac == 1)
		set_basic_run(m);
	else
	{
		cmd = parse_cmd(ac, av);
		if (cmd == NULL)
			set_error(w, m, 0);
		interpret_cmd(w, m, cmd);
	}
	if ((init_sdl(w)) == -1)
		set_error(w, m, 1);
	if (!run(w, m))
		ft_putendl("program closing now");
	return (0);
}
