/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/23 20:13:28 by rriyas           ###   ########.fr       */
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

t_rgb illuminate(t_scene *scene, t_ray ray, t_hit_record *hrec)
{
	t_rgb diffuse;
	t_rgb surf_col;
	t_rgb amb;
	t_vec3 point_on_surf = evaluate_ray(&ray, hrec->distance);
	t_vec3 light_ray = sub_vec3(scene->light.origin, point_on_surf);
	t_vec3 light_normal = normalize_vec3(light_ray);
	t_vec3 hit_normal = hrec->normal;
	surf_col = hrec->surface->color;

	amb = scene->ambient.color;
	amb = mult_rgb(amb, surf_col);
	amb = scale_rgb(amb, scene->ambient.intensity);

	diffuse = mult_rgb(scene->light.color, surf_col);
	float visibility = 1.0f;
	t_ray shadow_ray;
	shadow_ray.origin = point_on_surf;
	shadow_ray.direction = light_normal;
	t_hit_record *shadow_rec = closest_hit(scene, shadow_ray, 0.001, INFINITY);

	if (shadow_rec && shadow_rec->distance >= 0 && shadow_rec->distance != INFINITY)
	{
		// Point is in shadow, reduce visibility
		visibility = 0.0;
	}
	diffuse = scale_rgb(diffuse,visibility * scene->light.intensity * fmaxf(0.0, dot_vec3(hit_normal, light_normal)) * (1 / pow(get_vec3_magnitude(light_normal), 2)));
	diffuse = add_rgb(diffuse, amb);
	return (diffuse);
}


t_rgb shade(t_scene *scene, t_hit_record* hrec, t_ray ray)
{
	t_rgb col;

	if (hrec && hrec->distance < INFINITY)
	{
		col = illuminate(scene, ray, hrec);
		return (col);
	}
	return ((t_rgb){0,0,0});
}

int	main()
{
	t_scene scene;
	int i = -1;
	int j = -1;
	initialize_mlx(&scene);
	parser(&scene, "radi.rt");
	scene.light.color = normalize_rgb(scene.light.color);
	/*Set Basis Vector of Camera: */
	scene.camera.basis.w = normalize_vec3(scale_vec3(scene.camera.orientation, -1));
	scene.camera.basis.u = construct_basis(&scene);
	scene.camera.basis.v = normalize_vec3(cross_vec3(scene.camera.basis.w, scene.camera.basis.u));
	t_ray ray;
	t_hit_record *rec;
	t_rgb color;
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			ray = get_ray(&scene, i, j);
			rec = closest_hit(&scene, ray, 1, INFINITY);
			if (rec && rec->distance >= 0 && rec->distance != INFINITY)
			{
				color = shade(&scene, rec, ray);
				my_mlx_pixel_put(&scene.image, i, j, get_color(rgb_to_color(color)));
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