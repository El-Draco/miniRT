//
// Created by Zunon on 30/05/2023.
//

#include "../inc/minirt.h"

t_vec3    evaluate_ray(t_ray *ray, float t)
{
    t_vec3	result;

    result = add_vec3(ray->origin, scale_vec3(normalize_vec3(ray->direction), t));
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

t_vec3 construct_basis(t_scene *scene)
{
	// t_vec3 basis;
	t_vec3 w;
	t_vec3 t;
	t_vec3 u;

	w = scale_vec3(scene->camera.orientation, 1);
	t = non_collinear_vec(w);
	u = normalize_vec3(cross_vec3(t, w));
	return (u);
}

float get_focal_distance(float fov)
{
	// WARNING: possible division by 0
	return (1 / tan(fov / 2));
}

void display_ray(t_ray ray)
{
	printf("[ Ray : Direction - ");
	print_vec3(ray.direction);
	printf("\t Origin - ");
	print_vec3(ray.origin);
	printf("\n");
}

#include <stdio.h>

t_ray get_ray(t_scene *scene, unsigned int i, unsigned int j)
{
	// float focal_distance = get_focal_distance(scene);
	float u;
	float v;
	double fov = scene->camera.field_of_view * M_PI / 180;
	t_vec3 direction;
	float l, b, r, t;
	t_ray result;

	t = tan(fov / 2);
	b = -t;
	r = t * WIDTH / HEIGHT;
	l = -r;

	u = l + (((r - l) * (i + 0.5)) / WIDTH) ;
	v = b + ((t - b) * (j + 0.5) / HEIGHT) ;
	result.origin = scene->camera.origin;
	direction = scale_vec3(scene->camera.basis.w, -1);
	direction = add_vec3(scale_vec3(scene->camera.basis.u, u), direction);
	direction = add_vec3(scale_vec3(scene->camera.basis.v, v), direction);
	result.direction = direction;
	return (result);
}

void ft_swap (float *a, float *b)
{
	float temp;

	if (*a > *b)
	{
		temp = *a;
		*a = *b;
		*b = temp;
	}
}

t_hit_record *ray_sphere_intersect(t_scene *scene, t_ray ray, t_surface *sphere, float t0, float t1)
{
	float discriminant;
	float x1;
	float x2;
	float radius;
	t_hit_record *rec;
	t_vec3 p;

	(void)scene;
	rec = malloc(sizeof(t_hit_record));
	radius = *(float *)(sphere->attributes);
	discriminant = pow(dot_vec3(ray.direction, sub_vec3(ray.origin, sphere->origin)), 2);
	discriminant -= dot_vec3(ray.direction, ray.direction) * ((dot_vec3(sub_vec3(ray.origin, sphere->origin), sub_vec3(ray.origin, sphere->origin))) - (radius * radius));
	if (discriminant < 0)
	{
		rec->distance = INFINITY;
		return (rec);
	}
	x1 = (dot_vec3(scale_vec3(ray.direction, -1), sub_vec3(ray.origin, sphere->origin)) + sqrt(discriminant)) / dot_vec3(ray.direction, ray.direction);
	x2 = (dot_vec3(scale_vec3(ray.direction, -1), sub_vec3(ray.origin, sphere->origin)) - sqrt(discriminant)) / dot_vec3(ray.direction, ray.direction);
	ft_swap(&x1, &x2);
	if (x1 >= t0 && x1 <= t1)
		rec->distance = x1;
	else if (x2 >= t0 && x2 <= t1)
		rec->distance = x2;
	else
		rec->distance = 0;
	p = add_vec3(ray.origin, scale_vec3(ray.direction, rec->distance));
	rec->surface = sphere;
	rec->normal = normalize_vec3(scale_vec3(sub_vec3(p, sphere->origin), 1/radius));
	return (rec);
}

t_hit_record *hit_surface(t_scene *scene, t_ray ray, t_surface *surf, float t0, float t1)
{
	if (surf->type == SPHERE)
		return (ray_sphere_intersect(scene, ray, surf, t0, t1));
	return (NULL);
}

t_hit_record *closest_hit(t_scene *scene, t_ray ray, float t0, float t1)
{
	t_hit_record *closest;
	t_surface *surf;
	t_hit_record *rec;

	surf = scene->surfaces;
	closest = malloc(sizeof(t_hit_record));
	closest->distance = INFINITY;
	while (surf)
	{
		rec = hit_surface(scene, ray, surf, t0, t1);
		if (rec && rec->distance > 0 && rec->distance < INFINITY)
		{
			closest = rec;
			t1 = rec->distance;
			closest->surface = surf;
		}
		surf = surf->next;
	}
	return (closest);
}