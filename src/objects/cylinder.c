/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:27:47 by felicia           #+#    #+#             */
/*   Updated: 2024/05/05 20:06:42 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	intersection_point_is_within_cylinder_height(t_point *intersection_point, t_cylinder *cylinder)
{
	t_vector	center_to_intersection;
	double		y;

	center_to_intersection = subtract_vectors(intersection_point, &cylinder->center);
	y = dot(&center_to_intersection, &cylinder->axis);
	if (y <= -cylinder->height / 2.0 || y >= cylinder->height / 2.0) 
		return (false);
	return (true);
}

// Quadratic formula for infinite cylinders
void	find_abc_and_discriminant(t_cylinder *cylinder, t_ray *ray, double *abcd)
{
	double		a;
	t_vector	origin_minus_center;
	double		b;
	double		c;
	double		discriminant;

	a = dot(&ray->direction, &ray->direction) - powf(dot(&ray->direction, &cylinder->axis), 2);
    origin_minus_center = subtract_vectors(&ray->origin, &cylinder->center);
    b = 2 * (dot(&ray->direction, &origin_minus_center) - dot(&ray->direction, &cylinder->axis) * dot(&origin_minus_center, &cylinder->axis));
    c = dot(&origin_minus_center, &origin_minus_center) - powf(dot(&origin_minus_center, &cylinder->axis), 2) - powf(cylinder->radius, 2);
	discriminant = b * b - 4 * a * c;
	abcd[0] = a;
	abcd[1] = b;
	abcd[2] = c;
	abcd[3] = discriminant;
}

double find_cylinder_t(t_cylinder *cylinder, t_ray *ray, t_hit_params *params) 
{
	double t;
	double abcd[4];
	
    find_abc_and_discriminant(cylinder, ray, abcd);
	if (abcd[DISCRIMINANT] < 0) 
		return DBL_MIN;
	else if (abcd[DISCRIMINANT] == 0) 
	    t = -abcd[B] / (2 * abcd[A]);
	else 
	{
		double sqrtDiscriminant = sqrt(abcd[DISCRIMINANT]);
		t = (-abcd[B] + sqrtDiscriminant) / (2 * abcd[A]);
		double t2 = (-abcd[B] - sqrtDiscriminant) / (2 * abcd[A]);
		if (t2 >= params->ray_tmin && t2 <= params->closest_so_far) 
			t = t2;
	}
	return t;
}

t_ray transform_ray(t_ray *ray, t_point cylinder_center, t_matrix *rotation_matrix) 
{
	t_ray transformed_ray;

	transformed_ray.origin = subtract_vectors(&ray->origin, &cylinder_center);
	transformed_ray.origin = apply_rotation_matrix(&transformed_ray.origin, rotation_matrix);
	transformed_ray.direction = apply_rotation_matrix(&ray->direction, rotation_matrix);
	return (transformed_ray);
}

t_cylinder transform_cylinder(t_cylinder *cylinder) 
{
	t_cylinder transformed_cylinder;

	transformed_cylinder.center = get_point(0, 0, 0);
	transformed_cylinder.axis = get_point(0, 1, 0);
	transformed_cylinder.radius = cylinder->radius;
	transformed_cylinder.height = cylinder->height;
	transformed_cylinder.color = cylinder->color;
    transformed_cylinder.rotation_matrix = cylinder->rotation_matrix;
    transformed_cylinder.inverse_rotation_matrix = cylinder->inverse_rotation_matrix;
	return (transformed_cylinder);
}

// Handle intersection with infinite cylinder
bool find_cylinder_tube_hit(t_cylinder *transformed_cylinder, t_ray *transformed_ray, t_cylinder *cylinder, t_ray *ray, t_hit_params *params) 
{
	double t;

    t = find_cylinder_t(transformed_cylinder, transformed_ray, params);
	if (t == DBL_MIN)
		return false;
    else if (t >= params->ray_tmin && t <= params->closest_so_far) 
    {
        t_vector intersection_point = trace_ray(transformed_ray, t);
        if (!intersection_point_is_within_cylinder_height(&intersection_point, transformed_cylinder))
            return false;
        t_vector local_normal = subtract_vectors(&intersection_point, &transformed_cylinder->center);
        local_normal.y = 0;
        local_normal = normalize(&local_normal);
        local_normal = apply_rotation_matrix(&local_normal, cylinder->inverse_rotation_matrix);
		record_cylinder_tube_hit(t, cylinder, ray, params->temp_rec, &local_normal);
        params->closest_so_far = t;
		return true;
    }
	return false;
}

// Find the closest intersection with the cylinder
bool find_closer_cylinder_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params)
{
    t_ray transformed_ray = transform_ray(ray, cylinder->center, cylinder->rotation_matrix);
	t_cylinder transformed_cylinder = transform_cylinder(cylinder);
    bool hit_side = false;
    bool hit_cap = false;
    
    hit_side = find_cylinder_tube_hit(&transformed_cylinder, &transformed_ray, cylinder, ray, params);
    hit_cap = find_cylinder_cap_hit(&transformed_cylinder, &transformed_ray, params, ray);
    if (hit_cap || hit_side)
        return true;
    return false;
}