/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:41:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 16:57:13 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	scene_is_valid(t_data *data)
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
