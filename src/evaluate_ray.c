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

// t_hit_record *ray_cylinder_intersect(t_scene *scene, t_ray ray, t_surface *plane, float t0, float t1)
// {
// 	t_vec3 ba;
// 	t_vec3 oc;
// 	float baba;
// 	float bard;
// 	float baoc;
// 	float k2 = baba - bard * bard;
// 	float k1 = baba * dot_vec3(oc, ray.direction) - baoc * bard;
// 	float k0 = baba * dot_vec3(oc, oc) - baoc * baoc - radius * radius * baba;
// 	float h = k1 * k1 - k2 * k0;
// 	if (h < 0.0)
// 		return vec4(-1.0); // no intersection
// 	h = sqrt(h);
// 	float t = (-k1 - h) / k2;
// 	// body
// 	float y = baoc + t * bard;
// 	if (y > 0.0 && y < baba)
// 		ret = vec4(t, (sub_vec3(add_vec3(oc,scale_vec3(ray.direction, t)), ba) * y / baba) / radius);
// 	// caps
// 	t = (((y < 0.0) ? 0.0 : baba) - baoc) / bard;
// 	if (abs(k1 + k2 * t) < h)
// 	{
// 		return vec4(t, ba * sign(y) / sqrt(baba));
// 	}
// 	return vec4(-1.0); // no intersection
// }

t_hit_record *ray_cylinder_interesect(t_ray ray, t_surface *surface, float t0, float t1)
{
	t_hit_record *hit_record;
	t_cylinder *attr;

	attr = (t_cylinder *)(surface->attributes);
	hit_record = malloc(sizeof(t_hit_record));
	// Step 1: Calculate the cylinder's axis and half-height
	t_vec3 axis = attr->orientation;
	float half_height = attr->height / 2.0;

	// Step 2: Calculate the ray's direction vector and origin relative to the cylinder's coordinate system
	t_vec3 ray_dir = ray.direction;
	t_vec3 ray_origin = ray.origin;
	ray_origin.x -= attr->orientation.x * half_height;
	ray_origin.y -= attr->orientation.y * half_height;
	ray_origin.z -= attr->orientation.z * half_height;

	// Step 3: Calculate the coefficients of the quadratic equation
	float a = dot_vec3(ray_dir, ray_dir) - pow(dot_vec3(ray_dir, axis), 2);
	float b = 2 * (dot_vec3(ray_dir, ray_origin) - dot_vec3(ray_dir, axis) * dot_vec3(ray_origin, axis));
	float c = dot_vec3(ray_origin, ray_origin) - pow(dot_vec3(ray_origin, axis), 2) - pow(attr->diameter / 2.0, 2);

	// Step 4: Solve the quadratic equation
	float discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant >= 0)
	{
		float x1 = (-b - sqrt(discriminant)) / (2 * a);
		float x2 = (-b + sqrt(discriminant)) / (2 * a);
		float t = fmin(x1, x2);
		if (t < t0 || t > t1)
		{
			hit_record = malloc(sizeof(t_hit_record));
			hit_record->surface = surface;
			hit_record->distance = INFINITY;
			hit_record->normal = (t_vec3){0, 0, 0};
			return (hit_record);
		}
		// Step 5: Check if the intersection point is within the capped cylinder
		t_vec3 intersection = {
			ray.origin.x + ray_dir.x * t,
			ray.origin.y + ray_dir.y * t,
			ray.origin.z + ray_dir.z * t};

		float proj = dot_vec3(intersection, axis);

		t_bool intersected = FALSE;
		t_vec3 normal;

		// Check if the intersection point lies within the open ends of the cylinder
		if (proj >= -half_height && proj <= half_height)
		{
			intersected = TRUE;
			normal = (t_vec3){
				intersection.x - attr->orientation.x * proj,
				intersection.y - attr->orientation.y * proj,
				intersection.z - attr->orientation.z * proj};
		}

		// Check if the intersection point lies on the bottom cap of the cylinder
		t_vec3 bottom_cap_center = attr->orientation;
		bottom_cap_center.x *= -half_height;
		bottom_cap_center.y *= -half_height;
		bottom_cap_center.z *= -half_height;

		float distance_to_bottom_cap_center = dot_vec3(ray.origin, axis) - dot_vec3(bottom_cap_center, axis);
		t_vec3 point_on_bottom_cap = {
			ray.origin.x - bottom_cap_center.x - distance_to_bottom_cap_center * axis.x,
			ray.origin.y - bottom_cap_center.y - distance_to_bottom_cap_center * axis.y,
			ray.origin.z - bottom_cap_center.z - distance_to_bottom_cap_center * axis.z};

		float distance_to_point_on_bottom_cap = sqrt(pow(point_on_bottom_cap.x - ray.origin.x, 2) + pow(point_on_bottom_cap.y - ray.origin.y, 2) + pow(point_on_bottom_cap.z - ray.origin.z, 2));

		if (distance_to_point_on_bottom_cap <= attr->diameter / 2.0)
		{
			if (t >= t0 && t<= t1 && (t >= distance_to_bottom_cap_center || intersected == FALSE))
			{
				intersected = TRUE;
				t = -distance_to_bottom_cap_center;
				normal = attr->orientation;
			}
		}

		// Check if the intersection point lies on the top cap of the cylinder
		t_vec3 top_cap_center = attr->orientation;
		top_cap_center.x *= half_height;
		top_cap_center.y *= half_height;
		top_cap_center.z *= half_height;

		float distance_to_top_cap_center = dot_vec3(ray.origin, axis) - dot_vec3(top_cap_center, axis);
		t_vec3 point_on_top_cap = {
			ray.origin.x - top_cap_center.x - distance_to_top_cap_center * axis.x,
			ray.origin.y - top_cap_center.y - distance_to_top_cap_center * axis.y,
			ray.origin.z - top_cap_center.z - distance_to_top_cap_center * axis.z};

		float distance_to_point_on_top_cap = sqrt(pow(point_on_top_cap.x - ray.origin.x, 2) + pow(point_on_top_cap.y - ray.origin.y, 2) + pow(point_on_top_cap.z - ray.origin.z, 2));

		if (distance_to_point_on_top_cap <= attr->diameter / 2.0)
		{
			if ((t >= t0 && t <= t1) && (t >= distance_to_top_cap_center || intersected == FALSE))
			{
				intersected = TRUE;
				t = -distance_to_top_cap_center;
				normal = attr->orientation;
			}
		}
		if (intersected && t >=0)
		{
			hit_record = malloc(sizeof(t_hit_record));
			hit_record->surface = surface;
			hit_record->distance = t;
			hit_record->normal = normal;
		}
	}

	// Step 6: Handle the case when there is no intersection
	if (hit_record == NULL)
	{
		hit_record = malloc(sizeof(t_hit_record));
		hit_record->surface = surface;
		hit_record->distance = INFINITY;
		hit_record->normal = (t_vec3){0, 0, 0};
	}

	return hit_record;
}

t_hit_record *hit_surface(t_scene *scene, t_ray ray, t_surface *surf, float t0, float t1)
{
	if (surf->type == SPHERE)
		return (ray_sphere_intersect(scene, ray, surf, t0, t1));
	if (surf->type == PLANE)
		return (ray_plane_intersect(scene, ray, surf, t0, t1));
	if (surf->type == CYLINDER)
		return (ray_cylinder_interesect(ray, surf, t0, t1));
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