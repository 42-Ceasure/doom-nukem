/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 16:09:21 by agay              #+#    #+#             */
/*   Updated: 2019/02/15 08:22:01 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_isnega(int *n, int *neg)
{
	*neg = 0;
	if (*n < 0)
	{
		*n *= -1;
		*neg = 1;
	}
}

static char	*ft_asign(char *dest, int n, int len)
{
	while (n > 0)
	{
		dest[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (dest);
}

char		*ft_itoa(int n)
{
	int		neg;
	int		tmp;
	int		len;
	char	*dest;

	tmp = n;
	neg = 0;
	len = 1;
	ft_isnega(&n, &neg);
	while (tmp /= 10)
		len++;
	len = len + neg;
	if (n == 0)
		return (ft_strdup("0"));
	if (n == (-2147483648))
		return (ft_strdup("-2147483648"));
	if (!(dest = (char *)malloc(sizeof(char) * (len + 1))))
		return (0);
	if (neg == 1)
		dest[0] = '-';
	dest[len--] = '\0';
	dest = ft_asign(dest, n, len);
	return (dest);
}
