/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:35:31 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/24 19:59:20 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}



t_bool fequal(float a, float b)
{
	return fabs(a - b) < 0.000001;
}

float ft_max(float x, float y)
{
	if (x < y)
		return (y);
	return (x);
}