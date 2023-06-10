//
// Created by Khalifa Almheiri on 5/29/23.
//

#include "libmath.h"

t_rgb add_rgb(t_rgb v1, t_rgb v2)
{
	t_rgb  ret;

	ret.red = v1.red + v2.red;
	ret.green = v1.green + v2.green;
	ret.blue = v1.blue + v2.blue;
	return (ret);
}

t_rgb sub_rgb(t_rgb v1, t_rgb v2)
{
	t_rgb  ret;

	ret.red = v1.red - v2.red;
	ret.green = v1.green - v2.green;
	ret.blue = v1.blue - v2.blue;
	return (ret);
}

t_rgb mult_rgb(t_rgb v1, t_rgb v2)
{
	t_rgb  ret;

	ret.red = v1.red * v2.red;
	ret.green = v1.green * v2.green;
	ret.blue = v1.blue * v2.blue;
	return (ret);
}

t_rgb scale_rgb(t_rgb v, float scale)
{
	t_rgb  ret;

	ret.red = v.red * scale;
	ret.green = v.green * scale;
	ret.blue = v.blue * scale;
	return (ret);
}

t_rgb interpolate(t_rgb r1, t_rgb r2, float amount)
{
	t_rgb  ret;

	ret.red = r1.red + (r2.red - r1.red) * amount;
	ret.green = r1.green + (r2.green - r1.green) * amount;
	ret.blue = r1.blue + (r2.blue - r1.blue) * amount;
	return (ret);
}

t_color	rgb_to_color(t_rgb rgb)
{
	t_color ret;

	ret.alpha = 255;
	ret.red = (int)(rgb.red * 255);
	ret.green = (int)(rgb.green * 255);
	ret.blue = (int)(rgb.blue * 255);
	if (ret.red > 255)
		ret.red = 255;
	if (ret.green > 255)
		ret.green = 255;
	if (ret.blue > 255)
		ret.blue = 255;
	if (ret.red < 0)
		ret.red = 0;
	if (ret.green < 0)
		ret.green = 0;
	if (ret.blue < 0)
		ret.blue = 0;
	return (ret);
}