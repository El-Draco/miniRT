/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:15 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 17:44:28 by rriyas           ###   ########.fr       */
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
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	if ((status == FALSE) || (scene->camera.field_of_view < EPSILON )|| (scene->camera.field_of_view - 180.0f > EPSILON))
		return (FALSE);
	if (fabsf(get_vec3_magnitude(scene->camera.orientation) - 1.0f) > EPSILON)
		return (FALSE);
	return (status);
}