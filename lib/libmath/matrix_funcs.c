//
// Created by Khalifa Almheiri on 5/29/23.
//

#include "libmath.h"

t_matrix mat_multiply(t_matrix m1, t_matrix m2)
{
	t_matrix ret;
	int i;
	int j;
	int k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			ret.m[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				ret.m[i][j] += m1.m[i][k] * m2.m[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (ret);
}

t_vec3 transform_location(t_matrix kernel, t_vec3 v)
{
	t_vec3 ret;

	ret.x = kernel.m[0][0] * v.x + kernel.m[0][1] * v.y + kernel.m[0][2] * v.z + kernel.m[0][3];
	ret.y = kernel.m[1][0] * v.x + kernel.m[1][1] * v.y + kernel.m[1][2] * v.z + kernel.m[1][3];
	ret.z = kernel.m[2][0] * v.x + kernel.m[2][1] * v.y + kernel.m[2][2] * v.z + kernel.m[2][3];
	return (ret);
}

t_vec3 transform_direction(t_matrix kernel, t_vec3 v)
{
	t_vec3 ret;

	ret.x = kernel.m[0][0] * v.x + kernel.m[0][1] * v.y + kernel.m[0][2] * v.z;
	ret.y = kernel.m[1][0] * v.x + kernel.m[1][1] * v.y + kernel.m[1][2] * v.z;
	ret.z = kernel.m[2][0] * v.x + kernel.m[2][1] * v.y + kernel.m[2][2] * v.z;
	return (ret);
}

t_vec3 transform_surface_normal(t_matrix kernel, t_vec3 v)
{
	t_vec3 ret;

	ret.x = kernel.m[0][0] * v.x + kernel.m[1][0] * v.y + kernel.m[2][0] * v.z;
	ret.y = kernel.m[0][1] * v.x + kernel.m[1][1] * v.y + kernel.m[2][1] * v.z;
	ret.z = kernel.m[0][2] * v.x + kernel.m[1][2] * v.y + kernel.m[2][2] * v.z;
	return (ret);
}