/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:44:42 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:59:22 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void ft_swap(float *a, float *b)
{
	float temp;

	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

t_hit_record *ray_sphere_intersect(t_scene *scene, t_ray ray, t_surface *sphere, float t0, float t1)
{
	float discriminant;
	float x1;
	float x2;
	float radius;
	t_hit_record *rec;
	t_vec3 p;

	(void)scene;
	rec = malloc(sizeof(t_hit_record));
	radius = *(float *)(sphere->attributes);
	discriminant = pow(dot_vec3(ray.direction, sub_vec3(ray.origin, sphere->origin)), 2);
	discriminant -= (dot_vec3(ray.direction, ray.direction) * ((dot_vec3(sub_vec3(ray.origin, sphere->origin), sub_vec3(ray.origin, sphere->origin))) - (radius * radius)));
	if (discriminant <= 0)
	{
		rec->distance = INFINITY;
		return (rec);
	}
	x1 = (dot_vec3(scale_vec3(ray.direction, -1), sub_vec3(ray.origin, sphere->origin)) + sqrt(discriminant)) / dot_vec3(ray.direction, ray.direction);
	x2 = (dot_vec3(scale_vec3(ray.direction, -1), sub_vec3(ray.origin, sphere->origin)) - sqrt(discriminant)) / dot_vec3(ray.direction, ray.direction);
	ft_swap(&x1, &x2);
	if (x1 >= t0 && x1 <= t1)
		rec->distance = x1;
	else if (x2 >= t0 && x2 <= t1)
		rec->distance = x2;
	else
		rec->distance = 0;
	p = add_vec3(ray.origin, scale_vec3(ray.direction, rec->distance));
	rec->surface = sphere;
	rec->normal = normalize_vec3(scale_vec3(sub_vec3(p, sphere->origin), 1 / radius));
	return (rec);
}