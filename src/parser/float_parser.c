/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:59:04 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 14:01:43 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_bool	is_valid_float(char *str)
{
	int	i;

	i = 0;
	if (str && str[0] != '+' && str[0] != '-' && !ft_isdigit(str[0]))
		return (FALSE);
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i] || !ft_isdigit(str[i]) || count_dots(str) > 1)
		return (FALSE);
	while (str[i] && str[i] != '.')
	{
		if (!ft_isdigit(str[i++]))
			return (FALSE);
	}
	if (!str[i])
		return (TRUE);
	i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_bool	valid_number(char *str, t_bool floating)
{
	char *temp;
	if (floating)
		return (is_valid_float(str));
	else
	{
		temp = ft_itoa(ft_atoi(str));
		if (ft_strncmp(str, temp, ft_strlen(str)))
		{
			free(temp);
			return (FALSE);
		}
		free(temp);
	}
	return (TRUE);
}

char	*ft_ftoa(float n)
{
	char	*res;
	char	*floating;
	int		int_part;
	float	float_part;
	int		i;

	int_part = (int)n;
	float_part = n - (float)int_part;
	res = ft_itoa(int_part);
	if (float_part < 0.0f && int_part == 0)
		res = join_and_free("-", res, FALSE, TRUE);
	if (float_part < 0.0f)
		float_part = -float_part;
	res = join_and_free(res, ".", TRUE, FALSE);
	i = -1;
	while (float_part < 1.0f && float_part != 0.0f && ++i < 6)
	{
		float_part *= 10;
		if (float_part < 1.0f)
			res = join_and_free(res, "0", TRUE, FALSE);
	}
	while (++i < 7)
		float_part *= 10;
	floating = ft_itoa((int)(float_part));
	return (join_and_free(res, floating, TRUE, TRUE));
}

float	ft_atof(char *s)
{
	int		i;
	int		neg;
	double	d;
	double	temp;

	i = 0;
	neg = 1;
	d = 0;
	if (s[i] == '-')
	{
		neg = -1;
		i++;
	}
	while (s[i] && s[i] != '.')
		d = d * 10 + (s[i++] - '0');
	if (s[i] && s[i] == '.')
		i++;
	temp = 0.1;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		d += (s[i++] - '0') * temp;
		temp /= 10;
	}
	return (neg * d);
}
