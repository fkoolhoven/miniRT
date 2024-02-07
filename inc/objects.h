#ifndef OBJECTS_H
# define OBJECTS_H

// sphere.c
bool	find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, t_hit_params *params);

// plane.c
bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_params *params, double *t);
bool	find_closer_plane_hit(t_plane *plane, t_ray *ray, t_hit_params *params);

// cylinder.c
bool	find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params);

#endif