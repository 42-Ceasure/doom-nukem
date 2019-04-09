// gros taf de free sur le exit_game

#include "doom-nukem.h"

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
		{
			ft_putendl("error on command");
			ft_putendl("program closing now");
		}
		interpret_cmd(w, m, cmd);
	}
	if (!run(w, m))
		ft_putendl("program closing now");
	return (0);
}
