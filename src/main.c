/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/03/18 11:56:21 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

t_scene g_scene;

int	main(void)
{
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
	// Parse Scene
	// Render Scene (Ray Tracing)
	/*
	 * For each pixel:
	 * 	t_vec3 ray = get_ray();
	 * 	t_hit_record *rec = closest_hit(ray, 0, INFINITY);
	 * 	if (rec == NULL) handle_background();
	 * 	t_rgb color = shade(rec);
	 * 	image.set_pixel(x, y, color);
	 */
	// Push Image to Window
	return (0);
}
