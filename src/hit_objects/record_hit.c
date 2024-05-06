/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:42:11 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 13:42:23 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	trace_ray(t_ray *ray, double t)
{
	t_point	ray_location;

	ray_location = multiply(&ray->direction, t);
	ray_location = add_vectors(&ray->origin, &ray_location);
	return (ray_location);
}

void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit_record *rec)
{
	t_vector	intersection_to_center;

	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	intersection_to_center = subtract_vectors(&rec->point, &sphere->center);
	rec->normal = divide(&intersection_to_center, sphere->radius);
	rec->color = sphere->color;
}

void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit_record *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = plane->normal;
	rec->color = plane->color;
}

void	record_cylinder_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vector *normal)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = *normal;
	rec->color = cylinder->color;
}
