/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:18:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/24 18:23:54 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	check_all_spheres(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_sphere	*current_sphere;

	current_sphere = data->sphere;
	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params))
		{
			params->hit_anything = true;
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				params->inside_object = true;
				return (true);
			}
			params->closest_so_far = params->rec->t;
		}
		current_sphere = current_sphere->next;
	}
	return (params->hit_anything);
}

bool	check_all_planes(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_plane	*current_plane;

	current_plane = data->plane;
	while (current_plane != NULL)
	{
		if (find_closer_plane_hit(current_plane, ray, params))
		{
			params->hit_anything = true;
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				params->inside_object = true;
				return (true);
			}
			params->closest_so_far = params->rec->t;
		}
		current_plane = current_plane->next;
	}
	return (params->hit_anything);
}

bool	check_all_cylinders(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_cylinder	*current_cylinder;

	current_cylinder = data->cylinder;
	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			params->hit_anything = true;
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				params->inside_object = true;
				return (true);
			}
			params->closest_so_far = params->rec->t;
		}
		current_cylinder = current_cylinder->next;
	}
	return (params->hit_anything);
}
