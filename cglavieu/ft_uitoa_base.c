/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ochaar <ochaar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 11:20:27 by ochaar            #+#    #+#             */
/*   Updated: 2019/04/17 16:20:50 by ochaar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

//remplacer cette fonction par ft_bzero de la libft
void		ft_bzero(char *s1, char *s2)
{
	int i;

	i = 0;
	while (i < 100)
	{
		s1[i] = '\0';
		s2[i] = '\0';
		i++;
	}
}


char		*rev_str(char *str, char *tmp, int j)
{
	int i;

	i = 0;
	while (j >= 0)
	{
		str[i] = tmp[j];
		j--;
		i++;
	}
	return (str);
}

char		*ft_uitoa_base(unsigned int n, int base)
{
	char	*str;
	int		j;
	char	*tmp;
	char	*dbase;

	if (base <= 1)
		return (0);
	str = (char*)malloc(sizeof(char) * 100);
	tmp = (char*)malloc(sizeof(char) * 100);
	dbase = "0123456789ABCDEF";
	ft_bzero(str, tmp);
	j = 0;
	while (n > 0)
	{
		tmp[j] = dbase[n % base];
		n = n / base;
		j++;
	}
	j--;
	str = rev_str(str, tmp, j);
	free(tmp);
	return (str);
}

int main(int argc, char **argv)
{
	if (argc == 2)
		printf("%s\n", ft_uitoa_base(0xFFFFFF, atoi(argv[1])));
	return (0);
}
