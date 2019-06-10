/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 22:11:49 by abechet           #+#    #+#             */
/*   Updated: 2018/11/21 19:44:39 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		i;
	char	*s2;

	i = 0;
	if (!s || !f || !(s2 = ((char *)malloc(sizeof(char) * ft_strlen(s) + 1))))
		return (NULL);
	while (s[i])
	{
		s2[i] = (f)(s[i]);
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
