/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/06/25 19:56:38 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

static void	initialize_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	scene->window = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "MiniRT");
	scene->image.img = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->image.addr = mlx_get_data_addr(scene->image.img,
										 &scene->image.bits_per_pixel, &scene->image.line_length,
										 &scene->image.endian);
}

void	render_scene(t_scene *scene)
{
	int				i;
	int				j;
	t_ray			ray;
	t_hit_record	*rec;
	t_rgb			color;

	i = -1;
	j = -1;
	set_up_camera(scene);
	while (++j < HEIGHT)
	{
		i = -1;
		while (++i < WIDTH)
		{
			ray = get_ray(scene, i, j);
			rec = closest_hit(scene, ray, 1, INFINITY);
			if (i == 518 && j == 522)
				printf("sup");
			if (rec && rec->distance >= 0 && rec->distance != INFINITY)
			{
				color = shade(scene, rec, ray);
				my_mlx_pixel_put(&scene->image, i, j, get_color(rgb_to_color(color)));
			}
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (parser(&scene, argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	initialize_mlx(&scene);
	render_scene(&scene);
	mlx_key_hook(scene.window, &key_hook, &scene);
	mlx_mouse_hook(scene.window, &mouse_hook, &scene);
	mlx_hook(scene.window, 17, 0, &close_program, &scene);
	mlx_loop(scene.mlx);
	return (EXIT_SUCCESS);
}