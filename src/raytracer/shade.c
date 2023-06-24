/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:40:00 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:40:19 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

t_rgb illuminate(t_scene *scene, t_ray ray, t_hit_record *hrec)
{
	t_rgb diffuse;
	t_rgb surf_col;
	t_rgb amb;
	t_vec3 point_on_surf = evaluate_ray(&ray, hrec->distance);
	t_vec3 light_ray = sub_vec3(scene->light.origin, point_on_surf);
	t_vec3 light_normal = normalize_vec3(light_ray);
	t_vec3 hit_normal = hrec->normal;
	surf_col = hrec->surface->color;

	amb = scene->ambient.color;
	amb = mult_rgb(amb, surf_col);
	amb = scale_rgb(amb, scene->ambient.intensity);

	diffuse = mult_rgb(scene->light.color, surf_col);
	float visibility = 1.0f;
	t_ray shadow_ray;
	shadow_ray.origin = point_on_surf;
	shadow_ray.direction = scale_vec3(light_normal, 1);
	t_hit_record *shadow_rec = closest_hit(scene, shadow_ray, 0.001, INFINITY);

	if (shadow_rec && shadow_rec->distance >= 0 && shadow_rec->distance != INFINITY)
	{
		// Point is in shadow, reduce visibility
		visibility = 0.0;
	}
	diffuse = scale_rgb(diffuse, visibility * scene->light.intensity * fmaxf(0.0, dot_vec3(hit_normal, light_normal)));
	diffuse = add_rgb(diffuse, amb);
	return (diffuse);
}

t_rgb shade(t_scene *scene, t_hit_record *hrec, t_ray ray)
{
	t_rgb col;

	if (hrec && hrec->distance < INFINITY)
	{
		col = illuminate(scene, ray, hrec);
		return (col);
	}
	return ((t_rgb){0, 0, 0});
}