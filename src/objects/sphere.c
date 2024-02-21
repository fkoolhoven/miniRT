#include "minirt.h"

typedef enum
{
	a,
	half_b,
	c,
	discriminant
}	QUADRATIC_EQUATION;

/*
	this function takes in a sphere and a ray, it will determine
	with a quadratic equation if there is any intersection in the ray's direction
*/
bool	sphere_hit(t_sphere *sphere, t_ray *ray, double qa[])
{
	t_vector	offset;

	offset = subtract_vectors(&ray->origin, &sphere->center);
	qa[a] = dot(&ray->direction, &ray->direction);
	qa[half_b] = dot(&offset, &ray->direction);
	qa[c] = dot(&offset, &offset) - sphere->radius * sphere->radius;
	qa[discriminant] = qa[half_b] * qa[half_b] - qa[a] * qa[c];
	if (qa[discriminant] < 0)
		return (false);
	return (true);
}

bool	find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, t_hit_params *params) 
{
	double		qa[4];
	double		try_root;
	double		discriminant_root;

	if (sphere_hit(sphere, ray, qa) == false)
		return (false);
	// continue to try to find the real point of intersection (if any)
	discriminant_root = sqrt(qa[discriminant]);
	if (!qa[discriminant])
	{
		printf("0: root 1: %f, root 2: %f\n", (-qa[half_b] - discriminant_root) / qa[a], (-qa[half_b] + discriminant_root) / qa[a]);
	}
	try_root = (-qa[half_b] - discriminant_root) / qa[a];
	if (try_root <= params->ray_tmin || try_root >= params->closest_so_far) // first root out of range
	{
		try_root = (-qa[half_b] + discriminant_root) / qa[a];
		if (try_root <= params->ray_tmin || try_root >= params->closest_so_far)
			return (false); // both roots out of range, no sphere was hit
	}
	record_sphere_hit(try_root, sphere, ray, params->temp_rec);
	return (true);
}
