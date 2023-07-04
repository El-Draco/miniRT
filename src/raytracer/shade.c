/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shade.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:40:00 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 17:41:58 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"


static t_rgb	calculate_ambient_and_diffuse(t_scene *scene, t_hit_record *hrec)
{
	t_rgb	amb_diff;
	t_rgb	diffuse;
	t_rgb	surf_col;
	t_rgb	amb;

	surf_col = hrec->surface->color;
	amb = scene->ambient.color;
	amb = mult_rgb(amb, surf_col);
	amb = scale_rgb(amb, scene->ambient.intensity);
	diffuse = mult_rgb(scene->light.color, surf_col);
	amb_diff = add_rgb(diffuse, amb);
	return (amb_diff);
}

static float	add_shadows(t_scene *scene, t_vec3 point, t_vec3 light_ray, t_hit_record *hrec)
{
	float			visibility;
	t_ray			shadow_ray;
	t_hit_record	shadow_rec;

	visibility = 1.0f;
	shadow_ray.direction = scale_vec3(light_ray, 1);
	shadow_ray.origin = add_vec3(point, scale_vec3(shadow_ray.direction, EPSILON));
	shadow_rec = closest_hit(scene, shadow_ray, 0.0001, hrec->distance);
	if (shadow_rec.distance > 0 && shadow_rec.distance < hrec->distance)
		visibility = 0.0f;
	return (visibility);
}

static t_rgb	illuminate(t_scene *scene, t_ray ray, t_hit_record *hrec)
{
	t_vec3	point_on_surf;
	t_vec3	light_ray;
	t_vec3	hit_normal;
	t_rgb	light;
	float	visibility;

	point_on_surf = evaluate_ray(&ray, hrec->distance);
	light_ray = sub_vec3(scene->light.origin, point_on_surf);
	light_ray = normalize_vec3(light_ray);
	hit_normal = hrec->normal;
	visibility = add_shadows(scene, point_on_surf, light_ray, hrec);
	if (visibility <= 0.0f)
	{
		light = scene->ambient.color;
		light = mult_rgb(light, hrec->surface->color);
		light = scale_rgb(light, scene->ambient.intensity * 0.2);
		return (light);
	}
	light = calculate_ambient_and_diffuse(scene, hrec);
	light = scale_rgb(light, visibility * scene->light.intensity * fmaxf(0.0, dot_vec3(hit_normal, light_ray)));
	return (light);
}

t_rgb shade(t_scene *scene, t_hit_record *hrec, t_ray ray)
{
	t_rgb	col;

	if (hrec && hrec->distance != INFINITY)
	{
		col = illuminate(scene, ray, hrec);
		return (col);
	}
	return ((t_rgb){0, 0, 0});
}