/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:10:26 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:14:59 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_vec3	add_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vec3	sub_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

float	dot_vec3(t_vec3 v1, t_vec3 v2)
{
	float	ret;

	ret = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	return (ret);
}

t_vec3	cross_vec3(t_vec3 v1, t_vec3 v2)
{
	t_vec3	ret;

	ret.x = v1.y * v2.z - v1.z * v2.y;
	ret.y = v1.z * v2.x - v1.x * v2.z;
	ret.z = v1.x * v2.y - v1.y * v2.x;
	return (ret);
}

t_vec3	scale_vec3(t_vec3 v, float scale)
{
	t_vec3	ret;

	ret.x = v.x * scale;
	ret.y = v.y * scale;
	ret.z = v.z * scale;
	return (ret);
}
