/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:09:49 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:12:25 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_rgb	add_rgb(t_rgb v1, t_rgb v2)
{
	t_rgb	ret;

	ret.red = v1.red + v2.red;
	ret.green = v1.green + v2.green;
	ret.blue = v1.blue + v2.blue;
	return (ret);
}

t_rgb	sub_rgb(t_rgb v1, t_rgb v2)
{
	t_rgb	ret;

	ret.red = v1.red - v2.red;
	ret.green = v1.green - v2.green;
	ret.blue = v1.blue - v2.blue;
	return (ret);
}

t_rgb	mult_rgb(t_rgb v1, t_rgb v2)
{
	t_rgb	ret;

	ret.red = (v1.red * v2.red);
	ret.green = (v1.green * v2.green);
	ret.blue = (v1.blue * v2.blue);
	return (ret);
}

t_rgb	scale_rgb(t_rgb v, float scale)
{
	t_rgb	ret;

	ret.red = v.red * scale;
	ret.green = v.green * scale;
	ret.blue = v.blue * scale;
	return (ret);
}

t_rgb	interpolate(t_rgb r1, t_rgb r2, float amount)
{
	t_rgb	ret;

	ret.red = r1.red + (r2.red - r1.red) * amount;
	ret.green = r1.green + (r2.green - r1.green) * amount;
	ret.blue = r1.blue + (r2.blue - r1.blue) * amount;
	return (ret);
}
