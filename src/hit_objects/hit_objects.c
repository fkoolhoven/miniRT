/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:54:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 16:18:28 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	check_all_spheres(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	t_sphere	*current_sphere;
	bool		hit_anything;

	current_sphere = data->sphere;
	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params))
		{
			hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
			*rec = *params->temp_rec;
		}
		current_sphere = current_sphere->next;
	}
	return (hit_anything);
}

static bool	check_all_planes(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	t_plane	*current_plane;
	bool	hit_anything;

	current_plane = data->plane;
	while (current_plane != NULL)
	{
		if (find_closer_plane_hit(current_plane, ray, params))
		{
			hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
			*rec = *params->temp_rec;
		}
		current_plane = current_plane->next;
	}
	return (hit_anything);
}

static bool	check_all_cylinders(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	t_cylinder	*current_cylinder;
	bool		hit_anything;

	current_cylinder = data->cylinder;
	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
			*rec = *params->temp_rec;
		}
		current_cylinder = current_cylinder->next;
	}
	return (hit_anything);
}

bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	bool	hit_anything;

	hit_anything = check_all_spheres(data, ray, params, rec);
	hit_anything = check_all_planes(data, ray, params, rec);
	hit_anything = check_all_cylinders(data, ray, params, rec);
	free(params->temp_rec);
	free(params);
	return (hit_anything);
}
