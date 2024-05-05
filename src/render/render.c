#include "minirt.h"

static unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

static bool	object_is_in_shadow(t_data *data, t_hit_record *light_rec, t_hit_record *shadow_rec)
{
	t_vector		rounding_correction;
	t_ray			shadow_ray;
	double			distance_to_light;
	bool			in_shadow;
	t_hit_params	*shadow_params;

	rounding_correction = multiply(&light_rec->normal, 0.0001);
	shadow_ray.origin = add_vectors(&light_rec->point, &rounding_correction);
	shadow_ray.direction = subtract_vectors(&data->light.point, &light_rec->point);
	distance_to_light = length(&shadow_ray.direction);
	shadow_ray.direction = normalize(&shadow_ray.direction);
	shadow_params = get_hit_params();
	shadow_params->closest_so_far = distance_to_light;
	in_shadow = hit_objects(data, &shadow_ray, shadow_params, shadow_rec);
	return (in_shadow);
}

t_color get_pixel_color(t_data *data, t_ray ray, t_hit_record *light_rec, t_hit_record *shadow_rec) 
{
	t_hit_params	*light_params;
	bool			inside_object;
	bool			in_shadow;
	t_color			color;
	t_color			black;
	
	black = get_point(0.0, 0.0, 0.0);
	light_params = get_hit_params();
	if (hit_objects(data, &ray, light_params, light_rec))
	{
		inside_object = dot(&light_rec->normal, &ray.direction) > 0;
		if (inside_object) 
			return (black);
		in_shadow = object_is_in_shadow(data, light_rec, shadow_rec);
		color = apply_shading(data, light_rec, in_shadow);
		return (color);
	}
	else
		return (black);
}

static t_vector	get_total_offset(int x, int y, t_viewport *viewport, t_data *data)
{
	double		x_scaled;
	double		y_scaled;
	t_vector	x_offset_vector;
	t_vector	y_offset_vector;
	t_vector	total_offset;

	x_scaled = 1.0 * x / data->window_width;
	y_scaled = 1.0 * y / data->window_height;
	x_offset_vector = multiply(&viewport->horizontal_offset, x_scaled);
	y_offset_vector = multiply(&viewport->vertical_offset, y_scaled);
	total_offset = add_vectors(&x_offset_vector, &y_offset_vector);
	return (total_offset);
}

static t_vector	get_ray_direction(int x, int y, t_viewport *viewport, t_ray *ray, t_data *data)
{
	t_vector	ray_direction;
	t_vector	total_offset;
	
	total_offset = get_total_offset(x, y, viewport, data);
	ray_direction = add_vectors(&viewport->upper_left_corner, &total_offset);
	ray_direction = subtract_vectors(&ray_direction, &ray->origin);                   
	ray_direction = normalize(&ray_direction);
	return (ray_direction);
}

void	render_image(t_data *data)
{
	t_viewport		viewport;
	t_hit_record	*light_rec;
	t_hit_record	*shadow_rec;
	t_ray			light_ray;
	int				y;
	int				x;
	unsigned int	rgba;
	t_color			pixel_color;

	viewport = set_up_viewport(&data->camera, data->window_width, data->window_height);
	light_rec = get_hit_record();
	shadow_rec = get_hit_record();
	light_ray.origin = data->camera.view_point;
	y = 0;
	while (y < data->window_height)
	{
		x = 0;
		while (x < data->window_width)
		{
			light_ray.direction = get_ray_direction(x, y, &viewport, &light_ray, data);
			pixel_color = get_pixel_color(data, light_ray, light_rec, shadow_rec);       
			rgba = get_rgba((int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z), 255);
			mlx_put_pixel(data->mlx_info->img_ptr, x, y, rgba);
			x++;
		}
		y++;
	}
	free(light_rec);
	free(shadow_rec);
}
