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

int	main(void)
{
	t_scene	scene;

	scene.mlx = mlx_init();
	scene.window = mlx_new_window(scene.mlx, 1920, 1080, "MiniRT");
	scene.image.img = mlx_new_image(scene.mlx, 1920, 1080);
	scene.image.addr = mlx_get_data_addr(scene.image.img,
			&scene.image.bits_per_pixel, &scene.image.line_length,
			&scene.image.endian);
	my_mlx_pixel_put(scene.image.img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(scene.mlx, scene.window, scene.image.img, 0, 0);
	mlx_key_hook(scene.window, &key_hook, &scene);
	mlx_mouse_hook(scene.window, &mouse_hook, &scene);
	mlx_hook(scene.window, 17, 0, &close_program, &scene);
	mlx_loop(scene.mlx);
	return (0);
}
