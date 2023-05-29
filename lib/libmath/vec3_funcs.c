/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:10:26 by rriyas            #+#    #+#             */
/*   Updated: 2023/03/17 19:14:43 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"
#include <math.h>

t_vec3  add_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3  ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vec3  sub_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3  ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

float   dot_vec3(t_vec3 v1, t_vec3 v2)
{
	float   ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_vec3  cross_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3  ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vec3  scale_vec3(t_vec3 v, float scale)
{
	t_vec3  ret;

	ret.x = v.x * scale;
	ret.y = v.y * scale;
	ret.z = v.z * scale;
	return (ret);
}

t_vec3  normalize_vec3(t_vec3 v)
{
	t_vec3  ret;
	float   mag;

	mag = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	ret.x = v.x / mag;
	ret.y = v.y / mag;
	ret.z = v.z / mag;
	return (ret);
}