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
			ox++;
		}
		oy++;
	}
}

void		safe_sprite_to_screen(t_env *w, t_sprite sprite)
{
	int		i;
	int		tmpix;
	int		ox;
	int		oy;

	i = sprite.sy * WIDTH + sprite.sx;
	ox = 0;
	oy = 0;
	while (ox * oy < sprite.len && i < WIDTH * HEIGHT)
	{
		ox = 0;
		while (ox < sprite.w)
		{
			if (sprite.sx + ox < WIDTH)
			{
				if (sprite.sy + oy < HEIGHT)
				{
					tmpix = oy * sprite.w + ox;
					if (sprite.pix[tmpix] != 0xFF00FF00)
						w->pix[(sprite.sy + oy) * WIDTH + (sprite.sx + ox)] = sprite.pix[tmpix];
				}
			}
			ox++;
		}
		oy++;
	}
}

// void		safe_texte_to_screen(t_env *w, t_texture texture, int x, int y)
// {
	
// }
