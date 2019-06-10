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
	win->texture = SDL_CreateTextureFromSurface(win->renderer, win->surface);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_GetWindowSize(win->window, &win->w_win, &win->h_win);

	//SDL_BlitSurface(win->map_ui, NULL, win->surface, &win->dst2);

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
	t_lst	*tmp;

	tmp = win->lst;
	while (tmp->next)
	{

		line(win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);

		//draw_points(win, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	tmp = win->lst;
	while (tmp)
	{
		draw_points(win, tmp->x, tmp->y);
		tmp = tmp->next;
	}
	if (win->drawing == 1)
		ft_draw_line(win, win->x1, win->y1, win->x2, win->y2);
}

void		loop_play(t_win *win)
{
	int		close;
	t_lst	*tmp;

	tmp = NULL;
	close = 0;
	win->surface = SDL_CreateRGBSurface(0, WIN_X, WIN_Y, 32, 0, 0, 0, 0);
	while (42)
	{
		SDL_PollEvent(&win->event);
		sdl_event(win);
		if (win->left_click == 1 && win->mode == 0)
		{
			win->drawing = 1;
			if (win->lst == NULL)
				win->lst = lstnew(win->x1, win->y1, 0);
			else
				close = check_list(win, win->lst, win->x1, win->y1, win->sector);
		}
		if (win->left_click == 1 && win->mode == 1)
		{
			tmp = win->lst;
			while (tmp && win->moving == 0)
			{
				/*printf("%d x \n", tmp->x);
				printf("%d y \n", tmp->y);
				printf("%d x0 \n", win->x0);
				printf("%d y0 \n", win->y0);*/
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
			}
		}
		if (win->moving == 0)
			win->left_click = 0;
		clear_window(win);
		draw_grid(win);
		if (win->lst != NULL)
			draw_segments(win);
		print_game(win);
	}
}
