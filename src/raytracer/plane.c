/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:45:03 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:58:05 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_hit_record *ray_plane_intersect(t_scene *scene, t_ray ray, t_surface *plane, float t0, float t1)
{
	t_hit_record *hrec;
	t_vec3 normal;
	float denom;
	t_vec3 pl;
	float t;
	(void)scene;
	hrec = malloc(sizeof(t_hit_record));
	normal = *(t_vec3 *)(plane->attributes);
	denom = -1 * dot_vec3(normal, ray.direction);
	if (denom > 1e-9)
	{
		pl = sub_vec3(ray.origin, plane->origin);
		t = dot_vec3(pl, normal) / denom;
		if (t >= t0 && t <= t1)
		{
			hrec->surface = plane;
			hrec->normal = normal;
			hrec->distance = t;
		}
		if (t >= 0)
			return (hrec);
	}
	hrec->distance = INFINITY;
	return hrec;
}