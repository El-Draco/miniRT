/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/05 11:23:33 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/05 15:24:23 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_bool valid_args(int argc, char **argv)
{
	char *file_name;
	t_bool status;

	if (argc == 1 || argc > 2)
		return (FALSE);
	if (!ft_strncmp("", argv[1], 2) || ft_strlen(argv[1]) <= 3)
		return (FALSE);
	file_name = ft_substr(argv[1], ft_strlen(argv[1]) - 3, 4);
	status = FALSE;
	if (!ft_strncmp(file_name, ".rt", 4))
		status = TRUE;
	free(file_name);
	return (status);
}

t_bool valid_char(char *str, t_bool floating)
{
	int i;

	i = -1;
	while (str[++i])
	{
		if (floating && str[i] && ft_isalpha(str[i]) && str[i] != '.')
			return (FALSE);
		if (!floating && str[i] && (ft_isalpha(str[i]) || str[i] == '.'))
			return (FALSE);
	}
	return (TRUE);
}

t_bool check_commas(char **tokens)
{
	int i;

	i = -1;
	while (++i < 5)
		if (!tokens[i])
			return (FALSE);
	if (!ft_strncmp(tokens[0], ",", 2) || ft_strncmp(tokens[1], ",", 2) || (ft_strlen(tokens[1]) == 1 && tokens[1][0] == '.'))
		return (FALSE);
	if (ft_strncmp(tokens[1], ",", 2) || !ft_strncmp(tokens[2], ",", 2))
		return (FALSE);
	if (!ft_strncmp(tokens[2], ",", 2) || ft_strncmp(tokens[3], ",", 2))
		return (FALSE);
	if (ft_strncmp(tokens[3], ",", 2) || !ft_strncmp(tokens[4], ",", 2))
		return (FALSE);
	if (tokens[5] && !ft_strncmp(tokens[5], ",", 2))
		return (FALSE);
	if (ft_strlen(tokens[0]) == 1 && tokens[0][0] == '.')
		return (FALSE);
	if (ft_strlen(tokens[2]) == 1 && tokens[2][0] == '.')
		return (FALSE);
	if (ft_strlen(tokens[4]) == 1 && tokens[4][0] == '.')
		return (FALSE);
	return (TRUE);
}

t_bool invalid_rgb_range(t_rgb rgb)
{
	if (rgb.red < 0.0f || rgb.red > 255.0f)
		return (TRUE);
	if (rgb.green < 0.0f || rgb.green > 255.0f)
		return (TRUE);
	if (rgb.blue < 0.0f || rgb.blue > 255.0f)
		return (TRUE);
	return (FALSE);
}