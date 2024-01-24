#include "minirt.h"

// What if the plane is parallel to the ray?
bool	hit_plane(t_plane *plane, t_ray *ray, double ray_tmin, double ray_tmax, double *t) 
{
	t_vector	offset_point;
	double		denominator;
	double		numerator;
	
	denominator = dot(&plane->normal, &ray->direction);
	offset_point = vector_subtract(&ray->origin, &plane->point);
	numerator = dot(&plane->normal, &offset_point);
	*t = -numerator / denominator;
	if (*t <= ray_tmin || *t >= ray_tmax)
		return (false); // Didn't find a closer hit
	return (true); // Found a closer hit
}

bool	find_closer_plane_hit(t_plane *plane, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec)
{
	double	t;

	if (hit_plane(plane, ray, ray_tmin, ray_tmax, &t))
	{
		record_plane_hit(t, plane, ray, rec);
		return (true);
	}
	return (false);
}