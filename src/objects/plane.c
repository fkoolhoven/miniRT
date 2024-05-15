/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:55 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/07 19:32:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	hit_plane(t_plane *plane, t_ray *ray, t_hit_params *params, double *t)
{
	t_vector	offset_point;
	double		denominator;
	double		numerator;

	denominator = dot(&plane->normal, &ray->direction);
	if (denominator == 0)
		return (false);
	offset_point = subtract_vectors(&ray->origin, &plane->point);
	numerator = dot(&plane->normal, &offset_point);
	*t = -numerator / denominator;
	if (*t <= params->ray_tmin || *t >= params->closest_so_far)
		return (false);
	return (true);
}

bool	find_closer_plane_hit(t_plane *plane, t_ray *ray, t_hit_params *params)
{
	double	t;
	t_point	hit_point;

	if (hit_plane(plane, ray, params, &t))
	{
		hit_point = trace_ray(ray, t);
		record_plane_hit(hit_point, plane, params->temp_rec);
		params->closest_so_far = t;
		return (true);
	}
	return (false);
}
