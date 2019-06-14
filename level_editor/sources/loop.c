/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvienot <nvienot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:15:25 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 17:47:31 by nvienot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			print_game(t_win *win)
{
	//SDL_BlitSurface(win->map_ui, &win->dst2, win->surface, NULL);

	SDL_BlitSurface(win->helptxt, NULL, win->surface, &win->dst);

	win->texture = SDL_CreateTextureFromSurface(win->renderer, win->surface);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_GetWindowSize(win->window, &win->w_win, &win->h_win);

	//set_window(win);
	if ((SDL_RenderCopy(win->renderer, win->texture, NULL, &win->dst2)) < 0)
		clear_n_exit(win, 17);
	SDL_RenderPresent(win->renderer);
	SDL_DestroyTexture(win->texture);
	return (0);
}

void		clear_window(t_win *win)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (j < WIN_Y)
	{
		i = 0;
		while (i < WIN_X)
		{
			put_pixel_to_surface(win->surface, i, j, 000);
			i++;
		}
		j++;
	}
}

void		draw_points(t_win *win, int i, int j)
{
	put_pixel_to_surface(win->surface, i, j, 250240230);
	put_pixel_to_surface(win->surface, i + 1, j, 250240230);
	put_pixel_to_surface(win->surface, i - 1, j, 250240230);

	put_pixel_to_surface(win->surface, i, j - 1, 250240230);
	put_pixel_to_surface(win->surface, i + 1, j - 1, 250240230);
	put_pixel_to_surface(win->surface, i - 1, j - 1, 250240230);

	put_pixel_to_surface(win->surface, i, j + 1, 250240230);
	put_pixel_to_surface(win->surface, i + 1, j + 1, 250240230);
	put_pixel_to_surface(win->surface, i - 1, j + 1, 250240230);
}


void		draw_segments(t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;


	tmp2 = win->lstlst;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp->next)
		{
			line(win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);
			tmp = tmp->next;
		}
		tmp = tmp2->head;
		while (tmp)
		{
			draw_points(win, tmp->x, tmp->y);
			tmp = tmp->next;
		}
		if (win->drawing == 1)
			ft_draw_line(win, win->x1, win->y1, win->x2, win->y2);
		tmp2 = tmp2->next;
	}
}

void		last_is_first(t_lst *lst)
{
	t_lst	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->x = lst->x;
	tmp->y = lst->y;
}


void		on_click(t_win *win)
{
	int			closed;
	t_lst		*tmp;
	t_lstlst	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	closed = 0;
	if (win->left_click == 1 && win->mode == 0)
	{

		if (win->lstlst == NULL)
			win->lstlst = lstlstnew(win);

		if (win->sector == win->link)
		{
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->next = lstlstnew(win);
		}

		win->drawing = 1;
		if (win->lst == NULL)
		{
			win->lst = lstnew(win->x1, win->y1, win->sector);
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->head = win->lst;
		}
		else
			closed = check_list(win, win->lst, win->x1, win->y1);
		if (closed)
		{
			tmp2 = win->lstlst;
			while (tmp2->next)
				tmp2 = tmp2->next;
			tmp2->closed = 1;
		}
	}
	if (win->left_click == 1 && win->mode == 1)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp && win->moving == 0)
			{
				if (tmp->x == win->x0 && tmp->y == win->y0)
				{
					win->tmp = tmp;
					win->moving = 1;
				}
				else
					tmp = tmp->next;
			}
			if (win->moving == 1)
			{
				win->tmp->x = win->x2;
				win->tmp->y = win->y2;
				if (tmp2->closed == 1)
					last_is_first(tmp2->head);
			}
			tmp2 = tmp2->next;
		}
	}
	if (win->moving == 0)
		win->left_click = 0;
}

void		loop_play(t_win *win)
{
	win->surface = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0, 0, 0, 0);
	while (42)
	{
		SDL_WaitEvent(&win->event);
		sdl_event(win);
		on_click(win);
		clear_window(win);
		draw_grid(win);
		if (win->lstlst != NULL)
			draw_segments(win);
		print_game(win);
	}
}
