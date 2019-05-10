/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/16 15:46:38 by cglavieu          #+#    #+#             */
/*   Updated: 2015/01/21 16:21:28 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char const *s1, int fd)
{
	int i;

	i = 0;
	if (s1)
	{
		while(s1[i])
			i++;
		write(fd, s1, i);
	}
}
