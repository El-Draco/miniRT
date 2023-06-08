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

void ft_swap (float *a, float *b)
{
	float temp;

	if (*a < *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

t_hit_record *ray_sphere_intersect(t_ray ray, t_surface sphere, float t0, float t1)
{
	float discriminant;
	float x1;
	float x2;
	t_vec3 neg_cam;
	float radius;
	t_hit_record *rec;

	rec = malloc(sizeof(t_hit_record));
	radius = *(float *)(sphere.attributes);
	neg_cam = scale_vec3(g_scene.camera.origin, -1);
	discriminant = pow(dot_vec3(ray.direction, neg_cam), 2);
	discriminant -= dot_vec3(ray.direction, ray.direction) * ((dot_vec3(add_vec3(g_scene.camera.origin, neg_cam), add_vec3(g_scene.camera.origin, neg_cam))) - (radius * radius));
	if (discriminant < 0)
	{
		rec->distance = INFINITY;
		return (rec);
	}
	x1 = (dot_vec3(scale_vec3(ray.direction, -1), add_vec3(g_scene.camera.origin, neg_cam)) + sqrt(discriminant)) / dot_vec3(ray.direction, ray.direction);
	x2 = (dot_vec3(scale_vec3(ray.direction, -1), add_vec3(g_scene.camera.origin, neg_cam)) - sqrt(discriminant)) / dot_vec3(ray.direction, ray.direction);
	ft_swap(&x1, &x2);
	if (x1 >= t0 && x1 <= t1)
		rec->distance = x1;
	else if (x2 >= t0 && x2 <= t1)
		rec->distance = x2;
	return (rec);
}


t_hit_record hit_surface(t_surface *surf, float t0, float t1)
{

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
		rec = hit_surface(surf, t0, t1);
		if (rec.distance < INFINITY)
		{
			closest = rec;
			t1 = rec.distance;
		}
		surf = surf->next;
	}

	return (closest);
}