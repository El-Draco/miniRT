//
// Created by Zunon on 30/05/2023.
//

#include "../inc/minirt.h"

t_vec3    evaluate_ray(t_ray *ray, float t)
{
    t_vec3	result;

    result = add_vec3(ray->origin, scale_vec3(ray->direction, t));
    return (result);
}

t_vec3 non_collinear_vec(t_vec3 vector)
{
	unsigned char minimum;

	if (vector.x < vector.y && vector.x < vector.z)
		minimum = 'x';
	else if (vector.y < vector.x && vector.y < vector.z)
		minimum = 'y';
	else
		minimum = 'z';

	if (minimum == 'x')
		return ((t_vec3){vector.x + 1, vector.z, -vector.y});
	else if (minimum == 'y')
		return ((t_vec3){vector.z, vector.y + 1, -vector.x});
	else
		return ((t_vec3){vector.y, -vector.x, vector.z + 1});
}

t_vec3 construct_basis()
{
	// t_vec3 basis;
	t_vec3 w;
	t_vec3 t;
	t_vec3 u;

	w = scale_vec3(g_scene.camera.orientation, -1);
	t = non_collinear_vec(w);
	u = normalize_vec3(cross_vec3(t, w));

	return (u);
}

float get_focal_distance()
{
	// WARNING: possible division by 0
	return (1 / tan(g_scene.camera.field_of_view / 2));
}

t_ray get_ray(unsigned int i, unsigned int j)
{
	float focal_length;
	t_vec3 u;
	t_vec3 v;
	t_vec3 o;

	t_vec3 l, b, r, t;
	t_ray result;

	l = (t_vec3){-1 * sin(g_scene.camera.field_of_view / 2), 0, 0};
	r = (t_vec3){1 * sin(g_scene.camera.field_of_view / 2), 0, 0};
	b = (t_vec3){0, -1 * sin(g_scene.camera.field_of_view / 2), 0};
	t = (t_vec3){0, 1 * sin(g_scene.camera.field_of_view / 2), 0};

	u.x = l.x + ((r.x - l.x) * (i + 0.5) / WIDTH);
	u.y = r.y * (i + 0.5) / WIDTH;
	u.z = 0;
	v.x = t.x + ((t.x - b.x) * (j + 0.5) / HEIGHT);
	v.y = t.y * (j + 0.5) / HEIGHT;
	v.z = 0;
	result.origin = g_scene.camera.origin;
	focal_length = (WIDTH / 2) * get_focal_distance();

	o = scale_vec3(g_scene.camera.basis.w, -1 * focal_length);
	o = add_vec3(o, u);
	o = add_vec3(o, v);
	result.direction = scale_vec3(g_scene.camera.basis.w, -1);
	result.origin = o;
	return (result);
}

// TODO: compute u and v using the following equations
// u = l + (r  - l)(i + 0.5) / WIDTH
// v = b + (t - b)(j + 0.5) / HEIGHT
// where l, r, b, t are the left, right, bottom, top of the view plane

// TODO: compute ray direction using the following equation
// d = -W * focal_length + U * u + V * v
// where W, U, V are the basis vectors of the camera