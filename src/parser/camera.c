/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:15 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:28:36 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void retrieve_camera(t_scene *scene, char *line)
{
	char **tokens;
	int i;

	tokens = ft_split(line, ' ');
	scene->camera.origin.x = float_parser(tokens[1]);
	scene->camera.origin.y = float_parser(tokens[2]);
	scene->camera.origin.z = float_parser(tokens[3]);
	scene->camera.orientation.x = float_parser(tokens[4]);
	scene->camera.orientation.y = float_parser(tokens[5]);
	scene->camera.orientation.z = float_parser(tokens[6]);
	scene->camera.field_of_view = float_parser(tokens[7]);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}