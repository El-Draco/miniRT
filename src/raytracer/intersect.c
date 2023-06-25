/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:47:15 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/25 16:00:58 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_hit_record *no_intersection(t_hit_record *hrec)
{
	hrec->distance = INFINITY;
	hrec->normal = (t_vec3){0, 0, 0};
	hrec->surface = NULL;
	return (hrec);
}

	static t_hit_record *hit_surface(t_ray ray, t_surface *surf, float t0, float t1)
{
	if (surf->type == SPHERE)
		return (ray_sphere_intersect(ray, surf, t0, t1));
	if (surf->type == PLANE)
		return (ray_plane_intersect(ray, surf, t0, t1));
	if (surf->type == CYLINDER)
		return (ray_cylinder_intersect(ray, surf, t0, t1));
	return (NULL);
}

t_hit_record	*closest_hit(t_scene *scene, t_ray ray, float t0, float t1)
{
	t_hit_record	*closest;
	t_surface		*surf;
	t_hit_record	*rec;

	surf = scene->surfaces;
	closest = malloc(sizeof(t_hit_record));
	closest->distance = INFINITY;
	while (surf)
	{
		rec = hit_surface(ray, surf, t0, t1);
		if (rec && rec->distance > 0 && rec->distance < INFINITY)
		{
			closest = rec;
			t1 = rec->distance;
			closest->surface = surf;
		}
		surf = surf->next;
	}
	return (closest);
}