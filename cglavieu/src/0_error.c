//

#include "doom.h"

void			set_error(t_env *w, t_map *m, int errorno, char *s)
{
	if (errorno == 0)
		ft_putstr("Memory allocation error : \"");
	if (errorno == 1)
		ft_putstr("Incorrect command format : \"");
	if (errorno == 2)
		ft_putstr("Incorrect command : \"");
	if (errorno == 3)
		ft_putstr("Incorrect argument : \"");
	if (errorno == 4)
		ft_putstr("Execution error in : \"");
	ft_putstr(s);
	ft_putendl("\"\nProgram closing now.");
	exit_game(w, m);
}
