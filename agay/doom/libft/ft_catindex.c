/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_catindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 01:59:27 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 02:11:37 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_catindex(char *s1, char *s2, size_t index)
{
	char	*result;
	size_t	i;
	size_t	c;
	size_t	d;

	i = 0;
	d = 0;
	c = 0;
	if (index < ft_strlen(s1) && index != '\0' && s1 != '\0' && s2 != '\0')
	{
		if (!(result = malloc(sizeof(ft_strlen(s1) + ft_strlen(s2) + 1))))
			return (0);
		while (i < index)
			result[i++] = s1[d++];
		while (s2[c])
			result[i++] = s2[c++];
		while (s1[d])
			result[i++] = s1[d++];
		result[i] = '\0';
		return (result);
	}
	return (0);
}
