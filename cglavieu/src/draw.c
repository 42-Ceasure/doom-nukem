//

#include "doom-nukem.h"

Uint32		color(Uint32 color1)
{
	Uint8	a;
	Uint8	ro;
	Uint8	g;
	Uint8	b;

	a = (color1 & 0xFF000000) >> 24;
	ro = (color1 & 0x00FF0000) >> 16;
	g = (color1 & 0x0000FF00) >> 8;
	b = (color1 & 0x000000FF);
	return ((((((a << 8) + ro) << 8) + g) << 8) + b);
}

void	clean_render(t_env *w, Uint32 color)
{
	int x;

	x = 0;
	while (x < HEIGHT * WIDTH - 1)
	{
		w->pix[x] = color;
		x++;
	}

}

void	set_txtr_pix(t_env *w, int x, int y, Uint32 color)
{
	if (y >= 0 && y < HEIGHT && x >= 0 && x < WIDTH)
		w->pix[y * WIDTH + x] = color;
}

void	set_wall(t_env *w, t_work work, int x)
{
	int		y;

	y = 0;
		while ((y < ((HEIGHT - work.height) / 2)) && (y < HEIGHT))
		{
			w->pix[y * WIDTH + x] = 0x121E7FCB;
			y++;
		}
		while (y < (((HEIGHT + work.height) / 2)) && (y < HEIGHT))
		{
			w->pix[y * WIDTH + x] = 0x12FFFFFF;
			y++;
		}
		while (y < HEIGHT)
		{
			w->pix[y * WIDTH + x] = 0x124E3D28;
			y++;
		}
}

void vline(int x, int y1, int y2, t_env *w, t_color color)
{
	Uint32 *pix = (Uint32 *)w->pix;
	int y;

	y1 = vMid(y1, 0, HEIGHT-1);
	y2 = vMid(y2, 0, HEIGHT-1);
	y = y1 + 1;
	if(y2 == y1)
		pix[y1*WIDTH+x] = color.middle;
	else if(y2 > y1)
	{
		pix[y1*WIDTH+x] = color.top;
		while (y<y2)
		{
			pix[y*WIDTH+x] = color.middle;
			y++;
		}
		pix[y2*WIDTH+x] = color.bottom;
	}
}

void draw(t_env *w, t_map m)
{
	double x1;
	double y1;
	double x2;
	double y2;
	double px;
	double py;
	double pa;
	t_coor p1;
	t_coor p2;

	x1 = m.sector[0].dot[0].x + WIDTH / 2;
	y1 = m.sector[0].dot[0].y + HEIGHT / 2;
	x2 = m.sector[0].dot[1].x + WIDTH / 2;
	y2 = m.sector[0].dot[1].y + HEIGHT / 2;
	px = m.player.coor.x + WIDTH / 2;
	py = m.player.coor.y + HEIGHT / 2;
	pa = m.player.angle * M_PI / 180;
	p1.x = x1;
	p1.y = y1;
	p2.x = x2;
	p2.y = y2;

	set_txtr_pix(w, px, py, 0x12FFFFFF);
	vect_ab(p1, p2, w, 0x121E7FCB);
}

































