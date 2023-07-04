/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:17 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 11:53:57 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_bool retrieve_amb_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_rgb temp;
	t_bool status;

	tokens = ft_split(line, ' ');
	status = parse_identifier(tokens, "A") &&
			parse_float(tokens + 1, &(scene->ambient.intensity)) &&
			parse_rgb(tokens + 2, &(scene->ambient.color));
	temp = normalize_rgb(scene->ambient.color);
	scene->ambient.color.red = temp.red;
	scene->ambient.color.green = temp.green;
	scene->ambient.color.blue = temp.blue;
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	return (status);
}

t_bool retrieve_point_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_bool status;

	tokens = ft_split(line, ' ');
	status = parse_identifier(tokens, "L") &&
				parse_vec3(tokens + 1, &(scene->light.origin)) &&
				parse_float(tokens + 4, &(scene->light.intensity)) &&
				parse_rgb(tokens + 5, &(scene->light.color));
	scene->light.color.red /= 255.0;
	scene->light.color.green /= 255.0;
	scene->light.color.blue /= 255.0;
	scene->light.color = normalize_rgb(scene->light.color);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	return (status);
}