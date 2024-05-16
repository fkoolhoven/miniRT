/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:54:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/16 20:04:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	copy_rec_values(t_hit *source, t_hit *dest)
{
	dest->t = source->t;
	dest->point = source->point;
	dest->normal = source->normal;
	dest->color = source->color;
	dest->object_type = source->object_type;
}

static bool	check_all_spheres(t_data *data, t_ray *ray, \
	t_hit_params *params, t_hit *rec)
{
	t_sphere	*current_sphere;

	current_sphere = data->sphere;
	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params))
		{
			copy_rec_values(params->temp_rec, rec);
			if (params->ray_type == SHADOW_RAY)
				return (true);
			params->hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
		}
		current_sphere = current_sphere->next;
	}
	return (params->hit_anything);
}

static bool	check_all_planes(t_data *data, t_ray *ray, \
	t_hit_params *params, t_hit *rec)
{
	t_plane	*current_plane;

	current_plane = data->plane;
	while (current_plane != NULL)
	{
		if (find_closer_plane_hit(current_plane, ray, params))
		{
			copy_rec_values(params->temp_rec, rec);
			if (params->ray_type == SHADOW_RAY)
				return (true);
			params->hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
		}
		current_plane = current_plane->next;
	}
	return (params->hit_anything);
}

static bool	check_all_cylinders(t_data *data, t_ray *ray, \
	t_hit_params *params, t_hit *rec)
{
	t_cylinder	*current_cylinder;

	current_cylinder = data->cylinder;
	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			copy_rec_values(params->temp_rec, rec);
			if (params->ray_type == SHADOW_RAY)
				return (true);
			params->hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
		}
		current_cylinder = current_cylinder->next;
	}
	return (params->hit_anything);
}

static bool	free_mem_and_return(t_hit *temp_rec, bool hit_anything)
{
	free(temp_rec);
	return (hit_anything);
}

bool	hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit *rec)
{
	bool	hit_anything;
	int		ray_type;

	ray_type = params->ray_type;
	hit_anything = false;
	if (data->plane != NULL)
		hit_anything = check_all_planes(data, ray, params, rec);
	if (ray_type == SHADOW_RAY && hit_anything)
		return (free_mem_and_return(params->temp_rec, hit_anything));
	if (data->sphere != NULL)
		hit_anything = check_all_spheres(data, ray, params, rec);
	if (ray_type == SHADOW_RAY && hit_anything)
		return (free_mem_and_return(params->temp_rec, hit_anything));
	if (data->cylinder != NULL)
		hit_anything = check_all_cylinders(data, ray, params, rec);
	return (free_mem_and_return(params->temp_rec, hit_anything));
}
