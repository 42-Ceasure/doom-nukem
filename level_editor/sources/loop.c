/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 20:15:25 by abechet           #+#    #+#             */
/*   Updated: 2019/05/22 17:47:31 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

int			print_game(t_win *win)
{
	//SDL_BlitSurface(win->map_ui, &win->dst2, win->surface, NULL);

	SDL_SetCursor(win->cursor);

	SDL_BlitSurface(win->helptxt, NULL, win->surface, &win->dst);

	win->texture = SDL_CreateTextureFromSurface(win->renderer, win->surface);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_GetWindowSize(win->window, &win->w_win, &win->h_win);

	//set_window(win);
	if ((SDL_RenderCopy(win->renderer, win->texture, NULL, &win->dst2)) < 0)
		clear_n_exit(win, 17);
	SDL_RenderPresent(win->renderer);
	SDL_DestroyTexture(win->texture);

	//SDL_SetCursor(win->cursor);
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
			if (win->mode == 3 && tmp2->sector == win->overed_sector)
					win->color = 100100100;
			else
			{
				if (tmp2->closed)
					win->color = 1242520;
				else
					win->color = 255255255;
			}
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
	win->overed_sector = -1;
}




void		draw_triangulate(t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;


	tmp2 = win->triangles;
	//printf("%d \n ", len_listlist(win->triangles));
	//printf("%d \n ", len_list(win->triangles->head));
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp->next)
		{
			win->color = 100100100;
			/*printf("%d\n", tmp->x);
			printf("%d\n", tmp->x);
			printf("%d\n", tmp->next->x);
			printf("%d\n", tmp->next->y);*/
			line(win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);


			tmp = tmp->next;
		}
		if (tmp2)
		{
			if (tmp)
				line(win, tmp->x, tmp->y, tmp2->head->x, tmp2->head->y);
		}
		/*tmp = tmp2->head;
		while (tmp)
		{
			draw_points(win, tmp->x, tmp->y);
			tmp = tmp->next;
		}*/
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

	if (win->mode == 3)
		delete_sector(win);

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



/*		if (win->lstlst->closed == 1)
		{
			t_dot	p0;
			t_dot	p1;
			t_dot	p2;
			t_dot	m;

			tmp2 = win->lstlst;
			tmp = tmp2->head;

			p0.x = tmp->x;
			p0.y = tmp->y;
			p1.x = tmp->next->x;
			p1.y = tmp->next->y;
			p2.x = tmp->next->next->x;
			p2.y = tmp->next->next->y;
			m.x = win->x2;
			m.y = win->y2;
			if (point_in_triangle(p0, p1, p2, m) == 1)
				printf("ok\n");
		}*/



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
		if (win->lstlst)
			draw_segments(win);
		if (win->triangles)
			draw_triangulate(win);
		mode(win);
		print_game(win);
	}
}
