/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agay <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 10:39:27 by agay              #+#    #+#             */
/*   Updated: 2017/11/30 05:38:18 by agay             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strstr(const char *meule, const char *aiguille)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	if (aiguille[0] == '\0')
		return (char *)meule;
	while (meule[i] != '\0')
	{
		while (meule[i + c] == aiguille[c] && aiguille[c] != '\0')
			c++;
		if (aiguille[c] == '\0')
			return (((char*)meule) + i);
		c = 0;
		i++;
	}
	return (0);
}
