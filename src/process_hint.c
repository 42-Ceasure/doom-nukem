/*BIG42HEADER*/

#include "doom.h"

void			print_load(char *s, int i3, int len)
{
	char		*pre;
	char		*nb;
	char		*post;

	nb = ft_itoa((int)((double)i3 / (double)len * 100));
	post = ft_strjoin(nb, "\r");
	pre = ft_strjoin(s, post);
	ft_putstr(pre);
	free(nb);
	free(post);
	free(pre);
}

void			process_hint(int i, char *s)
{
	char		*pre;
	char		*post;

	ft_putstr("                                                        \r");
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (i == 0)
		pre = ft_strjoin("done", post);
	if (i == 1)
		pre = ft_strjoin("allocating memory for ", post);
	if (i == 2)
		pre = ft_strjoin("initialisating ", post);
	if (i == 3)
		pre = ft_strjoin("processing ", post);
	if (i == 4)
		pre = ft_strjoin("parsing ", post);
	if (i == 5)
		pre = ft_strjoin("running ", post);
	if (i == 6)
		pre = ft_strjoin("loading ", post);
	if (i == 7)
		pre = ft_strjoin("extracting ", post);
	ft_putstr(pre);
	free(post);
	if (pre != NULL)
		free(pre);
}

void			process_hint_w(t_env *w, int i, char *s)
{
	char		*pre;
	char		*post;
	t_dot		dot;

	w->txthead.x = 6;
	w->txthead.y = 550;
	dot.x = 800;
	dot.y = 550;
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (i == 0)
		pre = ft_strjoin("done", post);
	if (i == 1)
		pre = ft_strjoin("allocating memory for ", post);
	if (i == 2)
		pre = ft_strjoin("initialisating ", post);
	if (i == 3)
		pre = ft_strjoin("processing ", post);
	if (i == 4)
		pre = ft_strjoin("parsing ", post);
	if (i == 5)
		pre = ft_strjoin("running ", post);
	if (i == 6)
		pre = ft_strjoin("loading ", post);
	if (i == 7)
		pre = ft_strjoin("extracting ", post);
	hello_screen(w);
	type_str(w, w->txthead, pre, 0x12FEA800);
	type_str(w, dot, "loading game...", 0x12FEA800);
	img_update(w);
	free(post);
	if (pre != NULL)
		free(pre);

}
