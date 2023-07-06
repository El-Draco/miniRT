/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:44:42 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:00:22 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static void	ft_swap(float *a, float *b)
{
	float	temp;

	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

static float	get_first_intersection(float x, float y, float t0, float t1)
{
	ft_swap(&x, &y);
	if (x >= t0 && x <= t1)
		return (x);
	if (y >= t0 && y <= t1)
		return (y);
	return (0.0f);
}

static t_vec3	get_sphere_normal(t_ray ray, float distance,
	t_vec3 sphere_origin, float radius)
{
	t_vec3	normal;
	t_vec3	point;

	point = add_vec3(ray.origin, scale_vec3(ray.direction, distance));
	normal = normalize_vec3(scale_vec3(sub_vec3(point, sphere_origin),
				1 / radius));
	return (normal);
}

t_hit_record	ray_sphere_intersect(t_ray ray, t_surface *sphere,
	float t0, float t1)
{
	t_vec3			oc;
	float			b;
	float			c;
	float			h;
	t_hit_record	hrec;

	oc = sub_vec3(ray.origin, sphere->origin);
	b = dot_vec3(oc, ray.direction);
	c = dot_vec3(oc, oc) - ((*(float *)(sphere->attributes))
			/ 2.0 * (*(float *)(sphere->attributes)) / 2.0);
	h = b * b - c;
	if (h < 0.0f)
		return (construct_hit_rec(&hrec, INFINITY, (t_vec3){0, 0, 0}, sphere));
	h = sqrt(h);
	h = get_first_intersection(-b - h, -b + h, t0, t1);
	if (h <= 0.0f)
		return (construct_hit_rec(&hrec, INFINITY, (t_vec3){0, 0, 0}, sphere));
	hrec = construct_hit_rec(&hrec, h,
			get_sphere_normal(ray, h, sphere->origin,
				(*(float *)(sphere->attributes)) / 2.0), sphere);
	return (hrec);
}
