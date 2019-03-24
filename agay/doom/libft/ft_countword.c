/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_countword.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 02:00:09 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 03:52:00 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_countword(char *str)
{
	int		i;
	int		count;

	i = 0;
	str = ft_strtrim(str);
	if (str[i] != '\0')
		count = 1;
	else
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == ' ')
			count++;
		while (str[i] == ' ')
			i++;
		i++;
	}
	return (count);
}
