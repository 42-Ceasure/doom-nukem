/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_mode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 12:39:03 by abechet           #+#    #+#             */
/*   Updated: 2019/07/09 12:39:21 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		change_texture_index(t_env *w, t_win *win)
{
	if (win->txtr_input_type == 1 || win->txtr_input_type == 2)
	{
		if (win->texture_index < 45)
			win->texture_index += 1;
		if (win->hud_box < 4)
			win->hud_box++;
	}
	if (win->txtr_input_type == 3)
	{
		if (win->texture_index > 0)
			win->texture_index -= 1;
		if (win->hud_box > 0)
			win->hud_box--;
	}

	if (win->hud_box == 0)
	{
		win->slot0 = w->texturing[win->texture_index];
		win->slot1 = w->texturing[win->texture_index +1];
		win->slot2 = w->texturing[win->texture_index +2];
		win->slot3 = w->texturing[win->texture_index +3];
		win->slot4 = w->texturing[win->texture_index +4];
	}
	if (win->hud_box == 1)
	{
		win->slot0 = w->texturing[win->texture_index -1];
		win->slot1 = w->texturing[win->texture_index];
		win->slot2 = w->texturing[win->texture_index +1];
		win->slot3 = w->texturing[win->texture_index +2];
		win->slot4 = w->texturing[win->texture_index +3];
	}
	if (win->hud_box == 2)
	{
		win->slot0 = w->texturing[win->texture_index -2];
		win->slot1 = w->texturing[win->texture_index -1];
		win->slot2 = w->texturing[win->texture_index];
		win->slot3 = w->texturing[win->texture_index +1];
		win->slot4 = w->texturing[win->texture_index +2];
	}
	if (win->hud_box == 3)
	{
		win->slot0 = w->texturing[win->texture_index -3];
		win->slot1 = w->texturing[win->texture_index -2];
		win->slot2 = w->texturing[win->texture_index -1];
		win->slot3 = w->texturing[win->texture_index];
		win->slot4 = w->texturing[win->texture_index +1];
	}
	if (win->hud_box == 4)
	{
		win->slot0 = w->texturing[win->texture_index -4];
		win->slot1 = w->texturing[win->texture_index -3];
		win->slot2 = w->texturing[win->texture_index -2];
		win->slot3 = w->texturing[win->texture_index -1];
		win->slot4 = w->texturing[win->texture_index];
	}

	if (win->hud_box == 0)
		win->blackbox_x = 253;
	if (win->hud_box == 1)
		win->blackbox_x = 304;
	if (win->hud_box == 2)
		win->blackbox_x = 355;
	if (win->hud_box == 3)
		win->blackbox_x = 406;
	if (win->hud_box == 4)
		win->blackbox_x = 457;
}

void	texture_overing(t_win *win)
{
	t_lstlst	*tmp2;
	t_lst		*tmp;

	if (win->lstlst)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			tmp = tmp2->head;
			while (tmp)
			{
				if (tmp->x == win->x2 && tmp->y == win->y2 && tmp2->closed == 1)
					win->texture_overed_sector = tmp2->sector;
				tmp = tmp->next;
			}
			tmp2 = tmp2->next;
		}
	}
}

void		inventory_display(t_env *w, t_win *win)
{
	final_texture_to_screen(w, win->inventory, 250, 640, 250, 66);
	final_texture_to_screen(w, win->slot0, 253, 655, 40, 40);
	final_texture_to_screen(w, win->slot1, 304, 655, 40, 40);
	final_texture_to_screen(w, win->slot2, 355, 655, 40, 40);
	final_texture_to_screen(w, win->slot3, 406, 655, 40, 40);
	final_texture_to_screen(w, win->slot4, 457, 655, 40, 40);

	final_texture_to_screen(w, win->blackbox, win->blackbox_x, 645, 40, 58);
}

void		building_hud_display(t_env *w, t_win *win, t_texture slot)
{
	final_texture_to_screen(w, win->building_hud, 10, 270, 96, 96);
	final_texture_to_screen(w, slot, 15, 275, 85, 85);
}

void		help_text(t_env *w, t_win *win)
{
	if (win->texture_choice == 0)
		type_str(w, win->dst11, "Wall", 0xFF00FF);
	if (win->texture_choice == 1)
		type_str(w, win->dst11, "Ceiling", 0xFF00FF);
	if (win->texture_choice == 2)
		type_str(w, win->dst11, "Floor", 0xFF00FF);
	if (win->texture_choice == 3)
		type_str(w, win->dst11, "Lower Extrude", 0xFF00FF);
	if (win->texture_choice == 4)
		type_str(w, win->dst11, "Higher Extrude", 0xFF00FF);
}

void		thumbnail(t_env *w, t_win *win)
{
	t_lstlst	*tmp2;
	t_texture	tmp;

	tmp = win->slot0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == win->texture_overed_sector)
			break;
		tmp2 = tmp2->next;
	}
	if (win->texture_choice == 0)
		tmp = w->texturing[tmp2->txtr_wall];
	if (win->texture_choice == 1)
		tmp = w->texturing[tmp2->txtr_ceiling];
	if (win->texture_choice == 2)
		tmp = w->texturing[tmp2->txtr_floor];
	if (win->texture_choice == 3)
		tmp = w->texturing[tmp2->txtr_lower_extrude];
	if (win->texture_choice == 4)
		tmp = w->texturing[tmp2->txtr_higher_extrude];
	building_hud_display(w, win, tmp);
}

void		texture_mode(t_env *w, t_win *win)
{
	t_lstlst	*tmp2;

	texture_overing(win);

	inventory_display(w, win);

	if (win->put_texture)
	{
		tmp2 = win->lstlst;
		while (tmp2)
		{
			if (tmp2->sector == win->texture_overed_sector)
				break;
			tmp2 = tmp2->next;
		}
		if (tmp2)
		{
			if (win->texture_choice == 0)
				tmp2->txtr_wall = win->texture_index;
			if (win->texture_choice == 1)
				tmp2->txtr_ceiling = win->texture_index;
			if (win->texture_choice == 2)
				tmp2->txtr_floor = win->texture_index;
			if (win->texture_choice == 3)
				tmp2->txtr_lower_extrude = win->texture_index;
			if (win->texture_choice == 4)
				tmp2->txtr_higher_extrude = win->texture_index;
		}
	}

	if (win->texture_overed_sector != -1)
	{
		thumbnail(w, win);
		help_text(w, win);
	}
	win->put_texture = 0;
}
