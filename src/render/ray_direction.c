/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_direction.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:36:46 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/15 16:54:02 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_total_offset(t_viewport *viewport, t_data *data)
{
	double		x_scaled;
	double		y_scaled;
	t_vector	x_offset_vector;
	t_vector	y_offset_vector;
	t_vector	total_offset;

	x_scaled = 1.0 * viewport->pixel_x / data->window_width;
	y_scaled = 1.0 * viewport->pixel_y / data->window_height;
	x_offset_vector = multiply(&viewport->horizontal_offset, x_scaled);
	y_offset_vector = multiply(&viewport->vertical_offset, y_scaled);
	total_offset = add_vectors(&x_offset_vector, &y_offset_vector);
	return (total_offset);
}

void	set_ray_direction(t_viewport *viewport, t_ray *ray, t_data *data)
{
	t_vector	total_offset;

	total_offset = get_total_offset(viewport, data);
	ray->direction = add_vectors(&viewport->upper_left_corner, &total_offset);
	ray->direction = subtract_vectors(&ray->direction, &ray->origin);
	ray->direction = normalize(&ray->direction);
}
