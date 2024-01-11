#include "minirt.h"

t_sphere	get_test_sphere(double x, double y, double z, double radius)
{
	t_sphere sphere;

	sphere.center = get_point(x, y, z);
	sphere.color = get_point(1, 0, 0);
	sphere.radius = radius;
	sphere.diameter = radius * 2;
	return (sphere);
}

t_camera	get_test_camera()
{
	t_camera camera;

	camera.view_point = get_point(0, 0, 0);
	camera.orientation = get_point(0, 0, -1);
	camera.horizontal_field_of_view = 90;
	return (camera);
}

t_viewport	get_test_viewport()
{
	t_viewport viewport;

	viewport.height = 2.0;
	viewport.width = viewport.height * 1.0 * IMAGE_WIDTH / IMAGE_HEIGHT;
	return (viewport);
}

t_hit_record *get_test_hit_record()
{
	t_hit_record *rec;

	rec = malloc(sizeof(t_hit_record));
	rec->point = get_point(0, 0, 0);
	rec->normal = get_point(0, 0, 0);
	rec->t = 0;
	return (rec);
}