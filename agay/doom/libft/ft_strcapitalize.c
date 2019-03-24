/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 05:03:27 by agay              #+#    #+#             */
/*   Updated: 2017/11/29 05:34:54 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcapitalize(char *str)
{
	int		i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (ft_isupper(str[i]) == 1)
			str[i] = str[i] + ' ';
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) == 1 &&
			ft_isalpha(str[i - 1]) == 0 && ft_isdigit(str[i - 1]) == 0)
			str[i] = str[i] - ' ';
		i++;
	}
	return (str);
}
