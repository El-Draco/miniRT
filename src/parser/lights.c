/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:17 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:43:30 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void retrieve_amb_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_rgb temp;
	tokens = ft_split(line, ' ');
	scene->ambient.intensity = float_parser(tokens[1]);
	scene->ambient.color.red = float_parser(tokens[2]) / 255.0;
	scene->ambient.color.green = float_parser(tokens[3]) / 255.0;
	scene->ambient.color.blue = float_parser(tokens[4]) / 255.0;
	temp = normalize_rgb(scene->ambient.color);
	scene->ambient.color.red = temp.red;
	scene->ambient.color.green = temp.green;
	scene->ambient.color.blue = temp.blue;
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}

void retrieve_point_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	scene->light.origin.x = float_parser(tokens[1]);
	scene->light.origin.y = float_parser(tokens[2]);
	scene->light.origin.z = float_parser(tokens[3]);
	scene->light.intensity = float_parser(tokens[4]);
	scene->light.color.red = float_parser(tokens[5]) / 255.0;
	scene->light.color.green = float_parser(tokens[6]) / 255.0;
	scene->light.color.blue = float_parser(tokens[7]) / 255.0;
	scene->light.color = normalize_rgb(scene->light.color);

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}