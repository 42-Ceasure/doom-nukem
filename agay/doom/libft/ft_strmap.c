/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 16:23:33 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 06:43:29 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f) (char))
{
	char	*dest;
	int		i;

	dest = 0;
	if (s != 0)
	{
		i = ft_strlen(s);
		if (!(dest = malloc(sizeof(char) * i + 1)))
			return (0);
		i = 0;
		while (s[i] != '\0')
		{
			dest[i] = f(s[i]);
			i++;
		}
		dest[i] = '\0';
		return (dest);
	}
	return (NULL);
}
