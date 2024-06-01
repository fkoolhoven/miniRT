/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:27:47 by felicia           #+#    #+#             */
/*   Updated: 2024/06/01 15:03:52 by fkoolhov         ###   ########.fr       */
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

static void	solve_quadratic(t_cyl_params *cyl_params)
{
	t_vector	to_origin;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	to_origin = subtract_vectors(&cyl_params->rotated_ray.origin, \
		&cyl_params->rotated_cylinder.center);
	a = length_squared(&cyl_params->rotated_ray.direction);
	a -= square(dot(&cyl_params->rotated_ray.direction, \
		&cyl_params->rotated_cylinder.axis));
	b = dot(&to_origin, &cyl_params->rotated_cylinder.axis);
	b = dot(&cyl_params->rotated_ray.direction, \
		&cyl_params->rotated_cylinder.axis) * b;
	b = 2 * (dot(&cyl_params->rotated_ray.direction, &to_origin) - b);
	c = length_squared(&to_origin);
	c -= square(dot(&to_origin, &cyl_params->rotated_cylinder.axis));
	c -= square(cyl_params->rotated_cylinder.radius);
	discriminant = b * b - 4 * a * c;
	cyl_params->a = a;
	cyl_params->b = b;
	cyl_params->c = c;
	cyl_params->discriminant = discriminant;
}

static double	get_t_for_cylinder_tube(t_cyl_params *cyl_params, \
	t_hit_params *hit_params)
{
	double	t;
	double	sqrt_discriminant;
	double	t2;

	solve_quadratic(cyl_params);
	if (cyl_params->discriminant < 0)
		return (-__DBL_MAX__);
	else if (cyl_params->discriminant == 0)
		t = -cyl_params->b / (2 * cyl_params->a);
	else
	{
		sqrt_discriminant = sqrt(cyl_params->discriminant);
		t = (-cyl_params->b + sqrt_discriminant) / (2 * cyl_params->a);
		t2 = (-cyl_params->b - sqrt_discriminant) / (2 * cyl_params->a);
		if (t2 >= hit_params->ray_tmin && t2 <= hit_params->closest_so_far)
			t = t2;
	}
	return (t);
}

static bool	find_cylinder_tube_hit(t_cylinder *cylinder, \
	t_hit_params *hit_params, t_cyl_params *cyl_params)
{
	double		t;
	t_vector	local_normal;
	t_vector	hit_point;

	t = get_t_for_cylinder_tube(cyl_params, hit_params);
	if (t == -__DBL_MAX__)
		return (false);
	else if (t >= hit_params->ray_tmin && t <= hit_params->closest_so_far)
	{
		hit_point = trace_ray(&cyl_params->rotated_ray, t);
		if (!within_cylinder_height(&hit_point, &cyl_params->rotated_cylinder))
			return (false);
		local_normal = subtract_vectors(&hit_point, \
			&cyl_params->rotated_cylinder.center);
		local_normal.y = 0;
		local_normal = normalize(&local_normal);
		local_normal = rotate(&local_normal, cylinder->inverse_rotation);
		cyl_params->local_normal = local_normal;
		record_cylinder_tube_hit(t, cylinder, hit_params->rec, cyl_params);
		hit_params->closest_so_far = t;
		return (true);
	}
	return (false);
}

bool	find_closer_cylinder_hit(t_cylinder *cylinder,
	t_ray *ray, t_hit_params *hit_params) \
{
	t_cyl_params	cyl_params;
	bool			hit_side;
	bool			hit_cap;

	cyl_params.normal_ray = *ray;
	cyl_params.rotated_ray = rotate_ray(ray, cylinder);
	cyl_params.rotated_cylinder = rotate_cylinder(cylinder);
	hit_side = find_cylinder_tube_hit(cylinder, hit_params, &cyl_params);
	// if (hit_side)
	// {
	// 	printf("s t: %f\n", hit_params->closest_so_far);
	// }
	hit_cap = find_cylinder_cap_hit(hit_params, &cyl_params);
	// if (hit_cap)
	// {
	// 	printf("c t: %f\n", hit_params->closest_so_far);
	// }
	if (hit_cap || hit_side)
		return (true);
	return (false);
}
