/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 18:50:58 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_surface *add_surface(t_surface **surfaces, t_surface *surf)
{
	t_surface *iterator;


	if (!surf)
		return (*surfaces);
	if (!*surfaces)
	{
		surf->next = NULL;
		*surfaces = surf;
		return (*surfaces);
	}
	iterator = *surfaces;
	while (iterator->next)
		iterator = iterator->next;
	iterator->next = surf;
	iterator->next->next = NULL;
	return (*surfaces);
}

static t_bool retrieve_sphere(char **tokens, t_surface *surface)
{
	float *diameter;
	t_bool status;

	surface->type = SPHERE;
	diameter = malloc(sizeof(float) * 1);
	status = parse_identifier(tokens, "sp") &&
				parse_vec3(tokens + 1, &(surface->origin)) &&
				parse_float(tokens + 6, diameter) &&
				parse_rgb(tokens + 7, &(surface->color));
	if (!status)
	{
		free(diameter);
		return (status);
	}
	surface->attributes = diameter;
	surface->color.red /= 255.0;
	surface->color.green /= 255.0;
	surface->color.blue /= 255.0;
	return (status);
}

static t_bool retrieve_plane(char **tokens, t_surface *surface)
{
	t_vec3 *orientation;
	t_bool status;

	surface->type = PLANE;
	orientation = malloc(sizeof(t_vec3) * 1);
	status = parse_identifier(tokens, "pl") &&
				parse_vec3(tokens + 1, &(surface->origin)) &&
				parse_vec3(tokens + 6, &(*orientation)) &&
				parse_rgb(tokens + 11, &(surface->color));
	if (!status || fabsf(get_vec3_magnitude(*orientation) - 1.0f) > EPSILON)
	{
		free(orientation);
		return (status);
	}
	surface->attributes = orientation;
	surface->color.red /= 255.0;
	surface->color.green /= 255.0;
	surface->color.blue /= 255.0;
	return (status);
}

static t_bool retrieve_cylinder(char **tokens, t_surface *surface)
{
	t_cylinder *props;
	t_bool status;

	surface->type = CYLINDER;
	props = malloc(sizeof(t_cylinder) * 1);
	status = parse_identifier(tokens, "cy") &&
				parse_vec3(tokens + 1, &(surface->origin)) &&
				parse_vec3(tokens + 6, &(props->orientation)) &&
				parse_float(tokens + 11, &(props->diameter)) &&
				parse_float(tokens + 12, &(props->height)) &&
				parse_rgb(tokens + 13, &(surface->color));
	if (!status || fabsf(get_vec3_magnitude(props->orientation) - 1.0f) > EPSILON)
	{
		free(props);
		return (FALSE);
	}
	surface->attributes = props;
	surface->color.red /= 255.0;
	surface->color.green /= 255.0;
	surface->color.blue /= 255.0;
	return (status);
}

t_bool	retrieve_shape(t_scene *scene, t_list *line)
{
	t_surface *surf;
	char **tokens;
	t_bool status;
	int i;

	surf = malloc(sizeof(t_surface));
	tokens = ft_split((char *)(line->content), ' ');
	status = FALSE;
	if (!tokens || !tokens[0])
		return (TRUE);
	if (!ft_strncmp(tokens[0], "sp", 3))
		status = retrieve_sphere(tokens, surf);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		status = retrieve_plane(tokens, surf);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		status = retrieve_cylinder(tokens, surf);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	if (status == FALSE)
	{
		free(surf);
		return (FALSE);
	}
	scene->surfaces = add_surface(&scene->surfaces, surf);
	scene->num_surfaces++;
	return (status);
}