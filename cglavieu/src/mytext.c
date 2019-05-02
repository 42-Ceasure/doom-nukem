/*BIG42HEADER*/

#include "doom.h"

void		ft_putmychar(t_env *w, int i, int x, int y)
{
	int		c;
	int		ix;
	int		iy;

	ix = 0;
	iy = 0;
	if (ft_isdigit(w->txt.text[i]) == 1)
		c = (int)(w->txt.text[i] - 48);
	else if (ft_isalpha(w->txt.text[i]) == 1)
		c = (int)(ft_toupper(w->txt.text[i]) - 55);
	else
		c = 41;
	while (iy < w->ascii[c].h)
	{
		ix = 0;
		while (ix < w->ascii[c].w)
		{
			if (w->ascii[c].pix[iy * w->ascii[c].w + ix] != w->ascii[c].pix[0])
				w->pix[(iy + y) * WIDTH + (ix + x)] = w->txt.color;
			ix++;
		}
		iy++;
	}
}

void		type_w(t_env *w)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = w->txt.x;
	y = w->txt.y;
	while (w->txt.text[i])
	{
		ft_putmychar(w, i, x, y);
		x = x + w->ascii[0].w;
		i++;
	}
}

t_text		type_set(int x, int y, char *s, Uint32 color)
{
	t_text	txt;

	txt.x = x;
	txt.y = y;
	txt.text = s;
	txt.color = color;
	return (txt);
}

void		type_text(t_env *w, t_dot dot, char *s, Uint32 color)
{
	w->txt = type_set(dot.x, dot.y, s, color);
	type_w(w);
}
