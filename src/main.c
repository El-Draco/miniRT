/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/08 21:23:14 by rriyas           ###   ########.fr       */
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

double ft_max(float x, float y)
{
	if (x < y)
		return (y);
	return (x);
}

t_color illuminate_point_light(t_scene *scene, t_ray ray, t_hit_record *hrec)
{
	t_vec3 x;
	t_vec3 l;
	t_vec3 n;
	t_color E;
	float r;

	x = scale_vec3(ray.direction, hrec->distance);
	r = get_vec3_magnitude(add_vec3(scene->light.origin, scale_vec3(x, -1)));
	l = scale_vec3(add_vec3(scene->light.origin, scale_vec3(x, -1)), 1/r);
	n = hrec->normal;
	E = rgb_to_color(scale_rgb(scale_rgb(scene->light.color, ft_max(0, dot_vec3(n, l)) * scene->light.intensity), 1 / (r * r)));

	return (E);
}


t_color shade(t_scene *scene, t_ray ray, float t0, float t1)
{
	t_hit_record *hrec;
	t_color col;

	hrec = closest_hit(scene, ray, t0, t1);
	if (hrec && hrec->distance < INFINITY)
	{
		// col = (t_color) {0,0,0,0};
		col = illuminate_point_light(scene, ray, hrec);
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

	// printf("Camera Basis: ");
	// printf("\t u: ");
	// print_vec3(scene.camera.basis.u);
	// printf("\t v: ");
	// print_vec3(scene.camera.basis.v);
	// printf("\t w: ");
	// print_vec3(scene.camera.basis.w);


	// my_mlx_pixel_put(scene.image.img, 500, 500, 0x00FF0000);
	// mlx_put_image_to_window(scene.mlx, scene.window, scene.image.img, 0, 0);
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
			if (rec && rec->distance != INFINITY)
			{
					color = (t_color){0, 14, 56, 92};
				my_mlx_pixel_put(&scene.image, i, j, rec->surface->color.red | rec->surface->color.green << 8 | rec->surface->color.blue << 16);
			}
			// if (rec && rec->distance != INFINITY)
			// 	color = shade(&scene, ray, 1, INFINITY);
			// my_mlx_pixel_put(&scene.image, i, j, color.red | color.green << 8 | color.blue << 16);
		}
	}
	my_mlx_pixel_put(&scene.image, WIDTH / 2, HEIGHT/ 2, 0xFF0000);
	mlx_put_image_to_window(scene.mlx, scene.window, scene.image.img, 0, 0);
	mlx_key_hook(scene.window, &key_hook, &scene);
	mlx_mouse_hook(scene.window, &mouse_hook, &scene);
	mlx_hook(scene.window, 17, 0, &close_program, &scene);
	mlx_loop(scene.mlx);
	return (0);
}

/*
 * For each pixel:
 * 	t_vec3 ray = get_ray();
 * 	t_hit_record *rec = closest_hit(ray, 1, INFINITY);
 * 	if (rec == NULL) handle_background();
 * 	t_rgb color = shade(rec);
 * 	image.set_pixel(x, y, color);
 */