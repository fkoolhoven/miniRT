#include "minirt.h"

t_point	get_point(double x, double y, double z)
{
	t_point point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}

double	dot(const t_vector *u, const t_vector *v) 
{
    return (u->x * v->x + u->y * v->y + u->z * v->z);
}

t_viewport	setup_viewport()
{
	t_viewport viewport;

	viewport.height = 2.0;
	viewport.width = viewport.height * 1.0 * IMAGE_WIDTH / IMAGE_HEIGHT;
	return (viewport);
}

t_point trace_ray(t_ray ray, double t)
{
	t_point ray_location;
	// P(t) = A + tb
	ray_location = multiply(&ray.direction, t);
	ray_location = vector_add(&ray.origin, &ray_location);
    return (ray_location); // not neccessary?
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

double length_squared(t_vector *v) 
{
    return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double length(t_vector *v)
{
    return sqrt(length_squared(v));
}

t_vector unit_vector(t_vector *v) 
{
	return (divide(v, length(v)));
}

double hit_sphere(t_sphere *sphere, t_ray *ray) 
{
	t_vector offset_center;
	double a;
	double half_b;
	double c;
	double discriminant;

	offset_center = vector_subtract(&ray->origin, &sphere->center);
	a = length_squared(&ray->direction);
	half_b = dot(&offset_center, &ray->direction);
	c = length_squared(&offset_center) - (sphere->diameter / 2) * (sphere->diameter / 2);
	discriminant = half_b * half_b - a * c;

	if (discriminant < 0) 
	{
        return (-1.0);
    } 
	else 
	{
        return ((-half_b - sqrt(discriminant)) / a);
    }
}

t_sphere	get_test_sphere()
{
	t_sphere sphere;

	sphere.center = get_point(0, 0, -1);
	sphere.color = get_point(1, 0, 0);
	sphere.diameter = 1.0;
	return (sphere);
}

t_color ray_color(t_ray ray) 
{
	t_sphere sphere = get_test_sphere();

	double t = hit_sphere(&sphere, &ray);
	if (t > 0.0) 
	{
		t_vector temp1 = { 0, 0, -1 };
		t_vector temp2 = trace_ray(ray, t);
		t_vector temp3 = vector_subtract(&temp2, &temp1);
        t_vector N = unit_vector(&temp3);
		t_color temp4 = { N.x + 1, N.y + 1, N.z + 1 };
        return (multiply(&temp4, 0.5));
    }

    t_vector unit_direction = unit_vector(&ray.direction);
    double a = 0.5 * (unit_direction.y + 1.0);

	t_color temp1 = get_point(1.0, 1.0, 1.0);
	t_color temp2 = get_point(0.5, 0.7, 1.0);
	temp1 = multiply(&temp1, 1.0 - a);
	temp2 = multiply(&temp2, a);
    return (vector_add(&temp1, &temp2));
}

void	render_image(mlx_image_t *img_ptr, t_camera *camera)
{
	t_vector upper_left_corner;
	t_vector horizontal_offset;
	t_vector vertical_offset;
	int y;
	int x;

	upper_left_corner = get_point(-2.0, 1.0, -1.0);
	horizontal_offset = get_point(4.0, 0.0, 0.0);
	vertical_offset = get_point(0.0, -2.0, 0.0);

	t_ray ray;
	ray.origin = camera->view_point;

	y = 0;
    while (y < IMAGE_HEIGHT) 
	{
		x = 0;
        while (x < IMAGE_WIDTH) 
		{
			double x_scaled = (double)x / IMAGE_WIDTH;
			double y_scaled = (double)y / IMAGE_HEIGHT;
			t_vector x_offset_vector = multiply(&horizontal_offset, x_scaled);
			t_vector y_offset_vector = multiply(&vertical_offset, y_scaled);
			t_vector total_offset = vector_add(&x_offset_vector, &y_offset_vector);
			ray.direction = vector_add(&upper_left_corner, &total_offset);
            t_color pixel_color = ray_color(ray);
			int rgba = get_rgba((int)(255.999 * pixel_color.x), (int)(255.999 * pixel_color.y), (int)(255.999 * pixel_color.z), 255);
			mlx_put_pixel(img_ptr, x, y, rgba);
			x++;
        }
		y++;
    }
}

t_camera	get_test_camera()
{
	t_camera camera;

	camera.view_point = get_point(0, 0, 0);
	camera.orientation = get_point(0, 0, -1);
	camera.horizontal_field_of_view = 90;
	return (camera);
}

void	test(mlx_image_t *img_ptr)
{
	t_camera camera = get_test_camera();
	render_image(img_ptr, &camera);
}