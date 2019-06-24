/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/20 14:19:05 by abechet           #+#    #+#             */
/*   Updated: 2019/06/20 14:19:23 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

/*void		safe_texture_to_screen(t_env *w, t_texture texture, int x, int y)
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
}*/
