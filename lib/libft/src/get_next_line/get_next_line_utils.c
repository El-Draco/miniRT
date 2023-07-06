/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 20:56:37 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:09:02 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

long	ft_strchr(const char *s, int c)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == (char)c)
			return (i);
	if (s[i] == (char)c)
		return (i);
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	char	*temp;
	int		l1;

	if (!s1 || !s2)
		return (NULL);
	l1 = ft_len(s1);
	i = 0;
	temp = malloc(l1 + ft_len(s2) + 1);
	if (!temp)
		return (NULL);
	while (s1[i])
	{
		temp[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		temp[l1 + i] = s2[i];
		i++;
	}
	temp[l1 + i] = 0;
	free(s1);
	return (temp);
}

char	*sbstr(char *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	i;

	result = malloc(len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (i < len)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*s;

	i = 0;
	s = (char *)malloc(1 + sizeof(char) * ft_len(s1));
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = 0;
	return (s);
}
