/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_spacecleaner.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 02:02:34 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 04:51:33 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_size(char *str)
{
	int		i;
	int		size;

	size = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i] == 0))
			size++;
		i++;
	}
	return (size);
}

char		*ft_spacecleaner(char *str)
{
	char	*dest;
	int		i;
	int		count;
	int		size;

	i = 0;
	str = ft_strtrim(str);
	size = ft_size(str);
	count = ft_countword(str);
	if (!(dest = malloc(sizeof(char *) * (size + count))))
		return (0);
	count = 0;
	while (str[i] != '\0')
	{
		if (ft_isspace(str[i]))
			dest[count++] = str[i];
		while (ft_isspace(str[i]))
			i++;
		dest[count++] = str[i++];
	}
	dest[count] = '\0';
	return (dest);
}
