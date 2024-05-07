/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:34 by felicia           #+#    #+#             */
/*   Updated: 2024/05/07 13:21:32 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_OBJECTS_H
# define HIT_OBJECTS_H

// hit_objects.c
bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec);

// record_hit.c
void	record_sphere_hit(t_point hit_point, t_sphere *sphere, t_hit_record *rec);
void	record_plane_hit(t_point hit_point, t_plane *plane, t_hit_record *rec);
void	record_cylinder_hit(t_point hit_point, t_cylinder *cylinder, t_hit_record *rec, t_vector *normal);
t_point	trace_ray(t_ray *ray, double t);

#endif