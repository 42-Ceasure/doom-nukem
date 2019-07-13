/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   params.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 12:34:38 by abechet           #+#    #+#             */
/*   Updated: 2019/07/11 12:37:42 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		increase_value(t_win *win)
{
	if (win->param_index == 0)
	{
		if (win->hp_value < 1000)
			win->hp_value += 10;
	}
	if (win->param_index == 1)
	{
		if (win->gravity_value < 10)
			win->gravity_value++;
	}
	if (win->param_index == 2)
	{
		if (win->music_value < 5)
			win->music_value++;
	}
}

void		decrease_value(t_win *win)
{
	if (win->param_index == 0)
	{
		if (win->hp_value > 10)
			win->hp_value -= 10;
	}
	if (win->param_index == 1)
	{
		if (win->gravity_value > 0)
			win->gravity_value--;
	}
	if (win->param_index == 2)
	{
		if (win->music_value > 0)
			win->music_value--;
	}
}

void		param_text(t_win *win)
{
	char	*tmp;

	if (win->param_index == 0)
	{
		win->paramtxt = ft_strdup("HP");
		tmp = ft_itoa(win->hp_value);
		win->paramvaluetxt = ft_strdup(tmp);
	}
	if (win->param_index == 1)
	{
		// win->paramtxt = TTF_RenderText_Blended(win->police,
		// 	"Gravity", win->color_font_z);
		tmp = ft_itoa(win->gravity_value);
		// win->paramvaluetxt = TTF_RenderText_Blended(win->police,
		// 	tmp, win->color_font_z);
	}
	if (win->param_index == 2)
	{
		// win->paramtxt = TTF_RenderText_Blended(win->police,
		// 	"Music", win->color_font_z);
		tmp = ft_itoa(win->music_value);
		// win->paramvaluetxt = TTF_RenderText_Blended(win->police,
		// 	tmp, win->color_font_z);
	}
}

void	set_params(t_env *w, t_win *win)
{
	//printf("%d param index \n", win->param_index);
	t_dot dot;

	dot.x = 300;
	dot.y = 500;
	param_text(win);
	win->dst12.x = win->x2 + 30;
	win->dst12.y = win->y2 - 20;
	win->dst13.x = win->x2 + 30;
	win->dst13.y = win->y2 + 20;
	type_str(w, dot, win->paramtxt, 0xFF00FF);
	type_str(w, dot, win->paramvaluetxt, 0xFF00FF)
	// SDL_BlitSurface(win->paramtxt, NULL, win->surface, &win->dst12);
	// SDL_BlitSurface(win->paramvaluetxt, NULL, win->surface, &win->dst13);

}
