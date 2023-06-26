/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:45:03 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/26 10:27:35 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_hit_record ray_plane_intersect(t_ray ray, t_surface *plane, float t0, float t1)
{
	t_hit_record hrec;
	t_vec3 normal;
	float denom;
	t_vec3 pl;
	float t;
	float sign;

	normal = *(t_vec3 *)(plane->attributes);
	denom = dot_vec3(normal, ray.direction);
	if (fabsf(denom) < 0.000001f)
		return (construct_hit_rec(&hrec, INFINITY, (t_vec3){0, 0, 0}, plane));
	pl = sub_vec3(plane->origin, ray.origin);
	t = dot_vec3(pl, normal) / denom;
	sign = 1.0f;
	hrec.distance = INFINITY;
	if (t >= t0 && t <= t1)
	{
		hrec.surface = plane;
		if (denom > 0)
			sign = -1.0f;
		hrec.normal = scale_vec3(normal, sign);
		hrec.distance = t;
	}
	return hrec;
}