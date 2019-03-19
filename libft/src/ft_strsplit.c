/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cglavieu <cglavieu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 00:28:12 by cglavieu          #+#    #+#             */
/*   Updated: 2015/05/08 13:04:23 by cglavieu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_count(char const *s, char c)
{
	int				i;
	int				len;

	i = 0;
	len = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			len++;
		i++;
	}
	return (len);
}

static char			**ft_sublen(char const *s, char c, char **tab, int nbl)
{
	int				i;
	int				j;
	size_t			start;
	size_t			len;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c && nbl > 0)
		{
			nbl--;
			start = i;
			len = 0;
			while (s[i] != c && s[i] != '\0')
			{
				len++;
				i++;
			}
			tab[j++] = ft_strsub(s, start, len);
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}

char				**ft_strsplit(const char *s, char c)
{
	int				nbl;
	char			**tab;

	nbl = 0;
	if (!s)
		return (NULL);
	nbl = ft_count(s, c);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (nbl + 1))))
		return (NULL);
	tab = ft_sublen(s, c, tab, nbl);
	return (tab);
}
