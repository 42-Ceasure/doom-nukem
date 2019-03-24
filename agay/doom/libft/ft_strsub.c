/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 09:40:58 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 06:13:57 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (!(dest = malloc(sizeof(char) * len + 1)))
		return (0);
	if (s != 0)
	{
		while (i < len)
		{
			dest[i] = s[start];
			i++;
			start++;
		}
		dest[i] = '\0';
	}
	return (dest);
}
