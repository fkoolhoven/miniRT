/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:26 by felicia           #+#    #+#             */
/*   Updated: 2024/05/06 15:14:35 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

// sphere.c
bool		find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, t_hit_params *params);

// plane.c
bool		hit_plane(t_plane *plane, t_ray *ray, t_hit_params *params, double *t);
bool		find_closer_plane_hit(t_plane *plane, t_ray *ray, t_hit_params *params);

// cylinder.c
bool		find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params);

// cylinder_caps.c
int			find_cylinder_cap_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params, t_ray *normal_ray);

// cylinder_transformation.c
t_matrix	*transpose_matrix(t_matrix *m);
t_matrix	*calculate_rotation_matrix(t_vector cylinder_axis);

// cylinder_rotate.c
t_ray		rotate_ray(t_ray *ray, t_point cylinder_center, t_matrix *rotation);
t_cylinder	rotate_cylinder(t_cylinder *cylinder);
t_vector	rotate(t_vector *vector, t_matrix *m);

#endif