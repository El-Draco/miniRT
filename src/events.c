/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:47:06 by rriyas            #+#    #+#             */
/*   Updated: 2023/03/17 18:08:44 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minirt.h"

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == 53)
	{
		mlx_destroy_window(scene->mlx, scene->window);
		exit(0);
	}
	return (0);
}

int	mouse_hook(int keycode, int x, int y, t_scene *scene)
{
	(void)keycode;
	(void)scene;
	(void)x;
	(void)y;
	return (0);
}

int	close_program(t_scene *scene)
{
	mlx_destroy_window(scene->mlx, scene->window);
	exit(0);
	return (0);
}
