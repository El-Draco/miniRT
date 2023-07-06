/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attribute_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:18:46 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 14:15:40 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	count_dots(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (str[++i])
	{
		if (str[i] == '.')
			count++;
	}
	return (count);
}

t_bool	parse_float(char **tokens, float *num)
{
	if (!tokens[0] || !valid_number(tokens[0], TRUE))
		return (FALSE);
	if (count_dots(tokens[0]) > 1)
		return (FALSE);
	*num = ft_atof(tokens[0]);
	return (TRUE);
}

t_bool	parse_identifier(char **tokens, char *valid)
{
	if (!ft_strncmp(tokens[0], valid, 5))
		return (TRUE);
	return (FALSE);
}

t_bool	parse_rgb(char **tokens, t_rgb *rgb)
{
	if (!check_commas(tokens))
		return (FALSE);
	if (!valid_number(tokens[0], FALSE))
		return (FALSE);
	rgb->red = ft_atoi(tokens[0]);
	if (!valid_number(tokens[2], FALSE))
		return (FALSE);
	rgb->green = ft_atoi(tokens[2]);
	if (!valid_number(tokens[4], FALSE))
		return (FALSE);
	rgb->blue = ft_atoi(tokens[4]);
	if (invalid_rgb_range(*rgb))
		return (FALSE);
	return (TRUE);
}

t_bool	parse_vec3(char **tokens, t_vec3 *vec)
{
	t_bool	valid;

	if (!check_commas(tokens))
		return (FALSE);
	valid = parse_float(tokens, &(vec->x));
	if (!valid)
		return (FALSE);
	valid = parse_float(tokens + 2, &(vec->y));
	if (!valid)
		return (FALSE);
	valid = parse_float(tokens + 4, &(vec->z));
	if (!valid)
		return (FALSE);
	return (TRUE);
}
