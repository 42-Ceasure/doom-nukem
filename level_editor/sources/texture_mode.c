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

#include "editor.h"

void		change_texture_index(t_win *win)
{
	if (win->txtr_input_type == 1 || win->txtr_input_type == 2)
	{
		win->texture_index += 1;
		if (win->texture_index > 4)
			win->texture_index = 0;
	}
	if (win->txtr_input_type == 3)
	{
		win->texture_index -= 1;
		if (win->texture_index < 0)
			win->texture_index = 4;
	}
	if (win->texture_index == 0)
	{
		win->blackbox_x = 253;
		win->texture_sprite = IMG_Load("resources/textures/feather.png");
	}
	if (win->texture_index == 1)
	{
		win->blackbox_x = 304;
		win->texture_sprite = IMG_Load("resources/textures/gun1.png");
	}
	if (win->texture_index == 2)
	{
		win->blackbox_x = 355;
		win->texture_sprite = IMG_Load("resources/textures/shotgun.png");
	}
	if (win->texture_index == 3)
	{
		win->blackbox_x = 406;
		win->texture_sprite = IMG_Load("resources/textures/ennemy.png");
	}
	if (win->texture_index == 4)
	{
		win->blackbox_x = 457;
		win->texture_sprite = IMG_Load("resources/textures/m4_ammo.png");
	}
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

void		inventory_display(t_win *win)
{
	final_texture_to_screen(win->surface, win->inventory, 250, 640, 250, 66);
	final_texture_to_screen(win->surface, win->slot0, 253, 655, 40, 40);
	final_texture_to_screen(win->surface, win->slot1, 304, 655, 40, 40);
	final_texture_to_screen(win->surface, win->slot2, 355, 655, 40, 40);
	final_texture_to_screen(win->surface, win->slot3, 406, 655, 40, 40);
	final_texture_to_screen(win->surface, win->slot4, 457, 655, 40, 40);

	final_texture_to_screen(win->surface, win->blackbox, win->blackbox_x, 645, 40, 58);
}

void		building_hud_display(t_win *win, SDL_Surface *slot)
{
	final_texture_to_screen(win->surface, win->building_hud, 10, 270, 96, 96);
	final_texture_to_screen(win->surface, slot, 15, 275, 85, 85);
}

void		help_text(t_win *win)
{
	if (win->texture_choice == 0)
	{
		win->texturetxt = TTF_RenderText_Blended(win->police,
			"Wall", win->color_font_z);
	}
	if (win->texture_choice == 1)
	{
		win->texturetxt = TTF_RenderText_Blended(win->police,
			"Ceiling", win->color_font_z);
	}
	if (win->texture_choice == 2)
	{
		win->texturetxt = TTF_RenderText_Blended(win->police,
			"Floor", win->color_font_z);
	}
	if (win->texture_choice == 3)
	{
		win->texturetxt = TTF_RenderText_Blended(win->police,
			"Skybox", win->color_font_z);
	}
	if (win->texture_choice == 4)
	{
		win->texturetxt = TTF_RenderText_Blended(win->police,
			"Extrude ?", win->color_font_z);
	}
}

void		thumbnail(t_win *win)
{
	t_lstlst	*tmp2;

	SDL_Surface	*tmp;

	tmp = win->slot0;
	tmp2 = win->lstlst;
	while (tmp2)
	{
		if (tmp2->sector == win->texture_overed_sector)
			break;
		tmp2 = tmp2->next;
	}

	if (win->texture_choice == 0)
	{
		if (tmp2->txtr_wall == 0)
			tmp = win->slot0;
		if (tmp2->txtr_wall == 1)
			tmp = win->slot1;
		if (tmp2->txtr_wall == 2)
			tmp = win->slot2;
		if (tmp2->txtr_wall == 3)
			tmp = win->slot3;
		if (tmp2->txtr_wall == 4)
			tmp = win->slot4;
	}

	if (win->texture_choice == 1)
	{
		if (tmp2->txtr_ceiling == 0)
			tmp = win->slot0;
		if (tmp2->txtr_ceiling == 1)
			tmp = win->slot1;
		if (tmp2->txtr_ceiling == 2)
			tmp = win->slot2;
		if (tmp2->txtr_ceiling == 3)
			tmp = win->slot3;
		if (tmp2->txtr_ceiling == 4)
			tmp = win->slot4;
	}

	if (win->texture_choice == 2)
	{
		if (tmp2->txtr_floor == 0)
			tmp = win->slot0;
		if (tmp2->txtr_floor == 1)
			tmp = win->slot1;
		if (tmp2->txtr_floor == 2)
			tmp = win->slot2;
		if (tmp2->txtr_floor == 3)
			tmp = win->slot3;
		if (tmp2->txtr_floor == 4)
			tmp = win->slot4;
	}

	if (win->texture_choice == 3)
	{
		if (tmp2->txtr_skybox == 0)
			tmp = win->slot0;
		if (tmp2->txtr_skybox == 1)
			tmp = win->slot1;
		if (tmp2->txtr_skybox == 2)
			tmp = win->slot2;
		if (tmp2->txtr_skybox == 3)
			tmp = win->slot3;
		if (tmp2->txtr_skybox == 4)
			tmp = win->slot4;
	}

	if (win->texture_choice == 4)
	{
		if (tmp2->txtr_extrude == 0)
			tmp = win->slot0;
		if (tmp2->txtr_extrude == 1)
			tmp = win->slot1;
		if (tmp2->txtr_extrude == 2)
			tmp = win->slot2;
		if (tmp2->txtr_extrude == 3)
			tmp = win->slot3;
		if (tmp2->txtr_extrude == 4)
			tmp = win->slot4;
	}

	building_hud_display(win, tmp);

}

void		texture_mode(t_win *win)
{
	t_lstlst	*tmp2;

	texture_overing(win);

	inventory_display(win);

	help_text(win);

	if (win->texture_overed_sector != -1)
		thumbnail(win);

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
				tmp2->txtr_skybox = win->texture_index;
			if (win->texture_choice == 4)
				tmp2->txtr_extrude = win->texture_index;
		}
	}
	win->put_texture = 0;
}
