/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:45:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:13:12 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void	print_vec3(t_vec3 v)
{
	printf(" [ VEC3 (%f, %f, %f) ] ", v.x, v.y, v.z);
}

void	print_rgb(t_rgb rgb)
{
	printf(" [ RGB (%f, %f, %f) ] ", rgb.red, rgb.green, rgb.blue);
}
