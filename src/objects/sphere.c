/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/12 11:12:53 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static double	get_t_for_sphere(t_sphere_params *sphere_params, t_hit_params *hit_params)
{
	double	discriminant_root;
	double	t;

	discriminant_root = sqrt(sphere_params->discriminant);
	t = (-sphere_params->half_b - discriminant_root) / sphere_params->a;
	if (t <= hit_params->ray_tmin || t >= hit_params->closest_so_far)
	{
		t = (-sphere_params->half_b + discriminant_root) / sphere_params->a;
		if (t <= hit_params->ray_tmin || t >= hit_params->closest_so_far)
			return (-__DBL_MAX__);
	}
	return (t);
}

bool	find_closer_sphere_hit(t_sphere *sphere, t_ray *ray, t_hit_params *hit_params)
{
	t_vector		offset_center;
	t_sphere_params	sphere_params;
	double			t;

	offset_center = subtract_vectors(&ray->origin, &sphere->center);
	sphere_params.a = length_squared(&ray->direction);
	sphere_params.half_b = dot(&offset_center, &ray->direction);
	sphere_params.c = length_squared(&offset_center) - square(sphere->radius);
	sphere_params.discriminant = square(sphere_params.half_b) - sphere_params.a * sphere_params.c;
	if (sphere_params.discriminant < 0)
		return (false);
	t = get_t_for_sphere(&sphere_params, hit_params);
	if (t == -__DBL_MAX__)
		return (false);
	record_sphere_hit(t, sphere, ray, hit_params->rec);
	return (true);
}
