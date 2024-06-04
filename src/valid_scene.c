/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:35:46 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/04 18:47:18 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	inside_sphere(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_sphere	*current_sphere;

	current_sphere = data->sphere;
	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params))
		{
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				return (true);
			}
		}
		current_sphere = current_sphere->next;
	}
	return (false);
}

static bool	inside_cylinder(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_cylinder	*current_cylinder;

	current_cylinder = data->cylinder;
	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				return (true);
			}
		}
		current_cylinder = current_cylinder->next;
	}
	return (false);
}

static bool	light_is_inside_object(t_data *data)
{
	t_hit_params	params;
	t_ray			ray;
	t_hit			*rec;

	ray.origin = data->light.origin;
	ray.direction = get_point(1, 1, 1);
	rec = get_hit_record();
	params = get_hit_params(LIGHT_RAY, rec);
	if (inside_sphere(data, &ray, &params))
	{
		free(rec);
		return (true);
	}
	if (inside_cylinder(data, &ray, &params))
	{
		free(rec);
		return (true);
	}
	free(rec);
	return (false);
}

bool	scene_is_valid(t_data *data)
{
	if (!data->camera.is_initialized)
		error("No camera", EXIT_FAILURE);
	else if (!data->light.is_initialized)
		error("No light", EXIT_FAILURE);
	else if (!data->ambient.is_initialized)
		error("No ambient light", EXIT_FAILURE);
	else if (data->window_width <= 0 || data->window_height <= 0)
		error("Invalid window size", EXIT_FAILURE);
	else if (data->plane == NULL && data->sphere == NULL
		&& data->cylinder == NULL)
		error("No objects", EXIT_FAILURE);
	else if (light_is_inside_object(data))
		error("Light is inside object", EXIT_FAILURE);
	return (true);
}
