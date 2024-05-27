/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:54:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/27 13:14:25 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_all_spheres(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_sphere	*current_sphere;

	current_sphere = data->sphere;
	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params))
		{
			params->hit_anything = true;
			if (dot(&params->rec->normal, &ray->direction) > 0.0001)
			{
				params->inside_object = true;
				return (params->hit_anything);
			}
			params->closest_so_far = params->rec->t;
		}
		current_sphere = current_sphere->next;
	}
	return (params->hit_anything);
}

static bool	check_all_planes(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_plane	*current_plane;

	current_plane = data->plane;
	while (current_plane != NULL)
	{
		if (find_closer_plane_hit(current_plane, ray, params))
		{
			params->hit_anything = true;
			if (dot(&params->rec->normal, &ray->direction) > 0.0001)
			{
				params->inside_object = true;
				return (params->hit_anything);
			}
			params->closest_so_far = params->rec->t;
		}
		current_plane = current_plane->next;
	}
	return (params->hit_anything);
}

static bool	check_all_cylinders(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_cylinder	*current_cylinder;

	current_cylinder = data->cylinder;
	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			params->hit_anything = true;
			if (dot(&params->rec->normal, &ray->direction) > 0.0001)
			{
				params->inside_object = true;
				return (params->hit_anything);
			}
			params->closest_so_far = params->rec->t;
		}
		current_cylinder = current_cylinder->next;
	}
	return (params->hit_anything);
}

bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params)
{
	bool	hit_anything;
	int		ray_type;

	ray_type = params->ray_type;
	hit_anything = false;
	if (data->plane != NULL)
		hit_anything = check_all_planes(data, ray, params);
	if (ray_type == SHADOW_RAY && hit_anything)
		return (hit_anything);
	if (data->sphere != NULL)
		hit_anything = check_all_spheres(data, ray, params);
	if (ray_type == SHADOW_RAY && hit_anything)
		return (hit_anything);
	if (data->cylinder != NULL)
		hit_anything = check_all_cylinders(data, ray, params);
	return (hit_anything);
}
