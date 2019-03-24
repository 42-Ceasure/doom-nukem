/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 05:45:45 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 05:47:41 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *meule, const char *aiguille, size_t len)
{
	size_t	i;
	size_t	c;

	i = 0;
	c = 0;
	while (meule[i] != '\0' && i < len)
	{
		while (meule[i + c] == aiguille[c] &&
				aiguille[c] != '\0' && (i + c) < len)
			c++;
		if (aiguille[c] == '\0')
			return (((char *)meule) + i);
		c = 0;
		i++;
	}
	return (0);
}
