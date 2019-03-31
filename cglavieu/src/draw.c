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
	t_player player;
	t_coor p1;
	t_coor p2;
	t_coor tp1;
	t_coor tp2;

	p1.x = m.sector[0].dot[0].x;
	p1.y = m.sector[0].dot[0].y;
	p2.x = m.sector[0].dot[1].x;
	p2.y = m.sector[0].dot[1].y;
	player = m.player;

	tp1.x = p1.x - player.x;
	tp1.y = p1.y - player.y;
	tp2.x = p2.x - player.x;
	tp2.y = p2.y - player.y;
	tp1.z = tp1.x * cos(player.angle) + tp1.y * sin(player.angle);
	tp2.z = tp2.x * cos(player.angle) + tp2.y * sin(player.angle);
	tp1.x = tp1.x * sin(player.angle) - tp1.y * cos(player.angle);
	tp2.x = tp2.x * sin(player.angle) - tp2.y * cos(player.angle);

	set_txtr_pix(w, player.coor.x, player.coor.y, 0x12FFFFFF);
	vect_ab(p1, p2, w, 0x121E7FCB);
	player.move_speed.x = cos(player.angle) * 5 + player.coor.x;
	player.move_speed.y = sin(player.angle) * 5 + player.coor.y;
	vect_ab(player.coor, player.move_speed, w, 0x124E3D28);
}

































