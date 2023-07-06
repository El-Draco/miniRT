/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:47:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 14:53:52 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == 53)
	{
		clear_surfaces(scene->surfaces);
		mlx_destroy_window(scene->mlx, scene->window);
		mlx_destroy_image(scene->mlx, scene->image.img);
		exit(0);
	}
	if (keycode == 13)
		scene->camera.origin.z += 1;
	if (keycode == 0)
		scene->camera.origin.x -= 1;
	if (keycode == 2)
		scene->camera.origin.x += 1;
	if (keycode == 1)
		scene->camera.origin.z -= 1;
	if (keycode == 126)
		scene->camera.origin.y += 1;
	if (keycode == 125)
		scene->camera.origin.y -= 1;
	mlx_destroy_image(scene->mlx, scene->image.img);
	scene->image.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->image.addr = mlx_get_data_addr(scene->image.img,
			&scene->image.bits_per_pixel, &scene->image.line_length,
			&scene->image.endian);
	render_scene(scene);
	return (0);
}

int	close_program(t_scene *scene)
{
	clear_surfaces(scene->surfaces);
	mlx_destroy_image(scene->mlx, scene->image.img);
	exit(0);
}
