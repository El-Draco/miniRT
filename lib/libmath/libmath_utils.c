/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:45:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/04 16:14:23 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

void print_vec3(t_vec3 v)
{
	printf(" [ VEC3 (%f, %f, %f) ] ", v.x, v.y, v.z);
}

void print_hvec(t_hvec hv)
{
	printf(" [ HVEC(%f, %f, %f, %f) ] ", hv.h, hv.x, hv.y, hv.z);
}

void print_rgb(t_rgb rgb)
{
	printf(" [ RGB (%d, %d, %d) ] ", rgb.red, rgb.green, rgb.blue);
}

void print_matrix(t_matrix m)
{
	int i;
	int j;

	i = -1;
	j = -1;
	printf("\n[ 4x4 Matrix ]\n");
	while (++i < 4)
	{
		printf("[ ");
		j = 0;
		while (++j < 4)
			printf("%f ", m.m[i][j]);
		printf(" ]\n");
	}
	printf("\n");
}
