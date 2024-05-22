/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_ALC.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:54:12 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 17:01:48 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ambient_parameters_are_valid(t_ambient_light ambient)
{
	if (ambient.brightness < 0 || ambient.brightness > 1)
		return (false);
	else if (ambient.color.x < 0 || ambient.color.x > 255 || \
		ambient.color.y < 0 || ambient.color.y > 255 || \
		ambient.color.z < 0 || ambient.color.z > 255)
		return (false);
	else
		return (true);
}

bool	camera_parameters_are_valid(t_camera camera)
{
	if (camera.horizontal_fov <= 0 || camera.horizontal_fov > 180)
		return (false);
	else if (camera.orientation.x < -1 || camera.orientation.x > 1 || \
		camera.orientation.y < -1 || camera.orientation.y > 1 || \
		camera.orientation.z < -1 || camera.orientation.z > 1)
		return (false);
	else
		return (true);
}

bool	light_parameters_are_valid(t_light light)
{
	if (light.brightness < 0 || light.brightness > 1)
		return (false);
	else if (light.color.x < 0 || light.color.x > 255 || \
		light.color.y < 0 || light.color.y > 255 || \
		light.color.z < 0 || light.color.z > 255)
		return (false);
	else
		return (true);
}
