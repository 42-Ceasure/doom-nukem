/*BIG42HEADER*/

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
	if (errorno == 5)
		ft_putstr("File not found : \"");
	if (errorno == 6)
		ft_putstr("Section invalid : \"");
	if (errorno == 7)
		ft_putstr("This sector don't exist : \"");
	if (s != NULL)
	{
		ft_putstr(s);
		free(s);
	}
	else
		ft_putstr("NULL");
	ft_putendl("\"\nProgram closing now.");
	exit_game(w, m);
}
