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
#include "libft.h"

void			ft_strsplit_free(char **str)
{
	free(str);
	str = NULL;
}

static	int		ft_count_words(const char *str, char c)
{
	int	word;
	int	i;

	i = 0;
	word = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
			word++;
		i++;
	}
	if (str[0] != '\0')
		word++;
	return (word);
}

static	char	*ft_word(const char *str, char c, int *i)
{
	char	*s;
	int		k;

	if (!(s = (char *)malloc(sizeof(s) * (ft_strlen(str)))))
		return (NULL);
	k = 0;
	while (str[*i] != c && str[*i])
	{
		s[k] = str[*i];
		k++;
		*i += 1;
	}
	s[k] = '\0';
	while (str[*i] == c && str[*i])
		*i += 1;
	return (s);
}

char			**ft_strsplit(const char *str, char c)
{
	int		i;
	int		j;
	int		wrd;
	char	**s;

	i = 0;
	j = 0;
	wrd = ft_count_words(str, c);
	if (!(s = (char **)malloc(sizeof(s) * (ft_count_words(str, c) + 2))))
		return (NULL);
	while (str[i] == c && str[i])
		i++;
	while (j < wrd && str[i])
	{
		s[j] = ft_word(str, c, &i);
		j++;
	}
	s[j] = NULL;
	return (s);
}

// static int			ft_count(char const *s, char c)
// {
// 	int				i;
// 	int				len;

// 	i = 0;
// 	len = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
// 			len++;
// 		i++;
// 	}
// 	return (len);
// }

// #include <assert.h>

// static char			**ft_sublen(char const *s, char c, char **tab, int nbl)
// {
// 	int				i;
// 	int				j;
// 	size_t			start;
// 	size_t			len;

// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c && nbl > 0)
// 		{
// 			nbl--;
// 			start = i;
// 			len = 0;
// 			while (s[i] != c && s[i] != '\0')
// 			{
// 				len++;
// 				i++;
// 			}
// 			tab[j++] = ft_strsub(s, start, len);
// 		}
// 		i++;
// 		assert((size_t)i <= strlen(s));
// 	}
// 	tab[j] = NULL;
// 	return (tab);
// }

// char				**ft_strsplit(const char *s, char c)
// {
// 	int				nbl;
// 	char			**tab;

// 	nbl = 0;
// 	if (!s)
// 		return (NULL);
// 	nbl = ft_count(s, c);
// 	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (nbl + 1))))
// 		return (NULL);
// 	tab = ft_sublen(s, c, tab, nbl);
// 	return (tab);
// }
