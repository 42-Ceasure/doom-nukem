/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 00:51:46 by agay              #+#    #+#             */
/*   Updated: 2019/04/09 10:07:44 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	ceiling_line(int x, int *box, t_env *w, Uint32 color)
{
	int		y;
	int		y1;
	int		y2;

	y1 = box[0];
	y2 = box[1];
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1 + 1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = color;
	else if (y2 > y1)
	{
		w->pix[y1 * WIDTH + x] = color;
		while (y < y2)
		{
			w->pix[y * WIDTH + x] = color;
			y++;
		}
		w->pix[y2 * WIDTH + x] = color;
	}
}

void	vertical_line(int x, int *box, t_env *w, t_color color)
{
	int		y;
	int		y1;
	int		y2;

	y1 = box[0];
	y2 = box[1];
	y1 = vmid(y1, 0, HEIGHT - 1);
	y2 = vmid(y2, 0, HEIGHT - 1);
	y = y1 + 1;
	if (y2 == y1)
		w->pix[y1 * WIDTH + x] = color.middle;
	else if (y2 > y1)
	{
		w->pix[y1 * WIDTH + x] = color.top;
		while (y < y2)
		{
			w->pix[y * WIDTH + x] = color.middle;
			y++;
		}
		w->pix[y2 * WIDTH + x] = color.bottom;
	}
}

void	clean_render(t_env *w, Uint32 color)
{
	int x;

	x = 0;
	while (x < HEIGHT * WIDTH - 1)
	{
		w->pix[x] = color;
		x++;
	}
}

int		init_draw(t_draw *d, t_reader *read, t_map *m)
{
	read->head = read->queue;
	read->tail = read->queue;
	read->head->sectorno = m->player.sector;
	read->head->sx1 = 0;
	read->head->sx2 = WIDTH - 1;
	if (++read->head == read->queue + m->maxrenderedsector)
		read->head = read->queue;
	d->nearz = 0.0000000001;
	d->farz = 5;
	d->nearside = 0.0000000001;
	d->farside = 20.f;
	d->color.top = 0x12111111;
	d->color.middle = 0x12222222;
	d->color.bottom = 0x12111111;
	d->color2.top = 0x120000FF;
	d->color2.middle = 0x120000AA;
	d->color2.bottom = 0x120000FF;
	return (0);
}

void	init_verification(t_draw *d)
{
	d->i1.x1 = d->t1.x;
	d->i1.y1 = d->t1.z;
	d->i1.x2 = d->t2.x;
	d->i1.y2 = d->t2.z;
	d->i1.x3 = -d->nearside;
	d->i1.y3 = d->nearz;
	d->i1.x4 = -d->farside;
	d->i1.y4 = d->farz;
	d->i2.x1 = d->t1.x;
	d->i2.y1 = d->t1.z;
	d->i2.x2 = d->t2.x;
	d->i2.y2 = d->t2.z;
	d->i2.x3 = d->nearside;
	d->i2.y3 = d->nearz;
	d->i2.x4 = d->farside;
	d->i2.y4 = d->farz;
	d->ip1 = intersect(d->i1);
	d->ip2 = intersect(d->i2);
}

