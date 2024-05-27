/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:53:40 by felicia           #+#    #+#             */
/*   Updated: 2024/05/23 21:29:25 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_disk(t_plane *plane, t_hit_params *hit_params, \
	int cap, t_cyl_params *cyl_params)
{
	double		t;
	t_point		hit_point;
	t_vector	distance_to_center;
	t_vector	local_normal;
	t_vector	world_normal;

	if (hit_plane(plane, &cyl_params->rotated_ray, hit_params, &t))
	{
		hit_point = trace_ray(&cyl_params->rotated_ray, t);
		distance_to_center = subtract_vectors(&hit_point, &plane->point);
		if (length(&distance_to_center) > cyl_params->rotated_cylinder.radius)
			return (false);
		else
		{
			local_normal = get_point(0, 1 * cap, 0);
			world_normal = rotate(&local_normal, \
				cyl_params->rotated_cylinder.inverse_rotation);
			plane->normal = world_normal;
			record_cylinder_cap_hit(t, plane, &cyl_params->normal_ray, \
				hit_params->rec);
			hit_params->closest_so_far = t;
			return (true);
		}
	}
	return (false);
}

static t_plane	create_cap_plane(t_cyl_params *cyl_params, int cap)
{
	t_cylinder	*cylinder;
	t_plane		cap_plane;
	t_vector	center_offset;
	t_point		cap_center;

	cylinder = &cyl_params->rotated_cylinder;
	center_offset = multiply(&cylinder->axis, (cylinder->height * cap) / 2.0);
	cap_center = add_vectors(&cylinder->center, &center_offset);
	cap_plane.normal = cylinder->axis;
	cap_plane.color = cylinder->color;
	cap_plane.point = cap_center;
	return (cap_plane);
}

int	find_cylinder_cap_hit(t_hit_params *hit_params, t_cyl_params *cyl_params)
{
	bool	hit_top_cap;
	bool	hit_bottom_cap;
	t_plane	top_plane;
	t_plane	bottom_plane;

	top_plane = create_cap_plane(cyl_params, TOP);
	bottom_plane = create_cap_plane(cyl_params, BOTTOM);
	hit_top_cap = hit_disk(&top_plane, hit_params, TOP, cyl_params);
	hit_bottom_cap = hit_disk(&bottom_plane, hit_params, BOTTOM, cyl_params);
	if (hit_bottom_cap || hit_top_cap)
		return (true);
	return (false);
}
