/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:53:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/05 21:34:59 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "../lib/minilibx_opengl_20191021/mlx.h"
#include "../lib/libmath/libmath.h"
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>

#define HEIGHT 720
#define WIDTH 1080
#define EPSILON 1e-4
typedef struct s_image
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_image;

// t_material_phong {TBD}

typedef struct s_ambi_light
{
	float intensity;
	t_rgb color;
} t_ambi_light;

typedef struct s_basis
{
	t_vec3 u;
	t_vec3 v;
	t_vec3 w;
} t_basis;

typedef struct s_camera
{
	t_vec3 origin;
	t_vec3 orientation;
	float field_of_view;
	t_basis basis;
} t_camera;

typedef struct s_point_light
{
	t_vec3 origin;
	float intensity;
	t_rgb color;
} t_point_light;

typedef enum e_shape
{
	SPHERE,
	PLANE,
	CYLINDER
} t_shape;

typedef struct s_surface
{
	t_vec3 origin;
	t_rgb color;
	void *attributes;
	t_shape type;
	struct s_surface *next;
} t_surface;

// NOTE: attributes will point to a float (diameter) if sphere
// t_vec3 (orientation) if plane,
// t_cylinder if cylinder
typedef struct s_cylinder
{
	t_vec3 orientation;
	float diameter;
	float height;
} t_cylinder;

typedef struct s_scene
{
	void *mlx;
	void *window;
	t_image image;
	t_ambi_light ambient;
	t_camera camera;
	t_point_light light;
	t_surface *surfaces;
	size_t num_surfaces;
} t_scene;

typedef struct s_ray
{
	t_vec3 origin;
	t_vec3 direction;
} t_ray;

typedef struct s_hit_record
{
	t_surface *surface;
	float distance;
	t_vec3 normal;
} t_hit_record;

typedef struct s_ray_cyl_data
{
	t_vec3 p;
	t_vec3 a;
	t_vec3 b;
	t_vec3 ba;
	t_vec3 oc;
	float k0;
	float k1;
	float k2;
	float h;
	float y;
	float t0;
	float t1;
	float t;
	float sign;
} t_ray_cyl_data;

void render_scene(t_scene *scene);

// parser:
int parser(t_scene *scene, int argc, char **argv);
char *input_sanitizer(char *line);
float float_parser(char *s);
t_bool retrieve_amb_light(t_scene *scene, char *line);
t_bool retrieve_point_light(t_scene *scene, char *line);
t_bool retrieve_shape(t_scene *scene, t_list *line);
char *ft_ftoa(float n);
int count_dots(char *str);

t_bool valid_char(char *str, t_bool floating);
t_bool check_commas(char **tokens);
t_bool valid_args(int argc, char **argv);
t_bool invalid_rgb_range(t_rgb rgb);
t_bool parse_rgb(char **tokens, t_rgb *rgb);
t_bool parse_vec3(char **tokens, t_vec3 *vec);
t_bool parse_float(char **tokens, float *num);
t_bool retrieve_camera(t_scene *scene, char *line);
t_bool parse_identifier(char **tokens, char *valid);
void clear_surfaces(t_surface *surfaces);

// raytracer:
void set_up_camera(t_scene *scene);
t_ray get_ray(t_scene *scene, unsigned int i, unsigned int j);
t_hit_record closest_hit(t_scene *scene, t_ray ray, float t0, float t1);
t_rgb shade(t_scene *scene, t_hit_record *hrec, t_ray ray);
t_hit_record construct_hit_rec(t_hit_record *hrec, float dist, t_vec3 normal, t_surface *surf);
t_hit_record ray_cylinder_intersect(t_ray ray, t_surface *cyl, float t0, float t1);
t_hit_record ray_plane_intersect(t_ray ray, t_surface *plane, float t0, float t1);
t_hit_record ray_sphere_intersect(t_ray ray, t_surface *sphere, float t0, float t1);
t_vec3 evaluate_ray(t_ray *ray, float t);
t_ray get_ray(t_scene *scene, unsigned int i, unsigned int j);
// mlx:
void my_mlx_pixel_put(t_image *data, int x, int y, int color);
int key_hook(int keycode, t_scene *scene);
int mouse_hook(int keycode, int x, int y, t_scene *scene);
int close_program(t_scene *scene);

#endif