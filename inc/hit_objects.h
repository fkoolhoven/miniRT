#ifndef HIT_OBJECTS_H
# define HIT_OBJECTS_H

// hit_objects.c
bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec);

// record_hit.c
void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit_record *rec);
void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit_record *rec);
void	record_cylinder_tube_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
void	record_cylinder_cap_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec);
t_point	trace_ray(t_ray *ray, double t);

#endif