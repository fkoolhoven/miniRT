/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:34 by felicia           #+#    #+#             */
/*   Updated: 2024/05/15 17:26:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_OBJECTS_H
# define HIT_OBJECTS_H

// hit_objects.c
bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit *rec);

// record_hit.c
void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit *rec);
void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit *rec);
void	record_cylinder_hit(double t, t_cylinder *cylinder, t_hit *rec, \
			t_cyl_params *cyl_params);
t_point	trace_ray(t_ray *ray, double t);

#endif