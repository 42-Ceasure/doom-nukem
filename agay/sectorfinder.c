/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sectorunner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 10:10:10 by agay              #+#    #+#             */
/*   Updated: 2019/04/06 10:22:30 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		dualfinder(int s, int *list)
{
	int		i;

	i = 0;
	while (list[i] != -42)
	{
		if (list[i] == s)
			return (0);
		i++;
	}
	return (1);
}

void	sectorfinder(t_map m, int **sectorlist, int s, int f)
{
	int		d;
	t_work	work;

	d = 0;
	while (d < m.sector[s].wall_count - 1)
	{
		work.v1.x = m.sector[s].dot[d].x - m.player.coor.x;
		work.v1.y = m.sector[s].dot[d].y - m.player.coor.y;
		work.v2.x = m.sector[s].dot[d + 1].x - m.player.coor.x;
		work.v2.y = m.sector[s].dot[d + 1].y - m.player.coor.y;
		work.pcos = m.player.anglecos;
		work.psin = m.player.anglesin;
		work.t1.x = work.v1.x * work.psin - work.v1.y * work.pcos;
		work.t1.z = work.v1.x * work.pcos + work.v1.y * work.psin;
		work.t2.x = work.v2.x * work.psin - work.v2.y * work.pcos;
		work.t2.z = work.v2.x * work.pcos + work.v2.y * work.psin;
		if (m.sector[s].network[d] >= 0 && verifdouble(m.sector[s].network[d], *sectorlist)
		&& ((work.t1.z > 0 && work.t2.z > 0) || (work.t1.z > 0 || work.t2.z > 0)))
		{
			sectorlist[0][f] = m.sector[s].network[d];
			sector(w, m, sectorlist, m.sector[s].network[d], f + 1);
		}
		d++;
	}
}

int		initfinder(void)
{
	int		*sectorlist;
	t_env	*w;
	t_map	*m;
	int		i;
	int		s;
	int		f;

	sectorlist = NULL;
	if ((sectorlist = (int *)malloc(sizeof(int) * (m->sector_count + 1))) == NULL)
		return (0);
	i = 0;
	while (i < m.sector_count)
		sectorlist[i++] = -1;
	sectorlist[m.sector_count] = -42;
	sectorlist[0] = m->player.sector;
	s = m->player.sector;
	f = 1;
	sectorfinder(*m, &sectorlist, s, f);
}
