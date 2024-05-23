/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_objects.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:12 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/23 21:30:08 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	*get_hit_record(void)
{
	t_hit	*rec;

	rec = malloc(sizeof(t_hit));
	if (rec == NULL)
		error("malloc failure in get_hit_record()", EXIT_FAILURE);
	rec->point = get_point(0, 0, 0);
	rec->normal = get_point(0, 0, 0);
	rec->t = 0;
	rec->object_type = 0;
	return (rec);
}

t_hit_params	get_hit_params(int ray_type, t_hit *rec)
{
	t_hit_params	params;

	params.rec = rec;
	params.ray_tmin = 0.0;
	params.closest_so_far = __DBL_MAX__;
	params.hit_anything = false;
	params.ray_type = ray_type;
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
