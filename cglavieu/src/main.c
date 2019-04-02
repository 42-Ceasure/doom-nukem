// gros taf de free sur le exit_game

#include "doom-nukem.h"

void	set_special_run(t_map *m, char **av)
{
	char **tmp;
	char **tmp2;

	m->i = 0;
	m->s = 0;
	m->section_number = 0;
	m->dots_count = 0;
	m->sector_count = 0;
	m->dot = NULL;
	m->sector = NULL;
	m->player.field_of_vision = 1.0472;
	m->map_path = av[2];
	tmp = ft_strsplit(av[2], '/');
	tmp2 = ft_strsplit(tmp[1], '.');
	m->map_name = tmp2[0];
	free(tmp);
	free(tmp2);
	if (quick_look(m) == -1 || do_parse(m) == -1)
	{
		write(1, "error on map parsing, check your map path\n", 43);
		exit(0);
	}
}

void	set_basic_run(t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->section_number = 0;
	m->dots_count = 0;
	m->sector_count = 0;
	m->map_name = "test";
	m->map_path = "maps/map0.dn3d";
	m->dot = NULL;
	m->sector = NULL;
	m->player.field_of_vision = 1.0472;
	if (quick_look(m) == -1 || do_parse(m) == -1)
	{
		write(1, "error on map parsing\n", 22);
		exit(0);
	}
}

void	set_advanced_run(char **av, t_env *w, t_map *m)
{
	if (ft_strcmp(av[1], "-map") == 0)
	{
		if (av[2])
			set_special_run(m, av);
		else
			ft_putendl("no map specified");
	}
	else
	{		
		set_basic_run(m);
		if ((ft_strcmp(av[1], "-recap_parsing") == 0) && av[2] != NULL)
			recap_parsing(m, av);
		else
		{
			ft_putendl("\nThis part of the program is curently in development.");
			ft_putendl("the only command usable now is \"-recap_parsing\" with args :");
			ft_putendl("  \"map_list_general\"  \"map_list_dots\"  \"map_list_sectors\"");
			ft_putendl("  \"map_list_sector all <attribut>\"  \"player_list_vars\"\n");
			ft_putendl("possibles <attribut> are \"general\" \"dots\" \"network\"");
		}
		free(w);
		free(m);
		exit(0);
	}
}

int				main(int ac, char **av)
{
	t_env		*w;
	t_map		*m;

	if (((w = malloc(sizeof(t_env))) == NULL) || ((m = malloc(sizeof(t_map))) == NULL))
		return (0);
	if (ac == 1)
		set_basic_run(m);
	else
		set_advanced_run(av, w, m);
	if (!run(w, m))
		ft_putendl("program closing now");
	return (0);
}
