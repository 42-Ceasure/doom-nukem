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
	if (win->changemode)
	{
		SDL_SetCursor(win->cursor);
		SDL_BlitSurface(win->helptxt, NULL, win->surface, &win->dst);
	}
	if (win->mode == 4 && win->texture_overed_sector != -1)
		SDL_BlitSurface(win->texturetxt, NULL, win->surface, &win->dst11);
	win->texture = SDL_CreateTextureFromSurface(win->renderer, win->surface);
	SDL_SetRenderTarget(win->renderer, NULL);
	SDL_GetWindowSize(win->window, &win->w_win, &win->h_win);
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
			if (win->mode == 3 && tmp2->sector == win->overed_sector)
					win->color = 0xFF0000;
			if (win->mode == 4 && tmp2->sector == win->texture_overed_sector)
					win->color = 0x00BFFF;
			else
			{
				if (tmp2->closed)
					win->color = 0x00FF00;
				else
					win->color = 0x20B2AA;
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
	win->texture_overed_sector = -1;
}

void		draw_triangulate(t_win *win)
{
	t_lst		*tmp;
	t_lstlst	*tmp2;

	tmp2 = win->triangles;
	win->color = 0xFF00FF;
	while (tmp2)
	{
		tmp = tmp2->head;
		while (tmp)
		{
			if (tmp->next)
			{
				line(win, tmp->x, tmp->y, tmp->next->x, tmp->next->y);
				tmp = tmp->next;
			}
			else
				break;
		}
		if (tmp)
			line(win, tmp->x, tmp->y, tmp2->head->x, tmp2->head->y);
		tmp2 = tmp2->next;
	}
}

void		draw_asset_points(t_win *win, int i, int j, int color)
{
	put_pixel_to_surface(win->surface, i, j, color);
	put_pixel_to_surface(win->surface, i + 1, j, color);
	put_pixel_to_surface(win->surface, i - 1, j, color);
	put_pixel_to_surface(win->surface, i + 2, j, color);
	put_pixel_to_surface(win->surface, i - 2, j, color);

	put_pixel_to_surface(win->surface, i, j - 1, color);
	put_pixel_to_surface(win->surface, i + 1, j - 1, color);
	put_pixel_to_surface(win->surface, i - 1, j - 1, color);
	put_pixel_to_surface(win->surface, i - 2, j - 2, color);
	put_pixel_to_surface(win->surface, i + 2, j - 2, color);

	put_pixel_to_surface(win->surface, i, j + 1, color);
	put_pixel_to_surface(win->surface, i + 1, j + 1, color);
	put_pixel_to_surface(win->surface, i - 1, j + 1, color);
	put_pixel_to_surface(win->surface, i + 2, j + 2, color);
	put_pixel_to_surface(win->surface, i - 2, j + 2, color);
}

void		draw_assets(t_win *win)
{
	t_lstasset	*tmp;
	int			color;

	color = 707070;
	tmp = win->lstasset;
	while (tmp)
	{
		if (tmp->asset_type == 0)
			color = 707070;
		if (tmp->asset_type == 1)
			color = 0xC0C0C0;
		if (tmp->asset_type == 2)
			color = 0x800000;
		if (tmp->asset_type == 3)
			color = 0xFF0000;
		if (tmp->asset_type == 4)
			color = 0xFFFF00;
		if (tmp->asset_type == 5)
			color = 0xD3D3D3;
		if (tmp->asset_type == 6)
			color = 0xFF69B4;
		if (tmp->asset_type == 7)
			color = 0xBDB76B;
		if (tmp->asset_type == 8)
			color = 0xF5F5F5;
		draw_asset_points(win, tmp->x, tmp->y, color);
		tmp = tmp->next;
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
	t_lstasset	*tmp3;

	tmp = NULL;
	tmp2 = NULL;
	tmp3 = NULL;
	closed = 0;

	if (win->left_click)
	{
		win->changemode = 0;
		if (win->triangles)
			free_triangles(win);
	}

	if (win->mode == 3)
		overing(win);

	if (win->left_click && win->mode == 3)
	{
		delete_sector(win);
		delete_asset(win);
	}

	if (win->left_click && win->mode == 0)
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
		tmp3 = win->lstasset;

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

		while (tmp3 && win->moving == 0)
		{
			if (tmp3->x == win->x0 && tmp3->y == win->y0)
			{
				win->tmpasset = tmp3;
				win->moving = 2;
			}
			else
				tmp3 = tmp3->next;
		}
		if (win->moving == 2)
		{
			if (win->tmpasset)
			{
				win->tmpasset->x = win->x2;
				win->tmpasset->y = win->y2;
			}
		}
	}
	if (win->left_click == 1 && win->mode == 2)
	{
		win->place = 1;
	}

	if (win->left_click == 1 && win->mode == 4)
	{
		win->put_texture = 1;
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

		//if (win->lstlst && win->just_close)
		//	recursive_check(win);

		if (win->triangles)
			draw_triangulate(win);
		//free_triangles(win);
		if (win->lstlst)
			draw_segments(win);
		if (win->lstasset)
			draw_assets(win);
		mode(win);
		if (win->mode != 2)
			asset_overing(win);
		print_game(win);
	}
}
