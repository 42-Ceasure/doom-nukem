/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ishexa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abechet <abechet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 15:07:21 by abechet           #+#    #+#             */
/*   Updated: 2019/02/17 19:47:23 by abechet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ishexa(int c)
{
	return ((ft_isdigit(c)) || (c >= 'A' && c <= 'F') \
		|| (c >= 'a' && c <= 'f'));
}
