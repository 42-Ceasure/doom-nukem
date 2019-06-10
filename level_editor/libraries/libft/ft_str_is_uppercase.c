/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/13 01:29:41 by abechet           #+#    #+#             */
/*   Updated: 2018/11/21 21:17:51 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_str_is_uppercase(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (1);
	while (str[i] >= 'A' && str[i] <= 'Z')
		i++;
	if (str[i] == '\0')
		return (1);
	else
		return (0);
}
