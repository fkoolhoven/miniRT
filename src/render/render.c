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
t_color get_ray_color(t_data *data, t_ray ray) 
{
	t_hit_record *rec = get_hit_record();

	if (try_to_hit_objects(data, &ray, 0.0, DBL_MAX, rec)) // an object was hit, color it
	{
		t_vector temp = get_point(rec->normal.x + 1, rec->normal.y + 1, rec->normal.z + 1);
		free(rec);
		return (multiply(&temp, 0.5));
		// t_color color = rec->color;
		// free(rec);
		// return (color);
	}
	else // no object was hit, color background with some gradient
	{
		free(rec);
		t_vector unit_direction = normalize(&ray.direction);
		double a = 0.5 * (unit_direction.y + 1.0);
		t_color start_color = get_point(1.0, 1.0, 1.0);
		t_color end_color = get_point(0.5, 0.7, 1.0);
		start_color = multiply(&start_color, 1.0 - a);
		end_color = multiply(&end_color, a);
		return (vector_add(&start_color, &end_color));
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
	total_offset = vector_add(&x_offset_vector, &y_offset_vector);
	return (total_offset);
}

// Loops through all pixels in the image and renders them.
void	render_image(t_data *data, mlx_image_t *img_ptr)
{
	t_vector	upper_left_corner = get_point(-2.0, 1.0, -1.0);
	t_vector	horizontal_offset = get_point(4.0, 0.0, 0.0);
	t_vector	vertical_offset = get_point(0.0, -2.0, 0.0);
	int			y;
	int			x;
	t_ray 		ray;

	ray.origin = data->camera.view_point;
	y = 0;
	while (y < IMAGE_HEIGHT)
	{
		x = 0;
		while (x < IMAGE_WIDTH)
		{
			t_vector total_offset = get_total_offset(x, y, &horizontal_offset, &vertical_offset);
			ray.direction = vector_add(&upper_left_corner, &total_offset);
			ray.direction = normalize(&ray.direction);
			t_color pixel_color = get_ray_color(data, ray);
			unsigned int rgba = get_rgba((int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z), 255);
			mlx_put_pixel(img_ptr, x, y, rgba);
			x++;
		}
		y++;
	}
}
