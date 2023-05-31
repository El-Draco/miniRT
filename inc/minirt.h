/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:53:19 by rriyas            #+#    #+#             */
/*   Updated: 2023/05/31 19:50:40 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/minilibx_opengl_20191021/mlx.h"
# include "../lib/libmath/libmath.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>

# define HEIGHT 1920
# define WIDTH 1080

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

// t_material_phong {TBD}

typedef struct s_ambi_light
{
	float	intensity;
	t_rgb	color;
}			t_ambi_light;

typedef struct s_basis
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
}			t_basis;

typedef struct s_camera
{
	t_vec3			origin;
	t_vec3			orientation;
	unsigned char	field_of_view;
	t_basis			basis;
}					t_camera;

typedef struct s_point_light
{
	t_vec3	origin;
	float	intensity;
	t_rgb	color;
}	t_point_light;

typedef enum e_shape {SPHERE, PLANE, CYLINDER}	t_shape;

typedef struct s_surface
{
	t_vec3		origin;
	t_rgb		color;
	void		*attributes;
	t_shape		type;
}	t_surface;

// NOTE: attributes will point to a float (diameter) if sphere
// t_vec3 (orientation) if plane,
// t_cylinder if cylinder
typedef struct s_cylinder
{
	t_vec3	orientation;
	float	diameter;
	float	height;
}			t_cylinder;

typedef struct s_scene
{
	void			*mlx;
	void			*window;
	t_image			image;
	t_ambi_light	ambient;
	t_camera		camera;
	t_point_light	light;
	t_surface		*surfaces;
	size_t			num_surfaces;
}					t_scene;

typedef struct s_ray
{
    t_vec3	origin;
    t_vec3	direction;
}	t_ray;
// t_ray[0] = origin & t_ray[1] = direction

typedef struct s_hit_record
{
	t_surface	*surface;
	float		distance;
	t_vec3		normal;
}				t_hit_record;



int		key_hook(int keycode, t_scene *scene);
int		mouse_hook(int keycode, int x, int y, t_scene *scene);
int		close_program(t_scene *scene);
void	my_mlx_pixel_put(t_image *data, int x, int y, int color);
t_vec3 construct_basis();
t_vec3 evaluate_ray(t_ray *ray, float t);
t_vec3 non_collinear_vec(t_vec3 vector);
t_vec3 construct_basis();
float get_focal_distance();
t_ray get_ray(unsigned int i, unsigned int j);
extern t_scene g_scene;

#endif