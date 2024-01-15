#include "minirt.h"

t_point	trace_ray(t_ray *ray, double t)
{
	t_point ray_location;
	// INTERSECTION(t) = ORIGIN + tDIRECTION
	ray_location = multiply(&ray->direction, t);
	ray_location = vector_add(&ray->origin, &ray_location);
	return (ray_location);
}

void	record_new_closer_hit(double root, void *object, int type, t_ray *ray, t_hit_record *rec)
{
	t_sphere *sphere;
	t_plane *plane;
	t_cylinder *cylinder;

	sphere = NULL;
	plane = NULL;
	cylinder = NULL;
	rec->t = root;
	rec->point = trace_ray(ray, rec->t);
	if (type == SPHERE)
	{
		sphere = (t_sphere *)object;
		t_vector temp = vector_subtract(&rec->point, &sphere->center);
		rec->normal = divide(&temp, sphere->radius);
		rec->color = sphere->color;
	}
	else if (type == PLANE)
	{
		plane = (t_plane *)object;
		rec->normal = plane->axis;
		rec->color = plane->color;
	}
	else if (type == CYLINDER)
	{
		cylinder = (t_cylinder *)object;
		rec->normal = get_point(0, 0, 0); // calculate normal of cylinder
		rec->color = cylinder->color;
	}
}