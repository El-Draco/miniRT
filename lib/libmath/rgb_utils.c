/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 15:12:28 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:17:53 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmath.h"

t_color	rgb_to_color(t_rgb rgb)
{
	t_color	ret;

	ret.alpha = 0;
	ret.red = (int)(rgb.red * 255);
	ret.green = (int)(rgb.green * 255);
	ret.blue = (int)(rgb.blue * 255);
	return (ret);
}

t_rgb	normalize_rgb(t_rgb rgb)
{
	t_rgb	ret;
	float	dummy;

	dummy = rgb.red + rgb.blue + rgb.green;
	if (dummy == 0)
		dummy = 0.00001;
	ret.red = rgb.red / dummy;
	ret.green = rgb.green / dummy;
	ret.blue = rgb.blue / dummy;
	return (ret);
}
