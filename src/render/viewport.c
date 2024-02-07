#include "minirt.h"

t_vector	calculate_upper_left_corner(t_camera *camera, t_viewport *viewport, t_vector *inverse_orientation) // update
{
	t_vector	upper_left_corner;
	t_vector	half_width_horizontal;
	t_vector	half_height_vertical;
	t_vector	upper_left_corner_offset;
	t_vector	viewport_origin;

	half_width_horizontal = multiply(&viewport->horizontal_direction, viewport->half_width);
	half_height_vertical = multiply(&viewport->vertical_direction, viewport->half_height);
	upper_left_corner_offset = subtract_vectors(&half_width_horizontal, &half_height_vertical);
	viewport_origin = subtract_vectors(&camera->view_point, &upper_left_corner_offset);
	upper_left_corner = subtract_vectors(&viewport_origin, inverse_orientation);
	return (upper_left_corner);
}

// Sets up the viewport for the camera. 
t_viewport set_up_viewport(t_camera *camera)
{
	t_viewport	viewport;
	double		aspect_ratio;
	double		vertical_fov;
	double		vertical_radians;
	t_vector	inverse_orientation;
	t_vector	true_up;

	aspect_ratio = (double)IMAGE_WIDTH / (double)IMAGE_HEIGHT;
	inverse_orientation = multiply(&camera->orientation, -1.0);
	vertical_fov = camera->horizontal_fov / aspect_ratio;
	vertical_radians = vertical_fov * M_PI / 180.0;
	viewport.half_height = tan(vertical_radians / 2.0);
	viewport.half_width = aspect_ratio * viewport.half_height;
	true_up = get_point(0, 1.0, 0);
	viewport.horizontal_direction = cross_vectors(&true_up, &inverse_orientation);
	viewport.horizontal_direction = normalize(&viewport.horizontal_direction);
	viewport.vertical_direction = cross_vectors(&inverse_orientation, &viewport.horizontal_direction);
	viewport.horizontal_offset = multiply(&viewport.horizontal_direction, 2.0 * viewport.half_width);
	viewport.vertical_offset = multiply(&viewport.vertical_direction, -2.0 * viewport.half_height);
	viewport.upper_left_corner = calculate_upper_left_corner(camera, &viewport, &inverse_orientation);
	return (viewport);
}