#include "minirt.h"

bool	find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec) 
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
	record_sphere_hit(try_root, sphere, ray, rec);
	return (true);
}