/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_rotate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:11:40 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 15:12:36 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	rotate_ray(t_ray *ray, t_point cylinder_center, t_matrix *rotation)
{
	t_ray	rotated_ray;

	rotated_ray.origin = subtract_vectors(&ray->origin, &cylinder_center);
	rotated_ray.origin = rotate(&rotated_ray.origin, rotation);
	rotated_ray.direction = rotate(&ray->direction, rotation);
	return (rotated_ray);
}

t_cylinder	rotate_cylinder(t_cylinder *cylinder)
{
	t_cylinder	rotated_cylinder;

	rotated_cylinder.center = get_point(0, 0, 0);
	rotated_cylinder.axis = get_point(0, 1, 0);
	rotated_cylinder.radius = cylinder->radius;
	rotated_cylinder.height = cylinder->height;
	rotated_cylinder.color = cylinder->color;
	rotated_cylinder.rotation = cylinder->rotation;
	rotated_cylinder.inverse_rotation = cylinder->inverse_rotation;
	return (rotated_cylinder);
}

t_vector	rotate(t_vector *vector, t_matrix *m)
{
	t_vector	result;
	t_vector	matrix_row;

	matrix_row = get_point(m->m[0][0], m->m[0][1], m->m[0][2]);
	result.x = dot(&matrix_row, vector);
	matrix_row = get_point(m->m[1][0], m->m[1][1], m->m[1][2]);
	result.y = dot(&matrix_row, vector);
	matrix_row = get_point(m->m[2][0], m->m[2][1], m->m[2][2]);
	result.z = dot(&matrix_row, vector);
	return (result);
}
