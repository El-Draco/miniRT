/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:13:50 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:14:09 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

float	get_vec3_magnitude(t_vec3 vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

t_vec3	normalize_vec3(t_vec3 v)
{
	t_vec3	ret;
	float	mag;

	mag = get_vec3_magnitude(v);
	ret.x = v.x / mag;
	ret.y = v.y / mag;
	ret.z = v.z / mag;
	return (ret);
}
