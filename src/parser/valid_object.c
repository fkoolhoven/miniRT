/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:52:26 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 16:54:56 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	plane_parameters_are_valid(t_plane plane)
{
	if (plane.normal.x < -1 || plane.normal.x > 1 || \
		plane.normal.y < -1 || plane.normal.y > 1 || \
		plane.normal.z < -1 || plane.normal.z > 1)
		return (false);
	else if (plane.color.x < 0 || plane.color.x > 255 || \
		plane.color.y < 0 || plane.color.y > 255 || \
		plane.color.z < 0 || plane.color.z > 255)
		return (false);
	else
		return (true);
}

bool	sphere_parameters_are_valid(t_sphere sphere)
{
	if (sphere.radius <= 0)
		return (false);
	else if (sphere.color.x < 0 || sphere.color.x > 255 || \
		sphere.color.y < 0 || sphere.color.y > 255 || \
		sphere.color.z < 0 || sphere.color.z > 255)
		return (false);
	else
		return (true);
}

bool	cylinder_parameters_are_valid(t_cylinder cylinders)
{
	if (cylinders.radius <= 0 || cylinders.height <= 0)
		return (false);
	else if (cylinders.color.x < 0 || cylinders.color.x > 255 || \
		cylinders.color.y < 0 || cylinders.color.y > 255 || \
		cylinders.color.z < 0 || cylinders.color.z > 255)
		return (false);
	else if (cylinders.axis.x < -1 || cylinders.axis.x > 1 || \
		cylinders.axis.y < -1 || cylinders.axis.y > 1 || \
		cylinders.axis.z < -1 || cylinders.axis.z > 1)
		return (false);
	else
		return (true);
}
