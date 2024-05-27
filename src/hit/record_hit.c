/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   record_hit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:42:11 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/27 12:36:27 by fkoolhov         ###   ########.fr       */
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

void	record_sphere_hit(double t, t_sphere *sphere, t_ray *ray, t_hit *rec)
{
	t_vector	intersection_to_center;

	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	intersection_to_center = subtract_vectors(&rec->point, &sphere->center);
	rec->normal = divide(&intersection_to_center, sphere->radius);
	rec->color = sphere->color;
	rec->object_type = SPHERE;
}

void	record_plane_hit(double t, t_plane *plane, t_ray *ray, t_hit *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = plane->normal;
	rec->color = plane->color;
	rec->object_type = PLANE;
}

void	record_cylinder_cap_hit(double t, t_plane *cap, t_ray *ray, t_hit *rec)
{
	rec->t = t;
	rec->point = trace_ray(ray, rec->t);
	rec->normal = cap->normal;
	rec->color = cap->color;
	rec->object_type = CYLINDER_TUBE;
}

void	record_cylinder_tube_hit(double t, t_cylinder *cylinder, \
	t_hit *rec, t_cyl_params *cyl_params)
{
	rec->t = t;
	rec->point = trace_ray(&cyl_params->normal_ray, rec->t);
	rec->normal = cyl_params->local_normal;
	rec->color = cylinder->color;
	rec->object_type = CYLINDER_CAP;
}
