/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:47:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/04 18:58:36 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

// Function to calculate the angle between two points
float calculate_angle(float x1, float y1, float x2, float y2)
{
	// Calculate the angle between the two points using trigonometry
	float angle = atan2(y2 - y1, x2 - x1);
	return angle;
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == 53)
	{
		mlx_destroy_window(scene->mlx, scene->window);
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
	mlx_destroy_window(scene->mlx, scene->window);
	exit(0);
}
