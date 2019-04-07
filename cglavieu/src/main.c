// gros taf de free sur le exit_game

#include "doom-nukem.h"

void	set_special_run(t_map *m, char **av)
{
	char **tmp;
	char **tmp2;

	m->map_path = av[2];
	tmp = ft_strsplit(av[2], '/');
	tmp2 = ft_strsplit(tmp[1], '.');
	m->map_name = tmp2[0];
	ft_memreg(tmp);
	ft_memreg(tmp2);
	if (quick_look(m) == -1 || do_parse(m) == -1)
	{
		ft_putendl("error on map,");
		ft_putendl("that can be due to an incorrect map file or an incorrect path");
		exit(0);
	}
}

void	set_basic_run(t_map *m)
{
	if (quick_look(m) == -1 || do_parse(m) == -1)
	{
		write(1, "error on map parsing\n", 22);
		exit(0);
	}
}

void	set_basics(t_map *m)
{
	m->i = 0;
	m->s = 0;
	m->map_path = "maps/map0.dn3d";
	m->map_name = "test";
	m->section_number = 0;
	m->sector_count = 0;
	m->sector = NULL;
	m->dots_count = 0;
	m->dot = NULL;
	m->player.field_of_vision_h = 512;
	m->player.field_of_vision_v = 450;
	m->player.fall = 1;
	m->player.stance = 0;
	m->player.display = 0;
	m->yaw = 0;
	m->line = NULL;
	m->gravity = BASE_GRAVITY;
	m->maxrenderedsector = 32;
	m->sequential_draw = 0;
}

void	set_advanced_run(char **av, t_env *w, t_map *m)
{
	if (ft_strcmp(av[1], "-map") == 0)
	{
		if (av[2])
		{
			if (av[3])
			{
				if (ft_strcmp(av[3], "-seq") == 0)
					m->sequential_draw = 1;
			}
			set_special_run(m, av);
		}
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
			ft_putendl("the only commands usable now are\n\"-recap_parsing\" with args :");
			ft_putendl("\t\"map_list_general\"\t\"map_list_dots\"\t\"map_list_sectors\"");
			ft_putendl("\t\"map_list_sector all <attribut>\"\t\"player_list_vars\"");
			ft_putendl("<attribut> are \"general\" \"dots\" \"network\"");
			ft_putendl("\n-map maps/<name_of_map.dn3d>");
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
	set_basics(m);
	if (ac == 1)
		set_basic_run(m);
	else
		set_advanced_run(av, w, m);
	if (!run(w, m))
		ft_putendl("program closing now");
	return (0);
}
