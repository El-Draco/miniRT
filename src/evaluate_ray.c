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
		return ((t_vec3){1, vector.y + 1.1, vector.z});
	else if (minimum == 'y')
		return ((t_vec3){vector.x + 1, 1.1, vector.z});
	else
		return ((t_vec3){vector.x, vector.y + 1,1.1});
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

void display_ray(t_ray ray)
{
	printf("[ Ray : Direction - ");
	print_vec3(ray.direction);
	printf("\t Origin - ");
	print_vec3(ray.origin);
	printf("\n");
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

t_hit_record closest_hit(t_ray ray, float t0, float t1)
{
	t_hit_record closest;
	t_surface *surf;
	t_hit_record rec;

	surf = g_scene.surfaces;
	closest.distance = INFINITY;
	while (surf)
	{
		rec = hit(surf, t0, t1);
		if (rec.distance < INFINITY)
		{
			closest = rec;
			t1 = rec.distance;
		}
		surf = surf->next;
	}

	return (closest);
}