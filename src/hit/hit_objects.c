/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:54:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 17:19:17 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
