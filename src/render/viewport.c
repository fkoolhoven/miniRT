/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:28 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 17:52:09 by fkoolhov         ###   ########.fr       */
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

static bool	camera_aligned_with_y(t_camera *camera)
{
	return (camera->orientation.x == 0 && (camera->orientation.y == 1 || \
		camera->orientation.y == -1) && camera->orientation.z == 0);
}

static void	set_vertical_and_horizontal(t_viewport *view, t_camera *camera)
{
	t_vector	y_axis;

	y_axis = get_point(0, 1, 0);
	if (camera_aligned_with_y(camera))
	{
		view->horizontal = get_point(-1, 0, 0);
		view->vertical = get_point(0, 0, -1);
	}
	else
	{
		view->horizontal = cross(&y_axis, &camera->inverse_orientation);
		view->horizontal = normalize(&view->horizontal);
		view->vertical = cross(&camera->inverse_orientation, &view->horizontal);
	}
}

t_viewport	set_up_viewport(t_data *data)
{
	t_viewport	view;
	double		vertical_radians;
	double		aspect_ratio;
	t_camera	*camera;

	camera = &data->camera;
	camera->inverse_orientation = multiply(&camera->orientation, -1.0);
	aspect_ratio = (double)data->window_width / (double)data->window_height;
	vertical_radians = camera->horizontal_fov / aspect_ratio;
	vertical_radians = vertical_radians * M_PI / 180.0;
	view.half_height = tan(vertical_radians / 2.0);
	view.half_width = aspect_ratio * view.half_height;
	set_vertical_and_horizontal(&view, camera);
	view.horizontal_offset = multiply(&view.horizontal, 2.0 * view.half_width);
	view.vertical_offset = multiply(&view.vertical, -2.0 * view.half_height);
	view.upper_left_corner = get_upper_left_corner(camera, &view);
	return (view);
}
