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

	w = normalize_vec3(scale_vec3(scene->camera.orientation, -1));
	t = normalize_vec3(non_collinear_vec(w));
	u = normalize_vec3(cross_vec3(w, t));
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
	direction = scale_vec3(scene->camera.basis.w, -1 * get_focal_distance(fov));
	direction = add_vec3(scale_vec3(scene->camera.basis.u, u), direction);
	direction = add_vec3(scale_vec3(scene->camera.basis.v, v), direction);
	result.direction = normalize_vec3(direction);
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

t_bool fequal(float a, float b)
{
	return fabs(a - b) < 0.000001;
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
	discriminant -= (dot_vec3(ray.direction, ray.direction) * ((dot_vec3(sub_vec3(ray.origin, sphere->origin), sub_vec3(ray.origin, sphere->origin))) - (radius * radius)));
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

t_hit_record *ray_plane_intersect(t_scene *scene, t_ray ray, t_surface *plane, float t0, float t1)
{
	t_hit_record *hrec;
	t_vec3 normal;
	float denom;
	t_vec3 pl;
	float t;
	(void)scene;
	hrec = malloc(sizeof(t_hit_record));
	normal = *(t_vec3 *)(plane->attributes);
	denom = -1 * dot_vec3(normal, ray.direction);
	if (denom > 1e-9)
	{
		pl = sub_vec3(ray.origin, plane->origin);
		t = dot_vec3(pl, normal) / denom;
		if (t >= t0 && t <= t1)
		{
			hrec->surface = plane;
			hrec->normal = normal;
			hrec->distance = t;
		}
		if (t >= 0)
			return (hrec);
	}

	hrec->distance = INFINITY;
	return hrec;
}

t_vec3 get_cylinder_normal(t_vec3 p, t_vec3 a, t_vec3 b, float r)
{
	t_vec3 pa;
	t_vec3 ba;
	float ba_ba;
	float pa_ba;
	float h;

	pa = sub_vec3(p, a);
	ba = sub_vec3(b, a);
	ba_ba = dot_vec3(ba, ba);
	pa_ba = dot_vec3(pa, ba);
	h = dot_vec3(pa, ba) / ba_ba;
	return (scale_vec3(sub_vec3(pa, scale_vec3(ba, h)), 1.0/r));
}
t_vec3 hvec_to_vec3(t_hvec hvec)
{
	t_vec3 vec3;
	// Check if homogeneous coordinate is not zero to avoid division by zero
	if (hvec.h != 0)
	{
		// Perform dehomogenization
		vec3.x = hvec.x / hvec.h;
		vec3.y = hvec.y / hvec.h;
		vec3.z = hvec.z / hvec.h;
	}
	else
	{
		// Handle the case where the homogeneous coordinate is zero
		printf("Error: Division by zero encountered!\n");
		// Set the resulting 3D vector to some default value or handle the error accordingly
		vec3.x = 0;
		vec3.y = 0;
		vec3.z = 0;
	}
	return vec3;
}
t_hit_record *ray_cylinder_intersect(t_scene *scene, t_ray ray, t_surface *cyl, float t0, float t1)
{
	t_hit_record *hrec;
	t_vec3 ret;
	t_vec3 oc;
	t_hvec ans;
	t_vec3 p,a,b;
	(void)scene;
	(void)t0;
	(void)t1;
	t_cylinder *attr = (t_cylinder *)(cyl->attributes);
	a = add_vec3(cyl->origin, scale_vec3(attr->orientation, attr->height / 2));
	b = add_vec3(cyl->origin, scale_vec3(attr->orientation, -1 * (attr->height / 2)));
	hrec = malloc(sizeof(t_hit_record));
	float radius = attr->diameter / 2;
	t_vec3 ba = sub_vec3(b, a);
	oc = sub_vec3(ray.origin, a);
	float baba = dot_vec3(ba,ba);
	float bard = dot_vec3(ba, ray.direction);
	float baoc = dot_vec3(ba, oc);
	float k2 = baba - bard * bard;
	float k1 = baba * dot_vec3(oc, ray.direction) - baoc * bard;
	float k0 = baba * dot_vec3(oc, oc) - baoc * baoc - radius * radius * baba;
	float h = k1 * k1 - k2 * k0;
	if (h < 0.0)
	{
		hrec->surface = cyl;
		hrec->distance = INFINITY;
		hrec->normal = (t_vec3){0, 0, 0};
	} // no intersection
	h = sqrt(h);
	float t = (-k1 - h) / k2;
	// body
	float y = baoc + t * bard;
	hrec->surface = cyl;
	if (y > 0.0 && y < baba)
	{
		ret = scale_vec3(sub_vec3(add_vec3(oc,scale_vec3(ray.direction, t)), scale_vec3(ba, y / baba)), 1.0/radius);
		ans = (t_hvec){t, ret.x, ret.y, ret.z};
		hrec->distance = t;
		p = add_vec3(ray.origin, scale_vec3(ray.direction, t));
		hrec->normal = get_cylinder_normal(p, a, b, radius);
		return (hrec);
	}
	// caps
	t = ((((y < 0.0)) ? 0.0 : baba) - baoc) / bard;
	if (fabsf(k1 + k2 * t) < h)
	{
		float sign = (y >= 0.0f) ? 1.0f : -1.0f;
		ret = scale_vec3(ba, sign / sqrt(baba));
		ans = (t_hvec){t, ret.x, ret.y, ret.z};
		hrec->distance = t;
		p = add_vec3(ray.origin, scale_vec3(ray.direction, t));
		hrec->normal = scale_vec3(attr->orientation, -1 * sign);
		return (hrec);
	}

	return (hrec); // no intersection
}


t_hit_record *hit_surface(t_scene *scene, t_ray ray, t_surface *surf, float t0, float t1)
{
	if (surf->type == SPHERE)
		return (ray_sphere_intersect(scene, ray, surf, t0, t1));
	if (surf->type == PLANE)
		return (ray_plane_intersect(scene, ray, surf, t0, t1));
	if (surf->type == CYLINDER)
		return (ray_cylinder_intersect(scene, ray, surf, t0, t1));
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