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
			if (x + ox < WIDTH)
			{
				if (y + oy < HEIGHT)
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
			if (x + ox < WIDTH)
			{
				if (y + oy < HEIGHT)
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

// void		safe_texte_to_screen(t_env *w, t_texture texture, int x, int y)
// {
	
// }