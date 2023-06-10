/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/10 22:48:29 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

void initialize_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	scene->image.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->image.addr = mlx_get_data_addr(scene->image.img,
										 &scene->image.bits_per_pixel, &scene->image.line_length,
										 &scene->image.endian);
}

float ft_max(float x, float y)
{
	if (x < y)
		return (y);
	return (x);
}

t_color illuminate(t_scene *scene, t_ray ray, t_hit_record *hrec)
{
	t_vec3 x;
	t_vec3 l;
	t_vec3 n;
	t_color E;
	float r;
	float max;
	float dot;
	t_rgb diffuse;
	t_rgb amb;
	float dummy;

	x = add_vec3(scale_vec3(ray.direction, hrec->distance), ray.origin);
	r = get_vec3_magnitude(add_vec3(scene->light.origin, scale_vec3(x, -1)));
	l = scale_vec3(add_vec3(scene->light.origin, scale_vec3(x, -1)), 1/r);
	n = hrec->normal;
	dot = (dot_vec3(n, l));
	max = ft_max(0, dot_vec3(n, l));
	if (max != 0)
		printf("oops");
	diffuse = scale_rgb(scene->light.color, scene->light.intensity * (max * 1.0 / (r * r)));
	diffuse = scale_rgb(diffuse, 1.0/255.0);
	diffuse = mult_rgb(diffuse, scale_rgb(hrec->surface->color, 1.0));
	amb = (t_rgb) {scene->ambient.color.red, scene->ambient.color.green, scene->ambient.color.blue};
	dummy = amb.red + amb.blue + amb.green ;
	amb = scale_rgb(amb, scene->ambient.intensity * 1.0 / 255);
	amb.red = amb.red / dummy;
	amb.green = amb.green / dummy;
	amb.blue = amb.blue / dummy;
	amb = mult_rgb(amb, scale_rgb(hrec->surface->color, 0.1));
	diffuse = add_rgb(diffuse, amb);
	E = rgb_to_color(diffuse);
	if (E.blue > 255 || E.green > 255 || E.red > 255)
		printf("oops");
	return (E);
}


t_color shade(t_scene *scene, t_hit_record* hrec, t_ray ray)
{
	t_color col;

	if (hrec && hrec->distance < INFINITY)
	{
		col = illuminate(scene, ray, hrec);
		if (col.blue > 0 || col.green > 0 || col.red > 0)
			printf("oops");
		return (col);
	}
	return ((t_color){0,0,0,0});
}

int	main()
{
	t_scene scene;
	int i = -1;
	int j = -1;
	initialize_mlx(&scene);
	parser(&scene, "radi.rt");

	/*Set Basis Vector of Camera: */
	scene.camera.basis.w = scale_vec3(scene.camera.orientation, -1);
	scene.camera.basis.u = construct_basis(&scene);
	scene.camera.basis.v = cross_vec3(scene.camera.basis.w, scene.camera.basis.u);

	t_ray ray;
	t_hit_record *rec;
	t_color color;
	while (++i < HEIGHT)
	{
		j = -1;
		while (++j < WIDTH)
		{
			ray = get_ray(&scene, i, j);
			rec = closest_hit(&scene, ray, 1, INFINITY);
			// if (rec && rec->distance != INFINITY)
			// {
			// 		color = (t_color){0, 14, 56, 92};
			// 		my_mlx_pixel_put(&scene.image, i, j, rec->surface->color.red | rec->surface->color.green << 8 | rec->surface->color.blue << 16);
			// }
			if (rec && rec->distance != INFINITY)
			{
				color = shade(&scene, rec, ray);
				if (color.blue > 0 || color.green > 0 || color.red > 0)
					printf("oops");
				my_mlx_pixel_put(&scene.image, i, j, color.red | color.green << 8 | color.blue << 16);
			}
		}
	}
	mlx_put_image_to_window(scene.mlx, scene.window, scene.image.img, 0, 0);
	mlx_key_hook(scene.window, &key_hook, &scene);
	mlx_mouse_hook(scene.window, &mouse_hook, &scene);
	mlx_hook(scene.window, 17, 0, &close_program, &scene);
	mlx_loop(scene.mlx);
	return (0);
}