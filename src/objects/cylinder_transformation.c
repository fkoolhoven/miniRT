/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_transformation.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:22:40 by felicia           #+#    #+#             */
/*   Updated: 2024/05/28 18:16:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_angle(t_vector *cylinder_axis, t_vector *y_axis)
{
	double	numerator;
	double	denominator;

	numerator = dot(cylinder_axis, y_axis);
	denominator = length(cylinder_axis) * length(y_axis);
	return (acos(numerator / denominator));
}

static t_matrix	*set_rotation_matrix(double angle, t_vector axis)
{
	t_matrix	*rotation_matrix;
	double		cos_angle;
	double		sin_angle;
	double		t;

	rotation_matrix = malloc(sizeof(t_matrix));
	if (!rotation_matrix)
		error("malloc failure in set_rotation_matrix()", EXIT_FAILURE);
	cos_angle = cos(angle);
	sin_angle = sin(angle);
	t = 1.0 - cos_angle;
	rotation_matrix->m[0][0] = t * axis.x * axis.x + cos_angle;
	rotation_matrix->m[0][1] = t * axis.x * axis.y - sin_angle * axis.z;
	rotation_matrix->m[0][2] = t * axis.x * axis.z + sin_angle * axis.y;
	rotation_matrix->m[1][0] = t * axis.x * axis.y + sin_angle * axis.z;
	rotation_matrix->m[1][1] = t * axis.y * axis.y + cos_angle;
	rotation_matrix->m[1][2] = t * axis.y * axis.z - sin_angle * axis.x;
	rotation_matrix->m[2][0] = t * axis.x * axis.z - sin_angle * axis.y;
	rotation_matrix->m[2][1] = t * axis.y * axis.z + sin_angle * axis.x;
	rotation_matrix->m[2][2] = t * axis.z * axis.z + cos_angle;
	return (rotation_matrix);
}

t_matrix	*calculate_rotation_matrix(t_vector cylinder_axis)
{
	t_matrix	*rotation_matrix;
	t_vector	y_axis;
	t_vector	rotation_axis;
	double		angle;

	y_axis = get_point(0, 1, 0);
	rotation_axis = cross(&cylinder_axis, &y_axis);
	// if (rotation_axis.x == 0 && rotation_axis.y == 0 && rotation_axis.z == 0) 
	// {
	// 	printf("cylinder axis is parallel to y-axis\n");
    //     rotation_axis = get_point(1, 0, 0);  // or any other vector orthogonal to y-axis
    // } 
	// else 
	// {
        normalize(&rotation_axis);
    // }
	angle = get_angle(&cylinder_axis, &y_axis);
	rotation_matrix = set_rotation_matrix(angle, rotation_axis);
	return (rotation_matrix);
}

t_matrix	*transpose_matrix(t_matrix *matrix)
{
	t_matrix	*result;
	int			i;
	int			j;

	result = malloc(sizeof(t_matrix));
	if (!result)
		error("malloc failure in transpose_matrix()", EXIT_FAILURE);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			result->m[i][j] = matrix->m[j][i];
			j++;
		}
		i++;
	}
	return (result);
}
