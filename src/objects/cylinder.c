#include "minirt.h"

// Checks if the ray hits the plane that the cap is on.
// Then checks if the intersection point is within the radius of the cap.
// Records the hit if it is, because this means a cap was hit.
bool	hit_disk(t_plane *plane, t_ray *ray, t_hit_params *params, double radius) 
{
	double		t;
	t_point		intersection_point;
	t_vector	center_to_intersection;

	if (hit_plane(plane, ray, params, &t))
	{
		intersection_point = trace_ray(ray, t);
		center_to_intersection = subtract_vectors(&intersection_point, &plane->point);
		if (length(&center_to_intersection) > radius)
			return (false);
		record_plane_hit(t, plane, ray, params->temp_rec);
		return (true);
	}
	return (false);
}

// Creates a plane that is parallel to the cap and goes through the center of the cap.
void	create_cap_plane(t_plane *plane, t_cylinder *cylinder, t_point *center)
{
	plane->normal = cylinder->axis;
	plane->color = cylinder->color;
	plane->point = *center;
}

// Calculates the center of the top and bottom cap.
bool find_cap_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params)
{
	bool		hit_bottom_cap;
	bool		hit_top_cap;
	t_vector	top_offset;
	t_vector	bottom_offset;
	t_point		center_bottom_cap;
	t_point		center_top_cap;
	t_plane		bottom_cap;
	t_plane		top_cap;

	hit_bottom_cap = false;
	hit_top_cap = false;
	bottom_offset = multiply(&cylinder->axis, -cylinder->height / 2.0);
	top_offset = multiply(&cylinder->axis, cylinder->height / 2.0);
	center_bottom_cap = add_vectors(&cylinder->center, &bottom_offset);
	center_top_cap = add_vectors(&cylinder->center, &top_offset);
	create_cap_plane(&bottom_cap, cylinder, &center_bottom_cap);
	bottom_cap.normal = multiply(&bottom_cap.normal, -1);
	create_cap_plane(&top_cap, cylinder, &center_top_cap);
	hit_bottom_cap = hit_disk(&bottom_cap, ray, params, cylinder->radius);
	if (hit_bottom_cap)
		params->closest_so_far = params->temp_rec->t;
	hit_top_cap = hit_disk(&top_cap, ray, params, cylinder->radius);
	if (hit_bottom_cap || hit_top_cap)
		return (true);
	return (false);
}

// Checks if the intersection point is within the height of the cylinder.
// Previously, we checked if the intersection point was within the radius of the cylinder,
// which creates an infinite cylinder.
bool	intersection_point_is_within_cylinder_height(t_cylinder *cylinder, t_ray *ray, double t)
{
	t_point		intersection_point;
	t_vector	center_to_intersection;
	double		y;

	intersection_point = trace_ray(ray, t);
	center_to_intersection = subtract_vectors(&intersection_point, &cylinder->center);
	y = dot(&center_to_intersection, &cylinder->axis);
	if (y < -cylinder->height / 2.0 || y > cylinder->height / 2.0) 
		return (false);
	return (true);
}

// Quadratic formula for infinite cylinders
void	find_abc_and_discriminant(t_cylinder *cylinder, t_ray *ray, double *abcd)
{
	double		a;
	t_vector	origin_minus_center;
	double		b;
	double		c;
	double		discriminant;

	a = dot(&ray->direction, &ray->direction) - powf(dot(&ray->direction, &cylinder->axis), 2);
    origin_minus_center = subtract_vectors(&ray->origin, &cylinder->center);
    b = 2 * (dot(&ray->direction, &origin_minus_center) - dot(&ray->direction, &cylinder->axis) * dot(&origin_minus_center, &cylinder->axis));
    c = dot(&origin_minus_center, &origin_minus_center) - powf(dot(&origin_minus_center, &cylinder->axis), 2) - powf(cylinder->radius, 2);
	discriminant = b * b - 4 * a * c;
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = discriminant;
}

// What if light source is inside cylinder? Should we also record the other side of the cylinder? (same goes for spheres)
// handle insides
bool	find_infinite_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params, double *t)
{
	double	abcd[4];
	double	t2;

	find_abc_and_discriminant(cylinder, ray, abcd);
	if (abcd[DISCRIMINANT] < 0) 
	    return (false);
	else if (abcd[DISCRIMINANT] == 0) 
	    *t = -abcd[B] / (2 * abcd[A]);
	else 
	{
		double sqrtDiscriminant = sqrt(abcd[DISCRIMINANT]);
		*t = (-abcd[B] + sqrtDiscriminant) / (2 * abcd[A]);
		t2 = (-abcd[B] - sqrtDiscriminant) / (2 * abcd[A]);
		if (t2 >= params->ray_tmin && t2 <= params->closest_so_far) 
			*t = t2;
	}
	if (*t <= params->ray_tmin || *t >= params->closest_so_far) 
		return (false);
	return (true);
}

bool	find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params) 
{
	double	t;
	bool 	hit_side;
	bool 	hit_cap;

	hit_side = find_infinite_cylinder_hit(cylinder, ray, params, &t);
	if (!hit_side)
		return (false);
	hit_cap = false;
	if (intersection_point_is_within_cylinder_height(cylinder, ray, t)) 
		record_cylinder_tube_hit(t, cylinder, ray, params->temp_rec);
	else
	{
		hit_side = false;
		hit_cap = find_cap_hit(cylinder, ray, params);
	}
	if (!hit_cap && !hit_side)
		return (false);
	return (true);
}