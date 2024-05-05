/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_caps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 19:53:40 by felicia           #+#    #+#             */
/*   Updated: 2024/05/05 19:59:53 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	hit_disk(t_plane *plane, t_ray *ray, t_hit_params *params, double radius) 
{
	double		t;
	t_point		intersection_point;
	t_vector	center_to_intersection;

	if (hit_plane(plane, ray, params, &t))
	{
		intersection_point = trace_ray(ray, t);
		center_to_intersection = subtract_vectors(&intersection_point, &plane->point);
		if (length(&center_to_intersection) > radius)
			return (false);
        else
        {
            record_plane_hit(t, plane, ray, params->temp_rec);
            return (true);
        }
	}
	return (false);
}

static bool hit_caps(t_plane *cap_plane, t_ray *ray, t_hit_params *params, t_cylinder *cylinder, int cap, t_ray *normal_ray)
{
    bool hit_cap;
    
    hit_cap = hit_disk(cap_plane, ray, params, cylinder->radius);
    if (hit_cap)
    {
        params->closest_so_far = params->temp_rec->t;
        t_vector local_normal = get_point(0, 1 * cap, 0);
        t_vector world_normal = apply_rotation_matrix(&local_normal, cylinder->inverse_rotation_matrix);
        record_cylinder_cap_hit(params->temp_rec->t, cylinder, normal_ray, params->temp_rec, &world_normal);
        return true;
    }
    else
        return false;
}

// Creates a plane that is parallel to the cap and goes through the center of the cap.
static t_plane    create_cap_plane(t_cylinder *cylinder, int cap)
{
    t_plane cap_plane;
    t_vector center_offset; 
	t_point cap_center;
    
	center_offset = multiply(&cylinder->axis, (cylinder->height * cap) / 2.0);
	cap_center = add_vectors(&cylinder->center, &center_offset);
	cap_plane.normal = cylinder->axis;
	cap_plane.color = cylinder->color;
	cap_plane.point = cap_center;
    return (cap_plane);
}

int find_cylinder_cap_hit(t_cylinder *cylinder, t_ray *ray, t_hit_params *params, t_ray *normal_ray)
{
	bool hit_top_cap;
	bool hit_bottom_cap;
	t_plane top_cap_plane;
    t_plane bottom_cap_plane;
    
    top_cap_plane = create_cap_plane(cylinder, TOP_CAP);
	bottom_cap_plane = create_cap_plane(cylinder, BOTTOM_CAP);
    hit_top_cap = hit_caps(&top_cap_plane, ray, params, cylinder, TOP_CAP, normal_ray);
    hit_bottom_cap = hit_caps(&bottom_cap_plane, ray, params, cylinder, BOTTOM_CAP, normal_ray);
    if (hit_bottom_cap || hit_top_cap)
        return (true);
    return (false);
}