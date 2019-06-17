/*BIG42HEADER*/

#include "doom.h"

void		safe_texture_to_screen(t_env *w, t_texture texture, int x, int y)
{
	int		i;
	int		tmpix;
	int		ox;
	int		oy;

	i = y * WIDTH + x;
	ox = 0;
	oy = 0;
	while (ox * oy < texture.len && i < WIDTH * HEIGHT)
	{
		ox = 0;
		while (ox < texture.w)
		{
			if (x + ox >= 0 && x + ox < WIDTH)
			{
				if (y + oy >= 0 && y + oy < HEIGHT)
				{
					tmpix = oy * texture.w + ox;
					if (texture.pix[tmpix] != 0xFF00FF00)
						w->pix[(y + oy) * WIDTH + (x + ox)] = texture.pix[tmpix];
				}
			}
			i++;
			ox++;
		}
		if (w->sequential_frame == 1 && (oy % 2 == 0))
			img_update(w);
		oy++;
	}
}

void		safe_sprite_to_screen(t_env *w, t_sprite sprite, int x, int y)
{
	int		i;
	int		tmpix;
	int		ox;
	int		oy;

	i = y * WIDTH + x;
	ox = 0;
	oy = 0;
	while (ox * oy < sprite.len && i < WIDTH * HEIGHT)
	{
		ox = 0;
		while (ox < sprite.w)
		{
			if (x + ox >= 0 && x + ox < WIDTH)
			{
				if (y + oy >= 0 && y + oy < HEIGHT)
				{
					tmpix = oy * sprite.w + ox;
					if (sprite.pix[tmpix] != 0xFF00FF00)
						w->pix[(y + oy) * WIDTH + (x + ox)] = sprite.pix[tmpix];
				}
			}
			i++;
			ox++;
		}
		if (w->sequential_frame == 1 && (oy % 2 == 0))
			img_update(w);
		oy++;
	}
}

void		safe_char_to_screen(t_env *w, t_texture texture, int x, int y)
{
	int		i;
	int		tmpix;
	int		ox;
	int		oy;

	i = y * WIDTH + x;
	ox = 0;
	oy = 0;
	while (ox * oy < texture.len && i < WIDTH * HEIGHT)
	{
		ox = 0;
		while (ox < texture.w)
		{
			if (x + ox >= 0 && x + ox < WIDTH)
			{
				if (y + oy >= 0 && y + oy < HEIGHT)
				{
					tmpix = oy * texture.w + ox;
					if (texture.pix[tmpix] != texture.pix[0])
						w->pix[(y + oy) * WIDTH + (x + ox)] = w->txt.color;
				}
			}
			i++;
			ox++;
		}
		if (w->sequential_frame == 1 && (oy % 6 == 0))
				img_update(w);
		oy++;
	}
}

int		final_texture_to_screen(t_env *w, t_sprite texture, int x, int y, int width, int height)
{
	double 	step_x_tex;
	double 	step_y_tex;
	double	x_tex;
	double	y_tex;
	int 	maxx;
	int		maxy;
	Uint32	tmpix;

	// test pb HEIGHT WIDTH calculated
	// if (WIDTH <= 0 || HEIGHT <= 0)
	// 	return (0);
	// if (WIDTH > BASEWIDTH || HEIGHT > BASEHEIGHT)
	// 	return (0);
	// if (texture.h > 5000 || texture.w > 5000)
	// {
	// 	// printf("333333333\n");
	// 	return (0);
	// }
	// No bug with texture not loaded but trying with protection
	if (texture.pix == NULL || w->pix == NULL || texture.h <= 0 || texture.w <= 0 || texture.len <= 0)
		return (0);
	// Initializing steps
	step_x_tex = 0;
	step_y_tex = 0;
	// scalling depending on args (0,0 = no scale, X,0 or 0,X -> scalling with ratio on arg, X,X -> taking the new size given)
	if (width == 0 && height == 0)
	{
		width = texture.w;
		height = texture.h;
	}
	else if (width == 0 || height == 0)
	{
		if (width == 0)
			width = (int)(height * texture.w / texture.h);
		else if (height == 0)
			height = (int)(width * texture.h / texture.w);
	}
	// Calculating steps
	step_x_tex = (double)texture.w / (double)width;
	step_y_tex = (double)texture.h / (double)height;
	// Calculating our max on x and y (start point given on x and y + size of texture + not writing if <0 >Height/WIDTH)
	// maxx = vmid((width + x), 0, WIDTH);
	maxx = width + x;
	maxy = height + y;
	// if (maxx > WIDTH)
	// 	maxx = WIDTH;
	// if (maxy > HEIGHT)
	// 	maxy = HEIGHT;
	// maxy = vmid((height + y), 0, HEIGHT);
	// if (x < 0)
	// 	x = 0;
	// if (y < 0)
	// 	y = 0;
	
	// Initializing our x ans y for tex
	y_tex = 0;
	x_tex = 0;
	// trying to get error on steps
	if (step_x_tex <= 0 || step_y_tex <= 0)
	{
		// printf("4444444444\n");
		return (0);
	}
	// boucle hauteur + trying with test on max len
	while (y < maxy && (int)x_tex * (int)y_tex < texture.len)
	{
		// reset xtex
		x_tex = 0;
		// boucle largeur + trying with test on max len
		while (x < maxx && (int)x_tex * (int)y_tex < texture.len)
		{
			// protection on
			if (y >= 0 && y < HEIGHT && (int)y_tex >= 0 && (int)y_tex < texture.h)
			{
				// protection on
				if (x >= 0 && x < WIDTH && (int)x_tex >= 0 && (int)x_tex < texture.w)
				{
					tmpix = (int)y_tex * texture.w + (int)x_tex;
					if (texture.pix[tmpix] != 0xFF00FF00)
						w->pix[y * WIDTH + x] = texture.pix[tmpix];
				}
			}
			// adding step on xtex
			x_tex += step_x_tex;
			x++;
		}
		// decrementing x by our width
		x -= width;
		// adding step on ytex
		y_tex += step_y_tex;
		y++;
	}
	return (1);
}