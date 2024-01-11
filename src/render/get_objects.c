#include "minirt.h"

t_viewport	get_viewport() // currently not being used anywhere, will be based on camera FOV
{
	t_viewport	viewport;

	viewport.height = 2.0;
	viewport.width = viewport.height * 1.0 * IMAGE_WIDTH / IMAGE_HEIGHT;
	return (viewport);
}

t_hit_record	*get_hit_record()
{
	t_hit_record	*rec;

	rec = malloc(sizeof(t_hit_record));
	rec->point = get_point(0, 0, 0);
	rec->normal = get_point(0, 0, 0);
	rec->t = 0;
	return (rec);
}

t_point	get_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}