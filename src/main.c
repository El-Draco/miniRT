/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:46:47 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 14:23:08 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	split_count(char **tokens)
{
	int	i;

	if (!tokens)
		return (0);
	i = 0;
	while (tokens[i])
		i++;
	return (i);
}

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
	t_hit_record	hrec;
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
			hrec = closest_hit(scene, ray, 1, INFINITY);
			if (hrec.distance >= 0 && hrec.distance != INFINITY)
			{
				color = shade(scene, &hrec, ray);
				my_mlx_pixel_put(&scene->image, i, j,
					get_color(rgb_to_color(color)));
			}
		}
	}
	mlx_put_image_to_window(scene->mlx, scene->window, scene->image.img, 0, 0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (!parse_sucesfull(&scene, argc, argv))
	{
		printf("Parse error\n");
		return (EXIT_FAILURE);
	}
	initialize_mlx(&scene);
	render_scene(&scene);
	mlx_key_hook(scene.window, &key_hook, &scene);
	mlx_hook(scene.window, 17, 0, &close_program, &scene);
	mlx_loop(scene.mlx);
	return (EXIT_SUCCESS);
}
