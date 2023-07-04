/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:47:03 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/27 09:35:53 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

static t_vec3	get_non_collinear_vec(t_vec3 vector)
{
	unsigned char	minimum;

	if (vector.x < vector.y && vector.x < vector.z)
		minimum = 'x';
	else if (vector.y < vector.x && vector.y < vector.z)
		minimum = 'y';
	else
		minimum = 'z';
	if (minimum == 'x')
		return ((t_vec3){0.1, vector.y + 0.1, vector.z});
	else if (minimum == 'y')
		return ((t_vec3){vector.x + 0.1, 0.1, vector.z});
	return ((t_vec3){vector.x, vector.y + 0.1, 0.1});
}

static t_vec3	construct_basis(t_scene *scene)
{
	t_vec3 w;
	t_vec3 t;
	t_vec3 u;

	w = normalize_vec3(scale_vec3(scene->camera.orientation, -1));
	t = normalize_vec3(get_non_collinear_vec(w));
	u = normalize_vec3(cross_vec3(w, t));
	return (u);
}

void	set_up_camera(t_scene *scene)
{
	scene->camera.basis.w = normalize_vec3(scale_vec3(scene->camera.orientation, -1));
	scene->camera.basis.u = construct_basis(scene);
	scene->camera.basis.v = normalize_vec3(cross_vec3(scene->camera.basis.w, scene->camera.basis.u));
}