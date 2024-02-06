#include "minirt.h"

// This function tries to hit all objects in the scene with the ray and updates
// the hit record with the closest hit (if any). It does this by looping through
// all objects in the scene and calling the appropriate find_closer_[object]_hit function.
bool try_to_hit_objects(t_data *data, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec)
{
	t_hit_record *temp_rec = get_hit_record();
	bool hit_anything = false;
	double closest_so_far = ray_tmax;

	t_sphere *current_sphere = data->sphere;
	while (current_sphere != NULL) // gonna find the closest sphere hit
	{
		if (find_closer_sphere_hit(current_sphere, ray, ray_tmin, closest_so_far, temp_rec)) 
		{
			hit_anything = true;
			closest_so_far = temp_rec->t;
			*rec = *temp_rec;
		}
		current_sphere = current_sphere->next;
	}

	t_plane *current_plane = data->plane;
	while (current_plane != NULL) // the same thing but for planes
	{
		if (find_closer_plane_hit(current_plane, ray, ray_tmin, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec->t;
			*rec = *temp_rec;
		}
		current_plane = current_plane->next;
	}

	t_cylinder *current_cylinder = data->cylinder;
	while (current_cylinder != NULL) // the same thing but for cylinders
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, ray_tmin, closest_so_far, temp_rec))
		{
			hit_anything = true;
			closest_so_far = temp_rec->t;
			*rec = *temp_rec;
		}
		current_cylinder = current_cylinder->next;
	}
	free(temp_rec);
	return (hit_anything);
}

// Gets the color of either the background or the object that was hit.
t_color get_ray_color(t_data *data, t_ray ray, t_hit_record *rec) 
{
	t_color		 color;

	if (try_to_hit_objects(data, &ray, 0.0, DBL_MAX, rec)) // an object was hit, color it
	{
		// t_vector temp = get_point(rec->normal.x + 1, rec->normal.y + 1, rec->normal.z + 1);
		// free(rec);
		// color = multiply(&temp, 0.5);
		// printf("color: %f %f %f\n", color.x, color.y, color.z);
		// return (color);
		color = apply_shading(data, rec);
		return (color);
	}
	else // no object was hit, color background with some gradient
	{
		color = get_point(0.0, 0.0, 0.0);
		return (color);
	}
}

// Gets the offset needed to convert pixel coordinates to viewport coordinates.
t_vector	get_total_offset(int x, int y, t_vector *horizontal_offset, t_vector *vertical_offset)
{
	double		x_scaled;
	double		y_scaled;
	t_vector	x_offset_vector;
	t_vector	y_offset_vector;
	t_vector	total_offset;

	x_scaled = 1.0 * x / IMAGE_WIDTH;
	y_scaled = 1.0 * y / IMAGE_HEIGHT;
	x_offset_vector = multiply(horizontal_offset, x_scaled);
	y_offset_vector = multiply(vertical_offset, y_scaled);
	total_offset = add_vectors(&x_offset_vector, &y_offset_vector);
	return (total_offset);
}

t_viewport set_up_viewport(t_camera *camera)
{
	t_vector	upper_left_corner;
	t_vector	horizontal_offset;
	t_vector	vertical_offset;
	double	aspect_ratio;
	double	vertical_fov;
	double	theta;
	double	half_height;
	double	half_width;

	aspect_ratio = (double)IMAGE_WIDTH / (double)IMAGE_HEIGHT;
	vertical_fov = camera->horizontal_field_of_view / aspect_ratio;
	theta = vertical_fov * M_PI / 180.0;
	half_height	= tan(theta / 2.0);
	half_width = aspect_ratio * half_height;

	t_vector negative_orientation = multiply(&camera->orientation, -1.0);
	t_vector vup = get_point(0, 1.0, 0);
	t_vector temp = cross_vectors(&vup, &negative_orientation);
	t_vector horizontal = normalize(&temp);
	t_vector vertical = cross_vectors(&negative_orientation, &horizontal);

	double height_orientation = 2.0 * half_width;
	double vertical_orientation = -2.0 * half_height;
	horizontal_offset = multiply(&horizontal, height_orientation);
	vertical_offset = multiply(&vertical, vertical_orientation);
	
	// *upper_left_corner = get_point(-half_width, half_height, -1.0);
	
	t_vector temp1 = multiply(&horizontal, half_width);
	t_vector temp2 = multiply(&vertical, half_height);
	t_vector temp3 = subtract_vectors(&temp1, &temp2);
	t_vector temp4 = subtract_vectors(&camera->view_point, &temp3);
	t_vector temp5 = subtract_vectors(&temp4, &negative_orientation);
	upper_left_corner = temp5;
	t_viewport viewport = {upper_left_corner, horizontal_offset, vertical_offset};
	return (viewport);
}

t_vector	get_ray_direction(int x, int y, t_viewport *viewport, t_ray *ray)
{
	t_vector	ray_direction;
	t_vector	total_offset;
	
	total_offset = get_total_offset(x, y, &viewport->horizontal_offset, &viewport->vertical_offset);
	ray_direction = add_vectors(&viewport->upper_left_corner, &total_offset);
	ray_direction = subtract_vectors(&ray_direction, &ray->origin);                   
	ray_direction = normalize(&ray_direction);
	return (ray_direction);
}

// Loops through all pixels in the image and renders them.
void	render_image(t_data *data)
{
	t_viewport		viewport;
	t_hit_record	*rec;
	t_ray			ray;
	int				y;
	int				x;

	viewport = set_up_viewport(&data->camera);
	rec = get_hit_record();
	ray.origin = data->camera.view_point;
	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		x = 0;
		while (x < IMAGE_WIDTH)
		{
			ray.direction = get_ray_direction(x, y, &viewport, &ray);
			t_color pixel_color = get_ray_color(data, ray, rec);       
			unsigned int rgba = get_rgba((int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z), 255);
			mlx_put_pixel(data->mlx_info->img_ptr, x, y, rgba);
			x++;
		}
		y++;
	}
	free(rec);
}
