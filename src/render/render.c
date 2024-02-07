#include "minirt.h"

// Returns the color of the pixel as an unsigned int.
unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

// Gets the color of either the background or the object that was hit.
t_color get_ray_color(t_data *data, t_ray ray, t_hit_record *rec) 
{
	t_hit_params	*params;
	t_color			color;

	params = get_hit_params();
	if (hit_objects(data, &ray, params, rec)) // an object was hit, color it
	{
		color = apply_shading(data, rec);
		return (color);
	}
	else // no object was hit, color the background
	{
		color = get_point(0.0, 0.0, 0.0);
		return (color);
	}
}

// Gets the offset needed to convert pixel coordinates to viewport coordinates.
t_vector	get_total_offset(int x, int y, t_viewport *viewport)
{
	double		x_scaled;
	double		y_scaled;
	t_vector	x_offset_vector;
	t_vector	y_offset_vector;
	t_vector	total_offset;

	x_scaled = 1.0 * x / IMAGE_WIDTH;
	y_scaled = 1.0 * y / IMAGE_HEIGHT;
	x_offset_vector = multiply(&viewport->horizontal_offset, x_scaled);
	y_offset_vector = multiply(&viewport->vertical_offset, y_scaled);
	total_offset = add_vectors(&x_offset_vector, &y_offset_vector);
	return (total_offset);
}

// Gets the direction of the ray for a given pixel.
t_vector	get_ray_direction(int x, int y, t_viewport *viewport, t_ray *ray)
{
	t_vector	ray_direction;
	t_vector	total_offset;
	
	total_offset = get_total_offset(x, y, viewport);
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
	unsigned int	rgba;
	t_color			pixel_color;

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
			pixel_color = get_ray_color(data, ray, rec);       
			rgba = get_rgba((int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z), 255);
			mlx_put_pixel(data->mlx_info->img_ptr, x, y, rgba);
			x++;
		}
		y++;
	}
	free(rec);
}
