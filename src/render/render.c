#include "minirt.h"

t_point	trace_ray(t_ray *ray, double t)
{
	t_point ray_location;
	// INTERSECTION(t) = ORIGIN + tDIRECTION
	ray_location = multiply(&ray->direction, t);
	ray_location = vector_add(&ray->origin, &ray_location);
	return (ray_location);
}

void	record_new_closer_hit(double root, t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	rec->t = root;
	rec->point = trace_ray(ray, rec->t);
	t_vector temp = vector_subtract(&rec->point, &sphere->center);
	rec->normal = divide(&temp, sphere->radius);
}

double find_closer_hit(t_sphere *sphere, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec) 
{
	t_vector offset_center;
	double a;
	double half_b;
	double c;
	double discriminant;

	offset_center = vector_subtract(&ray->origin, &sphere->center);
	a = length_squared(&ray->direction);
	half_b = dot(&offset_center, &ray->direction);
	c = length_squared(&offset_center) - sphere->radius * sphere->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0) // no sphere was hit 
		return (false);

	// continue to try to find the real point of intersection (if any)
    double discriminant_root = sqrt(discriminant);
    double try_root = (-half_b - discriminant_root) / a;
    if (try_root <= ray_tmin || try_root >= ray_tmax)  // first root out of range
	{
		try_root = (-half_b + discriminant_root) / a; // try other root
		if (try_root <= ray_tmin || try_root >= ray_tmax)
		{
			return (false); // both roots out of range, no sphere was hit
		}
	}
	record_new_closer_hit(try_root, sphere, ray, rec); // a sphere was hit, record at which point
	return (true);
}

bool try_to_hit_objects(t_data *data, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec)
{
	t_hit_record *temp_rec = get_hit_record();
	bool hit_anything = false;
	double closest_so_far = ray_tmax;

	t_sphere *current_sphere = data->sphere;
	while (current_sphere != NULL) 
	{
		if (find_closer_hit(current_sphere, ray, ray_tmin, closest_so_far, temp_rec)) 
		{
			hit_anything = true;
			closest_so_far = temp_rec->t;
			*rec = *temp_rec;
		}
		current_sphere = current_sphere->next;
	}
	free(temp_rec);
	return (hit_anything);
}

t_color get_ray_color(t_data *data, t_ray ray) 
{
	t_hit_record *rec = get_hit_record();

	if (try_to_hit_objects(data, &ray, 0.0, DBL_MAX, rec)) // an object was hit, color it
	{
		t_vector temp = get_point(rec->normal.x + 1, rec->normal.y + 1, rec->normal.z + 1);
		free(rec);
		return (multiply(&temp, 0.5));
	}
	else // no object was hit, color background
	{
		free(rec);
		t_vector unit_direction = unit_vector(&ray.direction);
		double a = 0.5 * (unit_direction.y + 1.0);
		t_color start_color = get_point(1.0, 1.0, 1.0);
		t_color end_color = get_point(0.5, 0.7, 1.0);
		start_color = multiply(&start_color, 1.0 - a);
		end_color = multiply(&end_color, a);
		return (vector_add(&start_color, &end_color));
	}
}

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
			t_color pixel_color = get_ray_color(data, ray);
			int rgba = get_rgba((int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z), 255);
			mlx_put_pixel(img_ptr, x, y, rgba);
			x++;
		}
		y++;
	}
}
