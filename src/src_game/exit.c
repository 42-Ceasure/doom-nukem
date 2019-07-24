/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 10:17:33 by ochaar            #+#    #+#             */
/*   Updated: 2019/07/24 13:28:13 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		empty_music(t_env *w)
{
	if (w->sound.musique != NULL)
		Mix_FreeMusic(w->sound.musique);
	if (w->sound.jump != NULL)
		Mix_FreeChunk(w->sound.jump);
	if (w->sound.ground != NULL)
		Mix_FreeChunk(w->sound.ground);
	if (w->sound.reload != NULL)
		Mix_FreeChunk(w->sound.reload);
	if (w->sound.clic != NULL)
		Mix_FreeChunk(w->sound.clic);
	if (w->sound.dammage != NULL)
		Mix_FreeChunk(w->sound.dammage);
	Mix_CloseAudio();
}

void		empty_world(t_env *w)
{
	int		i;

	i = -1;
	if (w != NULL)
	{
		if (w->light_nb != NULL)
			free(w->light_nb);
		if (w->main_pic[0].pix != NULL)
			free(w->main_pic[0].pix);
		if (w->main_pic[1].pix != NULL)
			free(w->main_pic[1].pix);
		if (w->main_pic[2].pix != NULL)
			free(w->main_pic[2].pix);
		if (w->pix != NULL)
			free(w->pix);
		if (w->ascii != NULL)
		{
			while (++i < w->asciino)
			{
				if (w->ascii[i].pix != NULL)
					free(w->ascii[i].pix);
			}
			free(w->ascii);
		}
		i = -1;
		if (w->texturing != NULL)
		{
			while (++i < w->texturingno)
			{
				if (w->texturing[i].pix != NULL)
					free(w->texturing[i].pix);
			}
			free(w->texturing);
		}
		free(w);
	}
}

void		ft_free_sector(t_map *m)
{
	int	i;

	i = 0;
	if (m->sector != NULL)
	{
		while (i < m->sector_count && i < m->s)
		{
			if (m->sector[i].dot != NULL)
				free(m->sector[i].dot);
			if (m->sector[i].network != NULL)
				free(m->sector[i].network);
			i++;
		}
		free(m->sector);
		m->sector = NULL;
	}
}

void		empty_map(t_map *m)
{
	if (m != NULL)
	{
		if (m->player.fps != NULL)
			free(m->player.fps);
		if (m->player.stractu_ammo != NULL)
			free(m->player.stractu_ammo);
		if (m->player.strhp != NULL)
			free(m->player.strhp);
		if (m->player.strbullet != NULL)
			free(m->player.strbullet);
		if (m->map_name != NULL)
			free(m->map_name);
		if (m->map_name != NULL)
			free(m->map_path);
		if (m->dot != NULL)
			free(m->dot);
		if (m->hud.pix != NULL)
			free(m->hud.pix);
		if (m->ennemy != NULL)
			free(m->ennemy);
		ft_free_sprt(m);
		ft_free_weap(m);
		ft_free_sector(m);
		free(m);
	}
}

void		exit_game(t_env *w, t_map *m, int i)
{
	empty_music(w);
	empty_map(m);
	SDL_DestroyTexture(w->txtr);
	SDL_DestroyRenderer(w->rdr);
	SDL_DestroyWindow(w->win);
	SDL_Quit();
	empty_world(w);
	if (i == 1)
		exit(0);
}
