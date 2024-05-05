#include "minirt.h"

bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_params *params, double *t) 
{
	t_vector	offset_point;
	double		denominator;
	double		numerator;
	
	denominator = dot(&plane->normal, &ray->direction);
	if (denominator == 0)
		return (false);
	offset_point = subtract_vectors(&ray->origin, &plane->point);
	numerator = dot(&plane->normal, &offset_point);
	*t = -numerator / denominator;
	if (*t <= params->ray_tmin || *t >= params->closest_so_far)
		return (false);
	return (true);
}

bool	find_closer_plane_hit(t_plane *plane, t_ray *ray, t_hit_params *params)
{
	double	t;

	if (hit_plane(plane, ray, params, &t))
	{
		record_plane_hit(t, plane, ray, params->temp_rec);
		return (true);
	}
	return (false);
}