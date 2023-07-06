/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rriyas <rriyas@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 14:45:11 by rriyas            #+#    #+#             */
/*   Updated: 2023/07/06 15:17:09 by rriyas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
# define LIBMATH_H

# include "../minilibx_opengl_20191021/mlx.h"
# include "../libft/libft.h"

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_hvec
{
	float	x;
	float	y;
	float	z;
	float	h;
}	t_hvec;

typedef struct s_rgb
{
	float	red;
	float	green;
	float	blue;
}	t_rgb;

typedef struct s_matrix
{
	float	m[4][4];
}	t_matrix;

// t_vec3 - 3 dimensional vector (float[3])
t_vec3		add_vec3(t_vec3 v1, t_vec3 v2);
t_vec3		sub_vec3(t_vec3 v1, t_vec3 v2);
float		dot_vec3(t_vec3 v1, t_vec3 v2);
t_vec3		cross_vec3(t_vec3 v1, t_vec3 v2);
t_vec3		scale_vec3(t_vec3 v, float scsale);
float		get_vec3_magnitude(t_vec3 vec);
t_vec3		normalize_vec3(t_vec3 v);

// t_rgb - color type {int red, int green, int blue}
t_rgb		add_rgb(t_rgb r1, t_rgb r2);
t_rgb		sub_rgb(t_rgb r1, t_rgb r2);
t_rgb		mult_rgb(t_rgb r1, t_rgb r2); //- Multiply rgb values
t_rgb		scale_rgb(t_rgb r, float scale);
t_rgb		interpolate(t_rgb r1, t_rgb r2, float scale);
t_color		rgb_to_color(t_rgb rgb);
t_rgb		normalize_rgb(t_rgb rgb);
void		print_vec3(t_vec3 v);
void		print_rgb(t_rgb rgb);

#endif