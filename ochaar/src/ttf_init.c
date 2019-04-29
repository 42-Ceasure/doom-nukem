/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:02:56 by ochaar            #+#    #+#             */
/*   Updated: 2019/04/29 16:38:35 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

SDL_Color		init_sdl_color(int r, int g, int b)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return(color);
}

SDL_Rect		init_sdl_rect(int x, int y, int w, int h)
{
	SDL_Rect	rect;

	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
	return (rect);
}

void			ttf_init(t_env *w)
{
	TTF_Init();
	w->ttf.police = TTF_OpenFont("angelina.ttf", 65);
	w->ttf.color[0] = init_sdl_color(255,0,0);
	w->ttf.texte[0] = TTF_RenderText_Solid(w->ttf.police, "HP : ", w->ttf.color[0]);
	w->ttf.texte[1] = TTF_RenderText_Solid(w->ttf.police, "AMMO : ", w->ttf.color[1]);
	w->ttf.texte[2] = TTF_RenderText_Solid(w->ttf.police, ft_itoa(100), w->ttf.color[0]);
	w->ttf.size[0] = init_sdl_rect(0, 0, 100, 50);
	w->ttf.size[1] = init_sdl_rect(0, HEIGHT - 60, 150, 80);
	w->ttf.size[2] = init_sdl_rect(100, 0, 100, 50);
	TTF_CloseFont(w->ttf.police);
}