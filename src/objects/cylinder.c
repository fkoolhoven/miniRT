/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:27:47 by felicia           #+#    #+#             */
/*   Updated: 2024/05/07 13:22:15 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	within_cylinder_height(t_point *hit_point, t_cylinder *cylinder)
{
	t_vector	center_to_intersection;
	double		y;

	center_to_intersection = subtract_vectors(hit_point, &cylinder->center);
	y = dot(&center_to_intersection, &cylinder->axis);
	if (y <= -cylinder->height / 2.0 || y >= cylinder->height / 2.0)
		return (false);
	return (true);
}

static void	solve_quadratic(t_cylinder *cylinder, t_ray *ray, double *abcd)
{
	double		a;
	t_vector	to_origin;
	double		b;
	double		c;
	double		discriminant;

	a = dot(&ray->direction, &ray->direction);
	a -= powf(dot(&ray->direction, &cylinder->axis), 2);
	to_origin = subtract_vectors(&ray->origin, &cylinder->center);
	b = dot(&to_origin, &cylinder->axis);
	b = dot(&ray->direction, &cylinder->axis) * b;
	b = 2 * (dot(&ray->direction, &to_origin) - b);
	c = dot(&to_origin, &to_origin);
	c -= powf(dot(&to_origin, &cylinder->axis), 2);
	c -= powf(cylinder->radius, 2);
	discriminant = b * b - 4 * a * c;
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = discriminant;
}

static double	get_t_for_cylinder_tube(t_cylinder *cylinder, t_ray *ray, t_hit_params *params)
{
	double	t;
	double	abcd[4];
	double	sqrt_discriminant;
	double	t2;

	solve_quadratic(cylinder, ray, abcd);
	if (abcd[DISCRIMINANT] < 0)
		return (DBL_MIN);
	else if (abcd[DISCRIMINANT] == 0)
		t = -abcd[B] / (2 * abcd[A]);
	else
	{
		sqrt_discriminant = sqrt(abcd[DISCRIMINANT]);
		t = (-abcd[B] + sqrt_discriminant) / (2 * abcd[A]);
		t2 = (-abcd[B] - sqrt_discriminant) / (2 * abcd[A]);
		if (t2 >= params->ray_tmin && t2 <= params->closest_so_far)
			t = t2;
	}
	return (t);
}

static bool	find_cylinder_tube_hit(t_cylinder *rotated_cylinder, t_ray *rotated_ray, t_cylinder *cylinder, t_ray *ray, t_hit_params *params)
{
	double		t;
	t_vector	local_normal;
	t_vector	hit_point;

	t = get_t_for_cylinder_tube(rotated_cylinder, rotated_ray, params);
	if (t == DBL_MIN)
		return (false);
	else if (t >= params->ray_tmin && t <= params->closest_so_far)
	{
		hit_point = trace_ray(rotated_ray, t);
		if (!within_cylinder_height(&hit_point, rotated_cylinder))
			return (false);
		local_normal = subtract_vectors(&hit_point, &rotated_cylinder->center);
		local_normal.y = 0;
		local_normal = normalize(&local_normal);
		local_normal = rotate(&local_normal, cylinder->inverse_rotation);
		hit_point = trace_ray(ray, t);
		record_cylinder_hit(hit_point, cylinder, params->temp_rec, &local_normal);
		params->closest_so_far = t;
		return (true);
	}
	return (false);
}

bool	find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params)
{
	t_ray		rotated_ray;
	t_cylinder	rotated_cylinder;
	bool		hit_side;
	bool		hit_cap;

	rotated_ray = rotate_ray(ray, cylinder->center, cylinder->rotation);
	rotated_cylinder = rotate_cylinder(cylinder);
	hit_side = find_cylinder_tube_hit(&rotated_cylinder, &rotated_ray, cylinder, ray, params);
	hit_cap = find_cylinder_cap_hit(&rotated_cylinder, &rotated_ray, params, ray);
	if (hit_cap || hit_side)
		return (true);
	return (false);
}
