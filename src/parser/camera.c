/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:15 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 11:52:02 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_bool retrieve_camera(t_scene *scene, char *line)
{
	char **tokens;
	int i;
	t_bool status;

	tokens = ft_split(line, ' ');
	parse_identifier(tokens, "C");
	status = parse_vec3(tokens + 1, &(scene->camera.origin)) &&
				parse_vec3(tokens + 4, &(scene->camera.orientation)) &&
				parse_float(tokens + 7, &(scene->camera.field_of_view));
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	return (status);
}