/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 17:28:53 by nvienot           #+#    #+#             */
/*   Updated: 2019/05/22 17:54:55 by nvienot          ###   ########.fr       */
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

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_KP_1])
	{
		win->mode = 0;
		win->drawing = 1;
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_KP_2])
	{
		win->mode = 1;
		win->drawing = 0;
	}

	if (win->event.type == SDL_KEYDOWN && win->keystate[SDL_SCANCODE_Z])
	{
		t_lst	*tmp;
		t_lst	*previous;

		tmp = win->lst;
		previous = win->lst;
		if (win->lst != NULL)
		{
			if (tmp->next == NULL)
			{
				win->x1 = tmp->x;
				win->y1 = tmp->y;
				free (tmp);
				tmp = NULL;
				win->lst = NULL;
				return ;
			}
			if (tmp->next->next == NULL)
			{
				win->x1 = tmp->x;
				win->y1 = tmp->y;
			}
			while (previous->next->next)
			{
				previous = previous->next;
				win->x1 = previous->x;
				win->y1 = previous->y;
			}
			while (tmp->next)
				tmp = tmp->next;
			previous->next = NULL;
			free (tmp);
			tmp = NULL;
		}
	}
}

static void	sdl_event_mouse(t_win *win)
{
	int		x;
	int		y;
	int		sector;
	int		close;

	x = 0;
	y = 0;
	sector = 0;
	close = 0;
	if (SDL_GetMouseState(&x, &y) == 3)
	{
		printf("test\n");
		win->drawing = 0;
	}
	if ((SDL_GetMouseState(&x, &y) == 1) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (win->mode == 0)
		{
			win->x1 = ft_round(x);
			win->y1 = ft_round(y);
		}
		win->x0 = ft_round(x);
		win->y0 = ft_round(y);
		win->left_click = 1;
		if (win->left_click == 1 && win->mode == 1 && win->moving == 1)
		{
			win->moving = 0;
			win->x0 = -1;
			win->y0 = -1;
			//if (
		}
	}
	SDL_GetMouseState(&x, &y);
	win->x2 = ft_round(x);
	win->y2 = ft_round(y);
}

void		sdl_event(t_win *win)
{
	//SDL_PollEvent(&win->event);
	sdl_event_key(win);
	sdl_event_mouse(win);
}
