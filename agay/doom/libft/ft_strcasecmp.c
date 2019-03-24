/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasecmp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 05:35:25 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 03:50:49 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcasecmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	tmp1;
	unsigned char	tmp2;

	tmp1 = 0;
	tmp2 = 0;
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		i++;
	if (s1[i] >= 'A' && s1[i] <= 'Z')
		tmp1 = s1[i] + ' ';
	else
		tmp1 = s1[i];
	if (s2[i] >= 'A' && s2[i] <= 'Z')
		tmp2 = s2[i] + ' ';
	else
		tmp2 = s2[i];
	return (tmp1 - tmp2);
}
