/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:45:56 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/26 12:43:15 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_vec3 get_cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float r)
{
	t_vec3 pa;
	t_vec3 ba;
	float ba_ba;
	float h;

	pa = sub_vec3(p, a);
	ba = sub_vec3(b, a);
	ba_ba = dot_vec3(ba, ba);
	h = dot_vec3(pa, ba) / ba_ba;
	return (scale_vec3(sub_vec3(pa, scale_vec3(ba, h)), 1.0 / r));
}

static void perform_calculations(t_surface *cyl, t_ray ray, t_ray_cyl_data *data, float t0, float t1)
{
	t_cylinder *attr;
	float radius;

	attr = (t_cylinder *)(cyl->attributes);
	radius = attr->diameter / 2;
	data->t0 = t0;
	data->t1 = t1;
	data->a = add_vec3(cyl->origin, scale_vec3(attr->orientation, attr->height / 2));
	data->b = add_vec3(cyl->origin, scale_vec3(attr->orientation, -1 * (attr->height / 2)));
	data->ba = sub_vec3(data->b, data->a);
	data->oc = sub_vec3(ray.origin, data->a);
	data->k2 = dot_vec3(data->ba, data->ba) - dot_vec3(data->ba, ray.direction) * dot_vec3(data->ba, ray.direction);
	data->k1 = dot_vec3(data->ba, data->ba) * dot_vec3(data->oc, ray.direction) - dot_vec3(data->ba, data->oc) * dot_vec3(data->ba, ray.direction);
	data->k0 = dot_vec3(data->ba, data->ba) * dot_vec3(data->oc, data->oc) - dot_vec3(data->ba, data->oc) * dot_vec3(data->ba, data->oc) - radius * radius * dot_vec3(data->ba, data->ba);
	data->h = data->k1 * data->k1 - data->k2 * data->k0;
}

static t_bool intersects_cyl_body(t_ray ray, t_ray_cyl_data *data)
{
	data->t = (-data->k1 - data->h) / data->k2;
	data->y = dot_vec3(data->ba, data->oc) + data->t * dot_vec3(data->ba, ray.direction);
	data->p = add_vec3(ray.origin, scale_vec3(ray.direction, data->t));
	if (data->t >= data->t0 && data->t <= data->t1 && data->y > 0.0 && data->y < dot_vec3(data->ba, data->ba))
		return (TRUE);
	return (FALSE);
}

static t_bool intersects_cyl_caps(t_ray ray, t_ray_cyl_data *data)
{
	float num;
	float denom;

	data->t = 0.0f;
	if (data->y >= 1e-5)
		data->t = dot_vec3(data->ba, data->ba);
	num = data->t - dot_vec3(data->ba, data->oc);
	denom = dot_vec3(data->ba, ray.direction);
	data->t = num / denom;
	if (data->t < data->t0 || data->t > data->t1)
		return (FALSE);
	if (fabsf(data->k1 + data->k2 * data->t) < data->h)
	{
		data->p = add_vec3(ray.origin, scale_vec3(ray.direction, data->t));
		if (data->y < 0.0f)
			data->sign = -1.0f;
		data->sign = 1.0f;
		return (TRUE);
	}
	return (FALSE);
}

t_hit_record ray_cylinder_intersect(t_ray ray, t_surface *cyl, float t0, float t1)
{
	t_ray_cyl_data data;
	t_hit_record hrec;
	t_cylinder *attr;
	float radius;

	attr = (t_cylinder *)(cyl->attributes);
	radius = attr->diameter / 2;
	perform_calculations(cyl, ray, &data, t0, t1);
	if (data.h < 0.0)
		return (construct_hit_rec(&hrec, INFINITY, (t_vec3){0,0,0}, cyl));
	data.h = sqrt(data.h);
	if (intersects_cyl_body(ray, &data))
		return (construct_hit_rec(&hrec, data.t, get_cylinder_normal(data.p, data.a, data.b, radius), cyl));
	if (intersects_cyl_caps(ray, &data))
		return (construct_hit_rec(&hrec, data.t, scale_vec3(attr->orientation, data.sign), cyl));
	return (construct_hit_rec(&hrec, INFINITY, (t_vec3){0, 0, 0}, cyl));
}