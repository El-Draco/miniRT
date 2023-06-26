/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:47:15 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/26 10:26:25 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_hit_record construct_hit_rec(t_hit_record *hrec, float dist, t_vec3 normal, t_surface *surf)
{
	hrec->distance = dist;
	hrec->normal = normal;
	hrec->surface = surf;
	return (*hrec);
}

static t_hit_record hit_surface(t_ray ray, t_surface *surf, float t0, float t1)
{
	if (surf->type == SPHERE)
		return (ray_sphere_intersect(ray, surf, t0, t1));
	if (surf->type == PLANE)
		return (ray_plane_intersect(ray, surf, t0, t1));
	return (ray_cylinder_intersect(ray, surf, t0, t1));
}

t_hit_record	closest_hit(t_scene *scene, t_ray ray, float t0, float t1)
{
	t_hit_record	closest;
	t_surface		*surf;
	t_hit_record	hrec;

	surf = scene->surfaces;
	closest.distance = INFINITY;
	while (surf)
	{
		hrec = hit_surface(ray, surf, t0, t1);
		if (hrec.distance > 0 && hrec.distance != INFINITY)
		{
			closest = hrec;
			t1 = hrec.distance;
			closest.surface = surf;
		}
		surf = surf->next;
	}
	return (closest);
}