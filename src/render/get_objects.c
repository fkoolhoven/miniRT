#include "minirt.h"

t_hit_record	*get_hit_record()
{
	t_hit_record	*rec;

	rec = malloc(sizeof(t_hit_record));
	if (rec == NULL)
	{
		// handle error
	}
	rec->point = get_point(0, 0, 0);
	rec->normal = get_point(0, 0, 0);
	rec->t = 0;
	return (rec);
}

t_hit_params	*get_hit_params()
{
	t_hit_params	*params;

	params = malloc(sizeof(t_hit_params));
	if (params == NULL)
	{
		// handle error
	}
	params->temp_rec = get_hit_record();
	params->ray_tmin = 0.0;
	params->closest_so_far = DBL_MAX;
	params->hit_anything = false;
	return (params);
}

t_point	get_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}