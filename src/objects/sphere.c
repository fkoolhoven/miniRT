#include "minirt.h"

static double get_t_for_sphere(double a, double half_b, double discriminant, t_hit_params *params)
{
	double discriminant_root;
	double t;

	discriminant_root = sqrt(discriminant);
	t = (-half_b - discriminant_root) / a;
	if (t <= params->ray_tmin || t >= params->closest_so_far) 
	{
		t = (-half_b + discriminant_root) / a;
		if (t <= params->ray_tmin || t >= params->closest_so_far)
			return (DBL_MIN);
	}
	return (t);
}

bool find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, t_hit_params *params) 
{
	t_vector	offset_center;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		t;

	offset_center = subtract_vectors(&ray->origin, &sphere->center);
	a = dot(&ray->direction, &ray->direction);
	half_b = dot(&offset_center, &ray->direction);
	c = dot(&offset_center, &offset_center) - sphere->radius * sphere->radius;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (false);
	t = get_t_for_sphere(a, half_b, discriminant, params);
	if (t == DBL_MIN)
		return (false);
	record_sphere_hit(t, sphere, ray, params->temp_rec);
	return (true);
}
