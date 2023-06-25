/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:45:56 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/25 21:06:24 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_vec3 get_cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float r)
{
	t_vec3 pa;
	t_vec3 ba;
	float ba_ba;
	float pa_ba;
	float h;

	pa = sub_vec3(p, a);
	ba = sub_vec3(b, a);
	ba_ba = dot_vec3(ba, ba);
	pa_ba = dot_vec3(pa, ba);
	h = dot_vec3(pa, ba) / ba_ba;
	return (scale_vec3(sub_vec3(pa, scale_vec3(ba, h)), 1.0 / r));
}

float ray_cyl_cap_intersect(t_surface *surface, t_hit_record *hrec)
{
	// caps
	t = ((((y < 1e-5)) ? 0.0 : baba) - baoc) / bard;
	if (t < t0 || t > t1)
		return (no_intersection(hrec));
	if (fabsf(k1 + k2 * t) < h)
	{
		float sign = (y >= 1e-5) ? 1.0f : -1.0f;
		hrec->distance = t;
		p = add_vec3(ray.origin, scale_vec3(ray.direction, t));
		hrec->normal = scale_vec3(attr->orientation, sign);
		// return (hrec);
	}
}

float ray_cyl_body_intersect()
{
}

t_hit_record *ray_cylinder_intersect(t_ray ray, t_surface *cyl, float t0, float t1)
{
	t_hit_record *hrec;
	t_vec3 ret;
	t_vec3 oc;
	t_hvec ans;
	t_vec3 p, a, b;
	(void)t1;
	(void)t0;

	t_cylinder *attr = (t_cylinder *)(cyl->attributes);
	a = add_vec3(cyl->origin, scale_vec3(attr->orientation, attr->height / 2));
	b = add_vec3(cyl->origin, scale_vec3(attr->orientation, -1 * (attr->height / 2)));
	hrec = malloc(sizeof(t_hit_record));
	float radius = attr->diameter / 2;
	t_vec3 ba = sub_vec3(b, a);
	oc = sub_vec3(ray.origin, a);
	float baba = dot_vec3(ba, ba);
	float bard = dot_vec3(ba, ray.direction);
	float baoc = dot_vec3(ba, oc);
	float k2 = baba - bard * bard;
	float k1 = baba * dot_vec3(oc, ray.direction) - baoc * bard;
	float k0 = baba * dot_vec3(oc, oc) - baoc * baoc - radius * radius * baba;
	float h = k1 * k1 - k2 * k0;
	if (h < 1e-5)
		return (no_intersection(hrec));
	h = sqrt(h);
	float t = (-k1 - h) / k2;
	// body
	float y = baoc + t * bard;
	hrec->surface = cyl;
	if (y > 1e-5 && y < baba)
	{
		ret = scale_vec3(sub_vec3(add_vec3(oc, scale_vec3(ray.direction, t)), scale_vec3(ba, y / baba)), 1.0 / radius);
		ans = (t_hvec){t, ret.x, ret.y, ret.z};
		hrec->distance = t;
		p = add_vec3(ray.origin, scale_vec3(ray.direction, t));
		hrec->normal = get_cylinder_normal(p, a, b, radius);
		// return (hrec);
	}


	return (hrec); // no intersection
}