/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:28:53 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 17:54:55 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static int	ft_round(int n)
{
	int a;
	int b;
	int tmp;

	tmp = n;
	a = 0;
	b = 0;
	if (n == 0)
		return (0);
	while (n % 10 > 0)
	{
		n = n - 1;
		a++;
	}
	while (tmp % 10 > 0)
	{
		tmp = tmp + 1;
		b++;
	}
	if (a < b)
		return (n);
	return (tmp);
}


static void	sdl_event_key(t_win *win)
{
	win->keystate = (Uint8 *)SDL_GetKeyboardState(0);
	if (win->event.type == SDL_QUIT
		|| win->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		clear_n_exit(win, 0);

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_P])
	{
		if (win->lstlst)
			recursive_check(win);
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_L])
	{
		if (win->triangles)
			win->drawtriangles = 1;
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_F5])
	{
		if (win->lstlst)
			save_map(win);
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_I])
	{
		test(win);
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_K])
	{
		if (win->lstlst)
			check_neighbour(win);
	}

	/*if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_H])
	{
		win->helptxt = TTF_RenderText_Blended(win->police,
			"test", win->color_font_r);
		SDL_BlitSurface(win->helptxt, NULL, win->surface, &win->dst6);
	}*/
}

static void	sdl_event_mouse(t_win *win)
{
	int			x;
	int			y;
	int			sector;
	int			close;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	x = 0;
	y = 0;
	sector = 0;
	close = 0;
	tmp = win->lst;
	tmp2 = win->lstlst;

	if (win->event.type == SDL_MOUSEWHEEL)
	{
		win->changemode = 1;
		if (win->moving == 0)
		{
			if (win->event.wheel.y > 0)
				win->mode -= 1;
			if (win->event.wheel.y < 0)
				win->mode += 1;
		}

		if (win->mode > 3)
			win->mode = 0;
		if (win->mode < 0)
			win->mode = 3;

		if (win->mode == 0)
		{
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			if (tmp2)
			{
				while (tmp2->next)
					tmp2 = tmp2->next;
				if (tmp2->closed == 0)
					win->drawing = 1;
			}
			//win->drawing = 0;
			//SDL_FreeSurface(win->helptxt);
			win->helptxt = TTF_RenderText_Blended(win->police,
				"Drawing Mode", win->color_font_r);
		}

		if (win->mode == 1)
		{
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			win->drawing = 0;
			//SDL_FreeSurface(win->helptxt);
			win->helptxt = TTF_RenderText_Blended(win->police,
				"Moving Mode", win->color_font_r);
		}

		if (win->mode == 2)
		{
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			win->drawing = 0;
			win->helptxt = TTF_RenderText_Blended(win->police,
				"Placing Mode", win->color_font_r);
		}

		if (win->mode == 3)
		{
			win->cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_NO);
			win->drawing = 0;
			win->helptxt = TTF_RenderText_Blended(win->police,
				"Delete Mode", win->color_font_r);
		}
	}

	if (win->event.button.button == SDL_BUTTON_RIGHT
		&& win->event.type == SDL_MOUSEBUTTONUP && win->moving == 0)
	{
		if (win->mode == 0)
			undo(win);
		if (win->mode == 2)
			pick_asset(win);
	}

	if (win->event.button.button == SDL_BUTTON_LEFT
		&& win->event.type == SDL_MOUSEBUTTONUP)
	{
		SDL_GetMouseState(&x, &y);
		if (win->mode == 0)
		{
			win->x1 = ft_round(x);
			win->y1 = ft_round(y);
			win->just_close = 0;
		}
		win->x0 = ft_round(x);
		win->y0 = ft_round(y);
		win->left_click = 1;
		if (win->left_click == 1 && win->mode == 1 && (win->moving == 1 || win->moving == 2))
		{
			win->moving = 0;
			win->tmp = NULL;
			win->tmpasset = NULL;
			win->x0 = -1;
			win->y0 = -1;
			if (win->lst)
			{
				while (tmp->next)
					tmp = tmp->next;
				win->x1 = tmp->x;
				win->y1 = tmp->y;
			}
		}
	}
	SDL_GetMouseState(&x, &y);
	win->x2 = ft_round(x);
	win->y2 = ft_round(y);
}

void		sdl_event(t_win *win)
{
	sdl_event_key(win);
	sdl_event_mouse(win);
}
