//
// Created by Khalifa Almheiri on 5/29/23.
//

#include "libmath.h"
#include <math.h>

t_hvec  add_hvec(t_hvec hv1, t_hvec hv2)
{
	t_hvec  ret;

	ret.x = hv1.x + hv2.x;
	ret.y = hv1.y + hv2.y;
	ret.z = hv1.z + hv2.z;
	ret.h = hv1.h + hv2.h;
	return (ret);
}

t_hvec  sub_hvec(t_hvec hv1, t_hvec hv2)
{
	t_hvec  ret;

	ret.x = hv1.x - hv2.x;
	ret.y = hv1.y - hv2.y;
	ret.z = hv1.z - hv2.z;
	ret.h = hv1.h - hv2.h;
	return (ret);
}

float   dot_hvec(t_hvec hv1, t_hvec hv2)
{
	float   ret;

	ret = hv1.x * hv2.x + hv1.y * hv2.y + hv1.z * hv2.z + hv1.h * hv2.h;
	return (ret);
}

t_hvec  cross_hvec(t_hvec hv1, t_hvec hv2)
{
	t_hvec  ret;

	ret.x = hv1.y * hv2.z - hv1.z * hv2.y;
	ret.y = hv1.z * hv2.x - hv1.x * hv2.z;
	ret.z = hv1.x * hv2.y - hv1.y * hv2.x;
	ret.h = 0;
	return (ret);
}

t_hvec  scale_hvec(t_hvec hv, float scale)
{
	t_hvec  ret;

	ret.x = hv.x * scale;
	ret.y = hv.y * scale;
	ret.z = hv.z * scale;
	ret.h = hv.h * scale;
	return (ret);
}

t_hvec  normalize_hvec(t_hvec hv)
{
	t_hvec  ret;
	float   mag;

	mag = sqrt(hv.x * hv.x + hv.y * hv.y + hv.z * hv.z + hv.h * hv.h);
	ret.x = hv.x / mag;
	ret.y = hv.y / mag;
	ret.z = hv.z / mag;
	ret.h = hv.h / mag;
	return (ret);
}