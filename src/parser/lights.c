/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:17 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/05 15:09:47 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_bool retrieve_camera(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_bool status;

	tokens = ft_split(line, ' ');
	status = parse_identifier(tokens, "C") &&
			 parse_vec3(tokens + 1, &(scene->camera.origin)) &&
			 parse_vec3(tokens + 6, &(scene->camera.orientation)) &&
			 parse_float(tokens + 11, &(scene->camera.field_of_view));
	if (tokens[12])
		status = FALSE;
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	if ((status == FALSE) || (scene->camera.field_of_view < 0) || (scene->camera.field_of_view - 180.0f > EPSILON))
		return (FALSE);
	if (fabsf(get_vec3_magnitude(scene->camera.orientation) - 1.0f) > EPSILON)
		return (FALSE);
	return (status);
}

t_bool retrieve_amb_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_rgb temp;
	t_bool valid;

	tokens = ft_split(line, ' ');
	valid = parse_identifier(tokens, "A") &&
			parse_float(tokens + 1, &(scene->ambient.intensity)) &&
			parse_rgb(tokens + 2, &(scene->ambient.color));
	if (tokens[7])
		valid = FALSE;
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	if (!valid)
		return (valid);
	if ((scene->ambient.intensity < 0.0f) || (scene->ambient.intensity - 1.0f > EPSILON))
		return (FALSE);
	temp = normalize_rgb(scene->ambient.color);
	scene->ambient.color.red = temp.red;
	scene->ambient.color.green = temp.green;
	scene->ambient.color.blue = temp.blue;
	return (valid);
}

t_bool retrieve_point_light(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_bool valid;

	tokens = ft_split(line, ' ');
	valid = parse_identifier(tokens, "L") &&
				parse_vec3(tokens + 1, &(scene->light.origin)) &&
				parse_float(tokens + 6, &(scene->light.intensity)) &&
				parse_rgb(tokens + 7, &(scene->light.color));
	if(tokens[12])
		valid = FALSE;
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	if (!valid)
		return (valid);
	if ((scene->light.intensity < 0.0f )|| (scene->light.intensity - 1.0f > EPSILON))
		return (FALSE);
	scene->light.color.red /= 255.0;
	scene->light.color.green /= 255.0;
	scene->light.color.blue /= 255.0;
	scene->light.color = normalize_rgb(scene->light.color);
	return (valid);
}