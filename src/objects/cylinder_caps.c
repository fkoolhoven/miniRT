/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:53:40 by felicia           #+#    #+#             */
/*   Updated: 2024/06/01 15:12:09 by fkoolhov         ###   ########.fr       */
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

int	find_closest_cap(t_plane *top, t_plane *bottom, t_cyl_params *cyl_params)
{
	t_point		camera_position;
	t_vector	top_to_camera;
	t_vector	bottom_to_camera;
	double		distance_to_top_cap;
	double		distance_to_bottom_cap;

	camera_position = cyl_params->rotated_ray.origin;
	top_to_camera = subtract_vectors(&top->point, &camera_position);
	distance_to_top_cap = length(&top_to_camera);
	bottom_to_camera = subtract_vectors(&bottom->point, &camera_position);
	distance_to_bottom_cap = length(&bottom_to_camera);
	if (distance_to_top_cap < distance_to_bottom_cap)
		return (TOP);
	else
		return (BOTTOM);
}

int	find_cylinder_cap_hit(t_hit_params *hit_params, t_cyl_params *cyl_params)
{
	t_plane	top_plane;
	t_plane	bottom_plane;
	int		closest_cap;
	bool	hit_cap;

	top_plane = create_cap_plane(cyl_params, TOP);
	bottom_plane = create_cap_plane(cyl_params, BOTTOM);
	closest_cap = find_closest_cap(&top_plane, &bottom_plane, cyl_params);
	if (closest_cap == BOTTOM)
	{
		hit_cap = hit_disk(&bottom_plane, hit_params, BOTTOM, cyl_params);
		return (hit_cap);
	}
	else
	{
		hit_cap = hit_disk(&top_plane, hit_params, TOP, cyl_params);
		return (hit_cap);
	}
}
