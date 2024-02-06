#include "minirt.h"

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