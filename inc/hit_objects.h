#ifndef HIT_OBJECTS_H
# define HIT_OBJECTS_H

// sphere.c
double	find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec);

// plane.c
double	find_closer_plane_hit(t_plane *plane, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec);

// cylinder.c
double	find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec);

// record_hit.c
void	record_new_closer_hit(double root, void *object, int type, t_ray *ray, t_hit_record *rec);

#endif