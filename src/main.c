/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/04 15:44:12 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static t_scene g_scene;

int	main()
{
	parser("radi.rt");
	int i = -1, j = -1;
	// Initialize:
	g_scene.mlx = mlx_init();
	g_scene.window = mlx_new_window(g_scene.mlx, 1920, 1080, "MiniRT");
	g_scene.image.img = mlx_new_image(g_scene.mlx, 1920, 1080);
	g_scene.image.addr = mlx_get_data_addr(g_scene.image.img,
			&g_scene.image.bits_per_pixel, &g_scene.image.line_length,
			&g_scene.image.endian);
	my_mlx_pixel_put(g_scene.image.img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(g_scene.mlx, g_scene.window, g_scene.image.img, 0, 0);
	mlx_key_hook(g_scene.window, &key_hook, &g_scene);
	mlx_mouse_hook(g_scene.window, &mouse_hook, &g_scene);
	mlx_hook(g_scene.window, 17, 0, &close_program, &g_scene);
	mlx_loop(g_scene.mlx);
	//
	// validate argc argv
	// Parse Scene
	// Render Scene (Ray Tracing)
	/*
	 *
	 * Set Basis Vector of Camera: */
	g_scene.camera.basis.w = scale_vec3(g_scene.camera.orientation, -1);
	g_scene.camera.basis.u = construct_basis();
	g_scene.camera.basis.v = cross_vec3(g_scene.camera.basis.w, g_scene.camera.basis.u);

	t_ray ray;
	// t_hit_record *rec;
	// t_color color;
	while (++i < WIDTH)
	{
		j = -1;
		while (++j < HEIGHT)
		{
			ray = get_ray(i, j);
			// rec = closest_hit(ray, 1, INFINITY);
			// if (rec == NULL)
			// 	handle_background();
			// color = shade(rec);
			// my_mlx_pixel_put(g_scene.image.img, i, j, color);
		}
	}
	// Push Image to Window
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