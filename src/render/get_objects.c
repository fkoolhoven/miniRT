/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:12 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/07 19:34:52 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit_record	*get_hit_record(void)
{
	t_hit_record	*rec;

	rec = malloc(sizeof(t_hit_record));
	if (rec == NULL)
		error("malloc failure in get_hit_record()", EXIT_FAILURE);
	rec->point = get_point(0, 0, 0);
	rec->normal = get_point(0, 0, 0);
	// rec->t = 0;
	return (rec);
}

t_hit_params	*get_hit_params(void)
{
	t_hit_params	*params;

	params = malloc(sizeof(t_hit_params));
	if (params == NULL)
		error("malloc failure in get_hit_params()", EXIT_FAILURE);
	params->temp_rec = get_hit_record();
	params->ray_tmin = 0.0;
	params->closest_so_far = DBL_MAX;
	return (params);
}

t_point	get_point(double x, double y, double z)
{
	t_point	point;

	point.x = x;
	point.y = y;
	point.z = z;
	return (point);
}
