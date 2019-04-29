/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:02:56 by ochaar            #+#    #+#             */
/*   Updated: 2019/04/29 14:34:57 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

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
	w->ttf.texte = TTF_RenderText_Solid(w->ttf.police, "HP : ", w->ttf.color);
	w->ttf.texte2 = TTF_RenderText_Solid(w->ttf.police, "AMMO : ", w->ttf.color);
	TTF_CloseFont(w->ttf.police);
}