/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 16:06:40 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_upper_left_corner(t_camera *camera, t_viewport *view)
{
	t_vector	upper_left;
	t_vector	half_width_horizontal;
	t_vector	half_height_vertical;
	t_vector	offset;
	t_vector	view_origin;

	half_width_horizontal = multiply(&view->horizontal, view->half_width);
	half_height_vertical = multiply(&view->vertical, view->half_height);
	offset = subtract_vectors(&half_width_horizontal, &half_height_vertical);
	view_origin = subtract_vectors(&camera->view_point, &offset);
	upper_left = subtract_vectors(&view_origin, &camera->inverse_orientation);
	return (upper_left);
}

t_viewport	set_up_viewport(t_data *data)
{
	t_viewport	view;
	double		vertical_radians;
	double		aspect_ratio;
	t_vector	true_up;
	t_camera	*camera;

	camera = &data->camera;
	aspect_ratio = (double)data->window_width / (double)data->window_height;
	camera->inverse_orientation = multiply(&camera->orientation, -1.0);
	vertical_radians = camera->horizontal_fov / aspect_ratio;
	vertical_radians = vertical_radians * M_PI / 180.0;
	view.half_height = tan(vertical_radians / 2.0);
	view.half_width = aspect_ratio * view.half_height;
	true_up = get_point(0, 1, 0);
	view.horizontal = cross(&true_up, &camera->inverse_orientation);
	view.horizontal = normalize(&view.horizontal);
	view.vertical = cross(&camera->inverse_orientation, &view.horizontal);
	view.horizontal_offset = multiply(&view.horizontal, 2.0 * view.half_width);
	view.vertical_offset = multiply(&view.vertical, -2.0 * view.half_height);
	view.upper_left_corner = get_upper_left_corner(camera, &view);
	return (view);
}
