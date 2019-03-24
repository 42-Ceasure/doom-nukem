/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:25:00 by agay              #+#    #+#             */
/*   Updated: 2017/11/21 10:36:33 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		pos;

	i = 0;
	pos = -1;
	while (s[i] != '\0')
	{
		if (s[i] == ((char)c))
		{
			pos = i;
		}
		i++;
	}
	if (c == '\0')
		return (((char *)s) + i);
	else if (pos != -1)
		return (((char *)s) + pos);
	else
		return (0);
}
