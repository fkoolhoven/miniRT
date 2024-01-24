#include "minirt.h"

void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	t_vector temp = vector_subtract(&rec->point, &sphere->center);
	rec->normal = divide(&temp, sphere->radius);
	rec->color = sphere->color;
}

void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = get_point(0, 0, 0);
	rec->normal = plane->normal;
	rec->color = plane->color;
}

void	record_cylinder_tube_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	t_vector vectorToCenter = vector_subtract(&cylinder->center, &rec->point);
    double projection = dot(&vectorToCenter, &cylinder->axis);
    t_vector temp = multiply(&cylinder->axis, projection);
    t_vector normal = vector_subtract(&vectorToCenter, &temp);
    rec->normal = normalize(&normal);
}

void	record_cylinder_cap_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = cylinder->axis;
	rec->color = cylinder->color;
}
