/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:55:00 by agay              #+#    #+#             */
/*   Updated: 2018/06/03 01:03:38 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		c;
	char	*dest;

	if (s1 != 0 && s2 != 0)
	{
		i = ft_strlen(s1) + ft_strlen(s2);
		c = 0;
		if (!(dest = malloc(sizeof(char *) * i + 1)))
			return (0);
		i = 0;
		while (s1[i] != '\0')
		{
			dest[i] = s1[i];
			i++;
		}
		while (s2[c] != '\0')
		{
			dest[i + c] = s2[c];
			c++;
		}
		dest[i + c] = '\0';
		return (dest);
	}
	return (0);
}
