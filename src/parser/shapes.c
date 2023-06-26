/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:26:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/26 13:44:55 by rriyas           ###   ########.fr       */
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

static t_surface *retrieve_sphere(char **tokens)
{
	float *diameter;
	t_surface *surf;

	surf = malloc(sizeof(t_surface));
	surf->type = SPHERE;
	surf->origin.x = float_parser(tokens[1]);
	surf->origin.y = float_parser(tokens[2]);
	surf->origin.z = float_parser(tokens[3]);
	diameter = malloc(sizeof(float) * 1);
	*diameter = float_parser(tokens[4]) / 2;
	surf->attributes = diameter;
	surf->color.red = float_parser(tokens[5]) / 255.0;
	surf->color.green = float_parser(tokens[6]) / 255.0;
	surf->color.blue = float_parser(tokens[7]) / 255.0;
	return (surf);
}

static t_surface *retrieve_plane(char **tokens)
{
	t_vec3 *orientation;
	t_vec3 temp;
	t_surface *surf;

	surf = malloc(sizeof(t_surface));
	surf->type = PLANE;
	surf->origin.x = float_parser(tokens[1]);
	surf->origin.y = float_parser(tokens[2]);
	surf->origin.z = float_parser(tokens[3]);
	orientation = malloc(sizeof(t_vec3) * 1);
	orientation->x = float_parser(tokens[4]);
	orientation->y = float_parser(tokens[5]);
	orientation->z = float_parser(tokens[6]);
	surf->attributes = orientation;
	temp = *orientation;
	temp = normalize_vec3(temp);
	*orientation = temp;
	surf->attributes = orientation;
	surf->color.red = float_parser(tokens[7]) / 255.0;
	surf->color.green = float_parser(tokens[8]) / 255.0;
	surf->color.blue = float_parser(tokens[9]) / 255.0;
	return (surf);
}

static t_surface *retrieve_cylinder(char **tokens)
{
	t_cylinder *props;
	t_surface *surf;

	surf = malloc(sizeof(t_surface));
	surf->type = CYLINDER;
	surf->origin.x = float_parser(tokens[1]);
	surf->origin.y = float_parser(tokens[2]);
	surf->origin.z = float_parser(tokens[3]);
	props = malloc(sizeof(t_cylinder) * 1);
	props->orientation.x = float_parser(tokens[4]);
	props->orientation.y = float_parser(tokens[5]);
	props->orientation.z = float_parser(tokens[6]);
	props->diameter = float_parser(tokens[7]);
	props->height = float_parser(tokens[8]);
	surf->attributes = props;
	surf->color.red = float_parser(tokens[9]) / 255.0;
	surf->color.green = float_parser(tokens[10]) / 255.0;
	surf->color.blue = float_parser(tokens[11]) / 255.0;
	return (surf);
}

void	retrieve_shape(t_scene *scene, t_list *line)
{
	t_surface *surf;
	char **tokens;
	int i;

	surf = NULL;
	tokens = ft_split((char *)(line->content), ' ');
	if (!tokens || !tokens[0])
		return ;
	if (!ft_strncmp(tokens[0], "sp", 3))
		surf = retrieve_sphere(tokens);
	else if (!ft_strncmp(tokens[0], "pl", 3))
		surf = retrieve_plane(tokens);
	else if (!ft_strncmp(tokens[0], "cy", 3))
		surf = retrieve_cylinder(tokens);
	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
	scene->surfaces = add_surface(&scene->surfaces, surf);
	scene->num_surfaces++;
}