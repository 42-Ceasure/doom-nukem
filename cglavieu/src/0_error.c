//

#include "doom.h"

void			set_error(t_env *w, t_map *m, int errorno)
{
	if (errorno >= 0)
		ft_putendl("Error, program closing now.");
	exit_game(w, m);
}
