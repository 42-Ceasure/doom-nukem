
#include "doom.h"

void			do_alloc(t_env *w, t_map *m)
{
	if ((m->weap = (t_weapon *)malloc(sizeof(t_weapon)
		* m->weapon_count)) == NULL)
		set_error(w, m, 0, ft_strdup("weapon"));
	if ((w->ascii = (t_texture *)malloc(sizeof(t_texture)
		* w->asciino)) == NULL)
		set_error(w, m, 0, ft_strdup("ascii"));
	if ((m->sprite = (t_sprite *)malloc(sizeof(t_sprite)
		* m->sprite_count)) == NULL)
		set_error(w, m, 0, ft_strdup("sprite"));
	if ((w->texturing = (t_texture *)malloc(sizeof(t_texture)
		* m->texture_count)) == NULL)
		set_error(w, m, 0, ft_strdup("texturing"));
	if (load_sounds(w, m) == -1)
		set_error(w, m, 8, ft_strdup("load_sounds"));
}

void			parse_allocating_line(t_env *w, t_map *m, char *line)
{
	char **tmp;

	tmp = ft_strsplit(line, ':');
	if (ft_strcmp(tmp[0], "weapon") == 0)
		m->weapon_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "ascii") == 0)
		w->asciino = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "sprite") == 0)
		m->sprite_count = ft_atoi(tmp[1]);
	if (ft_strcmp(tmp[0], "texturing") == 0)
		m->texture_count = ft_atoi(tmp[1]);
	if (w->asciino > 0 && m->weapon_count > 0
		&& m->sprite_count > 0 && m->texture_count > 0)
		do_alloc(w, m);
	ft_memreg(tmp);
}
