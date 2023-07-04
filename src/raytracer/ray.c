/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 14:13:03 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 18:59:00 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vec3	evaluate_ray(t_ray *ray, float t)
{
    t_vec3	result;

    result = add_vec3(ray->origin, scale_vec3(normalize_vec3(ray->direction), t));
    return (result);
}

static float	get_focal_distance(float fov)
{
	return (1 / tan((fov + 0.0001) / 2));
}

t_ray get_ray(t_scene *scene, unsigned int i, unsigned int j)
{
	float	u;
	float	v;
	double	fov;
	t_vec3	direction;
	t_ray	result;
	float	vertices[4]; // l, b, r, t

	fov = scene->camera.field_of_view *M_PI / 180;
	vertices[3] = tan(fov / 2);
	vertices[1] = -vertices[3];
	vertices[2] = vertices[3] * WIDTH / HEIGHT;
	vertices[0] = -vertices[2];
	u = vertices[0] + (((vertices[2] - vertices[0]) * (i + 0.5)) / WIDTH) ;
	v = vertices[1] + ((vertices[3] - vertices[1]) * (j + 0.5) / HEIGHT) ;
	result.origin = scene->camera.origin;
	direction = scale_vec3(scene->camera.basis.w, -1 * get_focal_distance(fov));
	direction = add_vec3(scale_vec3(scene->camera.basis.u, u), direction);
	direction = add_vec3(scale_vec3(scene->camera.basis.v, v), direction);
	result.direction = normalize_vec3(direction);
	return (result);
}
