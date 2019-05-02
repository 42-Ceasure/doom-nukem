/*BIG42HEADER*/

#include "doom.h"

void		ft_printmychar(t_env *w, int x, int y, int c)
{
	int ix;
	int iy;

	iy = 0;
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

void		ft_putmychar(t_env *w, int i, int *xmain, int *ymain)
{
	int		print;
	int		c;
	int		x;
	int		y;

	print = 0;
	x = *xmain;
	y = *ymain;
	if (w->txt.text[i] == '\n')
	{
		print = 1;
		*xmain = w->txt.x;
		*ymain = *ymain + w->ascii[0].h + 5;
	}
	else if (w->txt.text[i] == '\t')
	{
		c = 41;
		ft_printmychar(w, x, y, c);
		ft_printmychar(w, x, y, c);
	}
	else if (w->txt.text[i] == ',')
		c = 36;
	else if (w->txt.text[i] == ':')
		c = 37;
	else if (w->txt.text[i] == '!')
		c = 38;
	else if (w->txt.text[i] == '?')
		c = 39;
	else if (w->txt.text[i] == '.')
		c = 40;
	else if (w->txt.text[i] == ' ')
		c = 41;
	else if (ft_isdigit(w->txt.text[i]) == 1)
		c = (int)(w->txt.text[i] - 48);
	else if (ft_isalpha(w->txt.text[i]) == 1)
		c = (int)(ft_toupper(w->txt.text[i]) - 55);
	else
		print = 1;
	if (print == 0)
		ft_printmychar(w, x, y, c);
	*xmain = *xmain + w->ascii[0].w;
}

void		type_s(t_env *w)
{
	int		i;
	int		x;
	int		y;

	i = 0;
	x = w->txt.x;
	y = w->txt.y;
	while (w->txt.text[i])
	{
		ft_putmychar(w, i, &x, &y);
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

void		type_str(t_env *w, t_dot dot, char *s, Uint32 color)
{
	w->txt = type_set(dot.x, dot.y, s, color);
	type_s(w);
}
