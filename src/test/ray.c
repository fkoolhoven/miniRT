#include "minirt.h"

t_point trace_ray(t_ray *ray, double t)
{
	t_point ray_location;
	// P(t) = A + tb
	ray_location = multiply(&ray->direction, t);
	ray_location = vector_add(&ray->origin, &ray_location);
    return (ray_location); // not neccessary?
}