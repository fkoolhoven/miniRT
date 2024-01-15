#include "minirt.h"

// What if the plane is parallel to the ray?
double find_closer_plane_hit(t_plane *plane, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec) 
{
	t_vector	normalized_ray_direction;
	t_vector	offset_point;
	double		denominator;
	double		numerator;
	double		t;
	
	normalized_ray_direction = unit_vector(&ray->direction);
	offset_point = vector_subtract(&ray->origin, &plane->point);
	denominator = dot(&plane->normal, &normalized_ray_direction);
	numerator = dot(&plane->normal, &offset_point);
	t = -numerator / denominator;
	if (t <= ray_tmin || t >= ray_tmax)
		return (false); // Didn't find a closer hit
	record_new_closer_hit(t, plane, PLANE, ray, rec);
	return (true); // Found a closer hit
}