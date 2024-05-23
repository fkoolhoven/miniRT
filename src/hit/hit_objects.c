/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:54:02 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/23 21:25:57 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
