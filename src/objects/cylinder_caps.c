/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:53:40 by felicia           #+#    #+#             */
/*   Updated: 2024/05/07 13:24:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_disk(t_plane *plane, t_ray *ray, t_hit_params *params, t_cylinder *cylinder, int cap, t_ray *normal_ray)
{
	double		t;
	t_point		hit_point;
	t_vector	distance_to_center;
	t_vector	local_normal;
	t_vector	world_normal;

	if (hit_plane(plane, ray, params, &t))
	{
		hit_point = trace_ray(ray, t);
		distance_to_center = subtract_vectors(&hit_point, &plane->point);
		if (length(&distance_to_center) > cylinder->radius)
			return (false);
		else
		{
			params->closest_so_far = t;
			local_normal = get_point(0, 1 * cap, 0);
			world_normal = rotate(&local_normal, cylinder->inverse_rotation);
			plane->normal = world_normal;
			hit_point = trace_ray(normal_ray, t);
			record_plane_hit(hit_point, plane, params->temp_rec);
			return (true);
		}
	}
	return (false);
}

static t_plane	create_cap_plane(t_cylinder *cylinder, int cap)
{
	t_plane		cap_plane;
	t_vector	center_offset;
	t_point		cap_center;

	center_offset = multiply(&cylinder->axis, (cylinder->height * cap) / 2.0);
	cap_center = add_vectors(&cylinder->center, &center_offset);
	cap_plane.normal = cylinder->axis;
	cap_plane.color = cylinder->color;
	cap_plane.point = cap_center;
	return (cap_plane);
}

int	find_cylinder_cap_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params, t_ray *normal_ray)
{
	bool	hit_top_cap;
	bool	hit_bottom_cap;
	t_plane	top_plane;
	t_plane	bottom_plane;

	top_plane = create_cap_plane(cylinder, TOP_CAP);
	bottom_plane = create_cap_plane(cylinder, BOTTOM_CAP);
	hit_top_cap = hit_disk(&top_plane, ray, params, cylinder, TOP_CAP, normal_ray);
	hit_bottom_cap = hit_disk(&bottom_plane, ray, params, cylinder, BOTTOM_CAP, normal_ray);
	if (hit_bottom_cap || hit_top_cap)
		return (true);
	return (false);
}
