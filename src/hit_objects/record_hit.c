#include "minirt.h"

// INTERSECTION(t) = ORIGIN + tDIRECTION
t_point	trace_ray(t_ray *ray, double t)
{
	t_point ray_location;

	ray_location = multiply(&ray->direction, t);
	ray_location = add_vectors(&ray->origin, &ray_location);
	return (ray_location);
}

void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vector intersection_to_center;

	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	intersection_to_center = subtract_vectors(&rec->point, &sphere->center);
	rec->normal = divide(&intersection_to_center, sphere->radius);
	rec->color = sphere->color;
}

void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = plane->normal;
	rec->color = plane->color;
}

void	record_cylinder_tube_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	t_vector	point_to_center;
	t_vector	temp_normal;
	double		projection;

	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	point_to_center = subtract_vectors(&rec->point, &cylinder->center);
	projection = dot(&point_to_center, &cylinder->axis);
	temp_normal = multiply(&cylinder->axis, projection);
	temp_normal = subtract_vectors(&point_to_center, &temp_normal);
	rec->normal = normalize(&temp_normal);
	rec->color = cylinder->color;
}

void	record_cylinder_cap_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = cylinder->axis;
	rec->color = cylinder->color;
}
