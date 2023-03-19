/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 12:10:26 by rriyas            #+#    #+#             */
/*   Updated: 2023/03/19 17:51:57 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

/**
 * @brief			Add 2 vectors
 *
 * @param v1		au + bv + cw
 * @param v2		xu + yv + zw
 * @return t_vec3	v1 + v2 = v3 = (a+x)u + (b+y)v + (c+z)w
 */
t_vec3	add_vec3(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	v3;

	v3.v[0] = v1->v[0] + v1->v[0];
	v3.v[1] = v1->v[1] + v1->v[1];
	v3.v[2] = v1->v[2] + v1->v[2];
	return (v3);
}

/**
 * @brief			Subtract 2 vectors
 *
 * @param v1		au + bv + cw
 * @param v2		xu + yv + zw
 * @return t_vec3	v1 - v2 = v3 = (a-x)u + (b-y)v + (c-z)w
 */
t_vec3	sub_vec3(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	v3;

	v3.v[0] = v1->v[0] - v1->v[0];
	v3.v[1] = v1->v[1] - v1->v[1];
	v3.v[2] = v1->v[2] - v1->v[2];
	return (v3);
}

/**
 * @brief			Compute the dot product of 2 vectors
 *
 * @param v1		au + bv + cw
 * @param v2		xu + yv + zw
 * @return float	Scalar dot product v3 = ax + by + cz
 */
float	dot_vec3(t_vec3 *v1, t_vec3 *v2)
{
	return (v1->v[0] * v2->v[0] + v1->v[1] * v2->v[1] + v1->v[2] * v2->v[2]);
}

/**
 * @brief			Compute the Cross Product of 2 vectors
 *
 * @param	v1		au + bv + cw
 * @param	v2		xu + yv + zw
 * @return	t_vec3	A vector perpendicular to v1 and v2.
 * 					v3 = (bz-cy)u + (cx - az)v + (ay - bx)w
 */
t_vec3	cross_vec3(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3	v3;

	v3.v[0] = (v1->v[1] * v2->v[2]) - (v1->v[2] * v2->v[1]);
	v3.v[1] = (v1->v[2] * v2->v[0]) - (v1->v[0] * v2->v[2]);
	v3.v[2] = (v1->v[0] * v2->v[1]) - (v1->v[1] * v2->v[0]);
	return (v3);
}

/**
 * @brief			Scales a given vector by some factor
 *
 * @param v			Vector to scale
 * @param scale		Magnitude to scale vector by
 * @return t_vec3	Scaled vector v3 = v * scale
 */
t_vec3	scale_vec3(t_vec3 *v, float scale)
{
	t_vec3	v3;

	v3.v[0] = v->v[0] * scale;
	v3.v[1] = v->v[1] * scale;
	v3.v[2] = v->v[2] * scale;
	return (v3);
}
