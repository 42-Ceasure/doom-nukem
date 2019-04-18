/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoui_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 15:29:41 by ochaar            #+#    #+#             */
/*   Updated: 2019/04/17 15:44:27 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

static char		to_upper(char c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}

static int		find_base(char c, int base)
{
	int		i;
	char	*def;

	i = 0;
	def = "0123456789ABCDEF";
	while (i < base)
	{
		if (def[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

unsigned int	ft_atoui_base(const char *str, int base)
{
	unsigned int	ret;

	ret = 0;
	while (*str && *str != ' ')
	{
		if (find_base(to_upper(*str), base) != -1)
			ret = (ret * base) + find_base(to_upper(*str), base);
		str++;
	}
	return (ret);
}

int main(int argc, char **argv)
{
	if (argc == 3)
		printf("%d", ft_atoui_base(argv[1], atoi(argv[2])));
	return (0);
}