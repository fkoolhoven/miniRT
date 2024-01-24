#include "minirt.h"

// INTERSECTION(t) = ORIGIN + tDIRECTION
t_point	trace_ray(t_ray *ray, double t)
{
	t_point ray_location;

	ray_location = multiply(&ray->direction, t);
	ray_location = vector_add(&ray->origin, &ray_location);
	return (ray_location);
}