/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:34 by felicia           #+#    #+#             */
/*   Updated: 2024/05/22 17:22:38 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_H
# define HIT_H

// hit_objects.c
bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit *rec);

// check_objects.c
bool	check_all_spheres(t_data *data, t_ray *ray, t_hit_params *params, t_hit *rec);
bool	check_all_planes(t_data *data, t_ray *ray, t_hit_params *params, t_hit *rec);
bool	check_all_cylinders(t_data *data, t_ray *ray, t_hit_params *params, t_hit *rec);

// record_hit.c
void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit *rec);
void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit *rec);
void	record_cylinder_cap_hit(double t, t_plane *cap, t_ray *ray, t_hit *rec);
void	record_cylinder_tube_hit(double t, t_cylinder *cylinder, t_hit *rec, \
			t_cyl_params *cyl_params);
t_point	trace_ray(t_ray *ray, double t);

#endif