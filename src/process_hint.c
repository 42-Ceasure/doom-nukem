/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_hint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 13:35:38 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/16 05:39:27 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char			*other_if(int i, char *post)
{
	if (i == 2)
		return (ft_strjoin("initialisating ", post));
	if (i == 3)
		return (ft_strjoin("processing ", post));
	if (i == 4)
		return (ft_strjoin("parsing ", post));
	if (i == 5)
		return (ft_strjoin("running ", post));
	if (i == 6)
		return (ft_strjoin("loading ", post));
	if (i == 7)
		return (ft_strjoin("extracting ", post));
	return ("yes");
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
	if (pre == NULL)
		pre = other_if(i, post);
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
	if (i == 2)
		s = ft_strjoin(s, " PERCENT");
	post = ft_strjoin(s, "\r");
	pre = NULL;
	if (i == 0)
		pre = ft_strjoin("Done", post);
	if (i == 1)
		pre = ft_strjoin("Allocating memory for ", post);
	if (i == 2)
		pre = ft_strjoin("Writing ... ", post);
	if (pre == NULL)
		pre = other_if(i, post);
	hello_screen(w);
	type_str(w, w->txthead, pre, 0x12FEA800);
	if (i == 2)
		type_str(w, dot, "Saving modif...", 0x12FEA800);
	else
		type_str(w, dot, "Loading game...", 0x12FEA800);
	img_update(w);
	free(post);
	if (pre != NULL)
		free(pre);
}
