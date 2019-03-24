/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 17:05:18 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 06:50:49 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim_char(char const *s, char c)
{
	size_t	i;
	size_t	start;
	size_t	end;
	char	*dest;

	i = 0;
	if (s != 0)
	{
		while (s[i] == c)
			i++;
		start = i;
		i = ft_strlen(s);
		while (s[i - 1] == c)
			i--;
		if (i == 0)
			return (dest = (char *)malloc(sizeof(char) * 0));
		end = i - start;
		return (ft_strsub(s, start, end));
	}
	return (0);
}
