/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:55:54 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 17:01:34 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	free_planes(t_plane *plane)
{
	t_plane	*next_plane;

	while (plane != NULL)
	{
		next_plane = plane->next;
		free(plane);
		plane = next_plane;
	}
}

void	free_spheres(t_sphere *sphere)
{
	t_sphere	*next_sphere;

	while (sphere != NULL)
	{
		next_sphere = sphere->next;
		free(sphere);
		sphere = next_sphere;
	}
}

void	free_cylinders(t_cylinder *cylinder)
{
	t_cylinder	*next_cylinder;

	while (cylinder != NULL)
	{
		next_cylinder = cylinder->next;
		free(cylinder->rotation);
		free(cylinder->inverse_rotation);
		free(cylinder);
		cylinder = next_cylinder;
	}
}

void	free_all_data(t_data *data)
{
	free_cylinders(data->cylinder);
	free_spheres(data->sphere);
	free_planes(data->plane);
	free(data->mlx_info);
}
