//
// Created by Zunon on 30/05/2023.
//

#include "../inc/minirt.h"

t_vec3    *evaluate_ray(t_ray *ray, float t)
{
    t_vec3	*result;

    result = malloc(sizeof(t_vec3));
    *result = add_vec3(ray->origin, scale_vec3(ray->direction, t));
    return (result);
}