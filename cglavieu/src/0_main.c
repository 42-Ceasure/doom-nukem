// gros taf de free sur le exit_game

#include "doom.h"

void			set_error(t_env *w, t_map *m, int errorno)
{
	if (errorno >= 0)
		ft_putendl("Error, program closing now.");
	exit_game(w, m);
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;
	char		***cmd;

	if ((w = malloc(sizeof(t_env))) == NULL)
		return (-1);
	if ((m = malloc(sizeof(t_map))) == NULL)
		return (-1);
	set_basics(w, m);
	if (ac > 1)
	{
		if ((cmd = parse_cmd(ac, av)) != NULL)
			l_f_priority_cmd(w, cmd);
		set_advanced(m);
	}
	if ((init_sdl(w)) == -1)
		set_error(w, m, 1);
	if (ac > 1 && cmd != NULL)
		interpret_cmd(w, m, cmd);
	else
		parse_map(w, m);
	if (!run(w, m))
		set_error(w, m, 0);
	return (0);
}
