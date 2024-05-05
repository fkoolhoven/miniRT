/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_transformation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:22:40 by felicia           #+#    #+#             */
/*   Updated: 2024/05/05 20:06:14 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// FIX NORMINETTE IN THIS FILE
static double get_angle(t_vector *cylinder_axis, t_vector *y_axis)
{
	return (acos(dot(cylinder_axis, y_axis) / (length(cylinder_axis) * length(y_axis))));
}

static t_matrix *set_rotation_matrix(double c, double s, double t, t_vector rotation_axis) 
{
    t_matrix *rotation_matrix;

    rotation_matrix = malloc(sizeof(t_matrix));
	if (!rotation_matrix)
		exit(1); // handle error
    
    rotation_matrix->m[0][0] = t * rotation_axis.x * rotation_axis.x + c;
    rotation_matrix->m[0][1] = t * rotation_axis.x * rotation_axis.y - s * rotation_axis.z;
    rotation_matrix->m[0][2] = t * rotation_axis.x * rotation_axis.z + s * rotation_axis.y;
    rotation_matrix->m[1][0] = t * rotation_axis.x * rotation_axis.y + s * rotation_axis.z;
    rotation_matrix->m[1][1] = t * rotation_axis.y * rotation_axis.y + c;
    rotation_matrix->m[1][2] = t * rotation_axis.y * rotation_axis.z - s * rotation_axis.x;
    rotation_matrix->m[2][0] = t * rotation_axis.x * rotation_axis.z - s * rotation_axis.y;
    rotation_matrix->m[2][1] = t * rotation_axis.y * rotation_axis.z + s * rotation_axis.x;
    rotation_matrix->m[2][2] = t * rotation_axis.z * rotation_axis.z + c;
    return (rotation_matrix);
}

t_matrix *calculate_rotation_matrix(t_vector cylinder_axis) 
{
    t_matrix *rotation_matrix;
    t_vector y_axis;
	t_vector rotation_axis;
    double angle;
    double cosine_angle;
    double sine_angle;
    double one_minus_cosine;
	
	y_axis = get_point(0, 1, 0);
    rotation_axis = cross_vectors(&cylinder_axis, &y_axis);
    normalize(&rotation_axis);
	angle = get_angle(&cylinder_axis, &y_axis);
    cosine_angle = cos(angle);
    sine_angle = sin(angle);
    one_minus_cosine = 1.0 - cosine_angle;
    rotation_matrix = set_rotation_matrix(cosine_angle, sine_angle, one_minus_cosine, rotation_axis);
    return (rotation_matrix);
}

t_vector apply_rotation_matrix(t_vector *v, t_matrix *m) 
{
    t_vector result;
	t_vector matrix_row;

	matrix_row = get_point(m->m[0][0], m->m[0][1], m->m[0][2]);
	result.x = dot(&matrix_row, v);
	matrix_row = get_point(m->m[1][0], m->m[1][1], m->m[1][2]);
	result.y = dot(&matrix_row, v);
	matrix_row = get_point(m->m[2][0], m->m[2][1], m->m[2][2]);
	result.z = dot(&matrix_row, v);
    return (result);
}

t_matrix *transpose_matrix(t_matrix *matrix) 
{
    t_matrix *result;

    result = malloc(sizeof(t_matrix));
	if (!result)
		exit(1); // handle error
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++) 
            result->m[i][j] = matrix->m[j][i];
    }
    return (result);
}