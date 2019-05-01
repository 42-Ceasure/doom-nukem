/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ttf_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 13:02:56 by ochaar            #+#    #+#             */
/*   Updated: 2019/05/01 16:55:05 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void			update_ttf_txtr3(t_env *w, t_map *m)
{
	SDL_FreeSurface(w->ttf.texte[3]);
	SDL_DestroyTexture(w->ttf.txtr[3]);
	if (!(w->ttf.texte[3] = TTF_RenderText_Solid(w->ttf.police,
		ft_itoa(m->weap[PH].actu_ammo), w->ttf.color[1])))
		set_error(w, m, 9, ft_strdup("No texte"));
	if (!(w->ttf.txtr[3] = SDL_CreateTextureFromSurface(w->rdr,
		w->ttf.texte[3])))
		set_error(w, m, 9, ft_strdup("No Texture"));
}

SDL_Color		init_sdl_color(int r, int g, int b)
{
	SDL_Color	color;

	color.r = r;
	color.g = g;
	color.b = b;
	return (color);
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

void			ttf_protect(t_env *w, t_map *m)
{
	if (!(w->ttf.texte[0] = TTF_RenderText_Solid(w->ttf.police,
		"HP : ", w->ttf.color[0])))
		set_error(w, m, 9, ft_strdup("No texte"));
	if (!(w->ttf.texte[1] = TTF_RenderText_Solid(w->ttf.police,
		"AMMO : ", w->ttf.color[1])))
		set_error(w, m, 9, ft_strdup("No texte"));
	if (!(w->ttf.texte[2] = TTF_RenderText_Solid(w->ttf.police,
		ft_itoa(100), w->ttf.color[0])))
		set_error(w, m, 9, ft_strdup("No texte"));
	if (!(w->ttf.texte[3] = TTF_RenderText_Solid(w->ttf.police,
		ft_itoa(m->weap[PH].ammo), w->ttf.color[1])))
		set_error(w, m, 9, ft_strdup("No texte"));
	if (!(w->ttf.txtr[0] = SDL_CreateTextureFromSurface(w->rdr,
		w->ttf.texte[0])))
		set_error(w, m, 9, ft_strdup("No Texture"));
	if (!(w->ttf.txtr[1] = SDL_CreateTextureFromSurface(w->rdr,
		w->ttf.texte[1])))
		set_error(w, m, 9, ft_strdup("No Texture"));
	if (!(w->ttf.txtr[2] = SDL_CreateTextureFromSurface(w->rdr,
		w->ttf.texte[2])))
		set_error(w, m, 9, ft_strdup("No Texture"));
	if (!(w->ttf.txtr[3] = SDL_CreateTextureFromSurface(w->rdr,
		w->ttf.texte[3])))
		set_error(w, m, 9, ft_strdup("No Texture"));
}

int				ttf_init(t_env *w, t_map *m)
{
	TTF_Init();
	if (!(w->ttf.police = TTF_OpenFont("arial.ttf", 95)))
		return (-1);
	w->ttf.color[0] = init_sdl_color(255, 0, 0);
	ttf_protect(w, m);
	w->ttf.size[0] = init_sdl_rect(0, 0, 100, 50);
	w->ttf.size[1] = init_sdl_rect(0, HEIGHT - 70, 150, 80);
	w->ttf.size[2] = init_sdl_rect(100, 0, 100, 50);
	w->ttf.size[3] = init_sdl_rect(150, HEIGHT - 70, 100, 80);
	return (0);
}
