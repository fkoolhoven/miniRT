/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:41:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/21 18:55:54 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	free_planes(t_plane *plane)
{
	t_plane	*next_plane;

	while (plane != NULL)
	{
		next_plane = plane->next;
		free(plane);
		plane = next_plane;
	}
}

static void	free_spheres(t_sphere *sphere)
{
	t_sphere	*next_sphere;

	while (sphere != NULL)
	{
		next_sphere = sphere->next;
		free(sphere);
		sphere = next_sphere;
	}
}

static void	free_cylinders(t_cylinder *cylinder)
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

static void	free_all_data(t_data *data)
{
	free_cylinders(data->cylinder);
	free_spheres(data->sphere);
	free_planes(data->plane);
	free(data->mlx_info);
}

bool	scene_is_valid(t_data *data)
{
	if (!data->camera.is_initialized)
		error("No camera", EXIT_FAILURE);
	if (!data->light.is_initialized)
		error("No light", EXIT_FAILURE);
	if (!data->ambient.is_initialized)
		error("No ambient light", EXIT_FAILURE);
	else if (data->window_width <= 0 || data->window_height <= 0)
		error("Invalid window size", EXIT_FAILURE);
	else if (data->plane == NULL && data->sphere == NULL
		&& data->cylinder == NULL)
		error("No objects", EXIT_FAILURE);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(&data, argv[1]);
	if (scene_is_valid(&data))
	{
		setup_mlx(&data);
		mlx_key_hook(data.mlx_info->mlx_ptr, key_press, &data);
		mlx_resize_hook(data.mlx_info->mlx_ptr, resize, &data);
		render_image(&data);
		mlx_loop(data.mlx_info->mlx_ptr);
		free_all_data(&data);
		exit(EXIT_SUCCESS);
	}
}
