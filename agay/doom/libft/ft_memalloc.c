/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 15:27:15 by agay              #+#    #+#             */
/*   Updated: 2017/11/21 15:43:37 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*dest;
	size_t	i;

	i = 0;
	if (!(dest = malloc(sizeof(dest) * size + 1)))
		return (0);
	while (i < size)
	{
		dest[i] = 0;
		i++;
	}
	return (dest);
}
