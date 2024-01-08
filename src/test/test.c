#include "minirt.h"

double	dot(const t_vector *u, const t_vector *v) 
{
    return (u->x * v->x + u->y * v->y + u->z * v->z);
}

t_viewport	setup_viewport()
{
	t_viewport viewport;

	viewport.height = 2.0;
	viewport.width = viewport.height * (double)IMAGE_WIDTH / IMAGE_HEIGHT;
	return (viewport);
}

t_point trace_ray(t_ray ray, double t)
{
	// P(t) = A + tb
	ray.location = multiply(&ray.direction, t);
	ray.location = vector_add(&ray.origin, &ray.location);
    return (ray.location); // not neccessary
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
	double b;
	double c;
	double discriminant;

	offset_center = vector_subtract(&ray->origin, &sphere->center);
	a = dot(&ray->direction, &ray->direction);
	b = 2.0 * dot(&offset_center, &ray->direction);
	c = dot(&offset_center, &offset_center) - sphere->diameter / 2.0 * sphere->diameter / 2.0;
	discriminant = b * b - 4 * a * c;

	if (discriminant < 0) 
	{
        return -1.0;
    } 
	else 
	{
        return (-b - sqrt(discriminant) ) / (2.0 * a);
    }
}

t_sphere	get_test_sphere()
{
	t_sphere sphere;

	sphere.center.x = 0;
	sphere.center.y = 0;
	sphere.center.z = -1;
	sphere.diameter = 1.0;
	sphere.color.x = 1.0;
	sphere.color.y = 0.0;
	sphere.color.z = 0.0;
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

    t_vector unit_direction = divide(&ray.direction, length(&ray.direction));
    double a = 0.5 * (unit_direction.y + 1.0);

	t_color temp1;
	temp1.x = 1.0;
	temp1.y = 1.0;
	temp1.z = 1.0;

	t_color temp2;
	temp2.x = 0.5;
	temp2.y = 0.7;
	temp2.z = 1.0;

	temp1 = multiply(&temp1, 1.0 - a);
	temp2 = multiply(&temp2, a);
    return (vector_add(&temp1, &temp2));
}

void	render_image(t_vector *pixel_delta_u, t_vector *pixel_delta_v, t_point *pixel00_loc, const t_camera *camera, mlx_image_t *img_ptr)
{
	t_ray ray;
	int y;
	int x;

	y = 0;
    while (y < IMAGE_HEIGHT) 
	{
		x = 0;
        while (x < IMAGE_WIDTH) 
		{
			t_vector temp1 = multiply(pixel_delta_u, (double)x);
			t_vector temp2 = multiply(pixel_delta_v, (double)y);
			t_vector temp3 = vector_add(&temp1, &temp2);
            t_point pixel_center = vector_add(pixel00_loc, &temp3);
            ray.direction = vector_subtract(&pixel_center, &camera->view_point);

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

	camera.view_point.x = 0;
	camera.view_point.y = 0;
	camera.view_point.z = 0;
	camera.orientation.x = 0;
	camera.orientation.y = 0;
	camera.orientation.z = 0;
	camera.horizontal_field_of_view = 90;
	return (camera);
}

void	test(mlx_image_t *img_ptr)
{
	t_camera camera = get_test_camera();
	t_viewport viewport = setup_viewport();
	double focal_length = 1.0;
    t_vector viewport_u;
	viewport_u.x = viewport.width;
	viewport_u.y = 0;
	viewport_u.z = 0;

	t_vector viewport_v;
	viewport_v.x = 0;
	viewport_v.y = -viewport.height;
	viewport_v.z = 0;

    t_vector pixel_delta_u = divide(&viewport_u, (double)IMAGE_WIDTH);
    t_vector pixel_delta_v = divide(&viewport_v, (double)IMAGE_HEIGHT);

	t_point temp1;
	temp1.x = 0;
	temp1.y = 0;
	temp1.z = focal_length;

	t_point temp2 = divide(&viewport_u, 2.0);
	t_point temp3 = divide(&viewport_v, 2.0);
	t_point temp4 = vector_subtract(&camera.view_point, &temp1);
	t_point viewport_upper_left = vector_subtract(&temp4, &temp2);
	t_point temp5 = vector_subtract(&viewport_upper_left, &temp3);

	t_point pixel00_loc = multiply(&temp5, 0.5);
	pixel00_loc = vector_add(&pixel00_loc, &pixel_delta_u);
	pixel00_loc = vector_add(&pixel00_loc, &pixel_delta_v);
	render_image(&pixel_delta_u, &pixel_delta_v, &pixel00_loc, &camera, img_ptr);
}