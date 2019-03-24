/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 11:32:08 by agay              #+#    #+#             */
/*   Updated: 2017/11/24 23:26:02 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	end;

	i = 0;
	while (dst[i] && i < size)
		i++;
	end = i;
	if (size != 0)
	{
		while (src[i - end] && i < size - 1)
		{
			dst[i] = src[i - end];
			i++;
		}
	}
	if (end < size)
		dst[i] = '\0';
	return (end + ft_strlen(src));
}
