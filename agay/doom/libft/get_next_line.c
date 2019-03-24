/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 13:11:58 by agay              #+#    #+#             */
/*   Updated: 2018/08/21 16:46:35 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		end_of_line(char *buff)
{
	int		count;

	count = 0;
	while (buff[count] != '\n' && buff[count])
		count++;
	if (buff[count] == '\n')
	{
		buff[count] = '\0';
		return (count);
	}
	else
		return (-1);
}

static char		*join(char *buff, char *tab)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = 0;
	j = 0;
	if (buff)
		i = ft_strlen(buff);
	if (tab)
		j = ft_strlen(tab);
	ptr = (char *)malloc(sizeof(*ptr) * (i + j + 1));
	ft_memcpy(ptr, buff, i);
	ft_memcpy(ptr + i, tab, j);
	ptr[i + j] = '\0';
	free(buff);
	ft_bzero(tab, BUFF_SIZE + 1);
	return (ptr);
}

static int		verif(char **buff, char **tab, char **line)
{
	char	*ptr;
	int		final;

	*buff = join(*buff, *tab);
	final = end_of_line(*buff);
	if (final > -1)
	{
		*line = ft_strdup(*buff);
		ptr = *buff;
		*buff = ft_strdup(*buff + final + 1);
		free(ptr);
		return (1);
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static char		*buff[256];
	char			*tmp;
	int				ret[2];

	tmp = ft_strnew(BUFF_SIZE);
	if (BUFF_SIZE <= 0 || fd < 0 || (ret[0] = read(fd, tmp, 0)) < 0)
		return (-1);
	while ((ret[0] = read(fd, tmp, BUFF_SIZE)) > 0)
	{
		ret[1] = verif(&buff[fd], &tmp, line);
		free(tmp);
		if (ret[1] == 1)
			return (1);
		tmp = ft_strnew(BUFF_SIZE);
	}
	if ((ret[1] = verif(&buff[fd], &tmp, line)))
		return (1);
	else if (ft_strlen(buff[fd]) > 0)
	{
		*line = ft_strdup(buff[fd]);
		ft_strdel(&buff[fd]);
		return (1);
	}
	free(tmp);
	return (ret[1]);
}
