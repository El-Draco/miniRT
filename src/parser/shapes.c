/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/05 15:18:04 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_surface *add_surface(t_surface **surfaces, t_surface *surf)
{
	t_surface *iterator;

	iterator = NULL;
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
	t_bool valid;

	surface->type = SPHERE;
	diameter = malloc(sizeof(float) * 1);
	valid = parse_identifier(tokens, "sp") &&
				parse_vec3(tokens + 1, &(surface->origin)) &&
				parse_float(tokens + 6, diameter) &&
				parse_rgb(tokens + 7, &(surface->color));
	if (!valid || *diameter <= 0.0f || tokens[12])
	{
		free(diameter);
		return (FALSE);
	}
	surface->attributes = diameter;
	surface->color.red /= 255.0;
	surface->color.green /= 255.0;
	surface->color.blue /= 255.0;
	return (valid);
}

static t_bool retrieve_plane(char **tokens, t_surface *surface)
{
	t_vec3 *orientation;
	t_bool valid;

	surface->type = PLANE;
	orientation = malloc(sizeof(t_vec3) * 1);
	valid = parse_identifier(tokens, "pl") &&
				parse_vec3(tokens + 1, &(surface->origin)) &&
				parse_vec3(tokens + 6, &(*orientation)) &&
				parse_rgb(tokens + 11, &(surface->color));
	if (!valid || fabsf(get_vec3_magnitude(*orientation) - 1.0f) > EPSILON || tokens[16])
	{
		free(orientation);
		return (FALSE);
	}
	surface->attributes = orientation;
	surface->color.red /= 255.0;
	surface->color.green /= 255.0;
	surface->color.blue /= 255.0;
	return (valid);
}

static t_bool retrieve_cylinder(char **tokens, t_surface *surface)
{
	t_cylinder *props;
	t_bool valid;

	surface->type = CYLINDER;
	props = malloc(sizeof(t_cylinder) * 1);
	valid = parse_identifier(tokens, "cy") &&
				parse_vec3(tokens + 1, &(surface->origin)) &&
				parse_vec3(tokens + 6, &(props->orientation)) &&
				parse_float(tokens + 11, &(props->diameter)) &&
				parse_float(tokens + 12, &(props->height)) &&
				parse_rgb(tokens + 13, &(surface->color));
	if (!valid || fabsf(get_vec3_magnitude(props->orientation) - 1.0f) > EPSILON ||
		props->diameter <= 0.0f || props->height <= 0.0f || tokens[18])
	{
		free(props);
		return (FALSE);
	}
	surface->attributes = props;
	surface->color.red /= 255.0;
	surface->color.green /= 255.0;
	surface->color.blue /= 255.0;
	return (valid);
}

t_bool	retrieve_shape(t_scene *scene, t_list *line)
{
	t_surface *surf;
	char **tokens;
	t_bool valid;
	int i;

	surf = malloc(sizeof(t_surface));
	tokens = ft_split((char *)(line->content), ' ');
	valid = FALSE;
	if (!tokens || !tokens[0])
	{
		i = -1;
		while (tokens[++i])
			free(tokens[i]);
		free(tokens);
	}
	if (!ft_strncmp(tokens[0], "sp", 3))
		valid = retrieve_sphere(tokens, surf);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		valid = retrieve_plane(tokens, surf);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		valid = retrieve_cylinder(tokens, surf);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	if (!valid)
	{
		free(surf);
		return (FALSE);
	}
	scene->surfaces = add_surface(&scene->surfaces, surf);
	scene->num_surfaces++;
	return (valid);
}