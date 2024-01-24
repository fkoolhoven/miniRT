#ifndef HIT_OBJECTS_H
# define HIT_OBJECTS_H

// sphere.c
bool	find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec);

// plane.c
bool	hit_plane(t_plane *plane, t_ray *ray, double ray_tmin, double ray_tmax, double *t);
bool	find_closer_plane_hit(t_plane *plane, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec);

// cylinder.c
bool	find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, double ray_tmin, double ray_tmax, t_hit_record *rec);

// record_hit.c
void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit_record *rec);
void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit_record *rec);
void	record_cylinder_tube_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
void	record_cylinder_cap_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);

// trace_ray.c
t_point	trace_ray(t_ray *ray, double t);

#endif