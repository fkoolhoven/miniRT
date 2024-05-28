/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:41:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/28 18:14:33 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static bool	inside_sphere(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_sphere	*current_sphere;

	current_sphere = data->sphere;
	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params))
		{
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				return (true);
			}
		}
		current_sphere = current_sphere->next;
	}
	return (false);
}

static bool	inside_cylinder(t_data *data, t_ray *ray, t_hit_params *params)
{
	t_cylinder	*current_cylinder;

	current_cylinder = data->cylinder;
	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			if (dot(&params->rec->normal, &ray->direction) > 0)
			{
				return (true);
			}
		}
		current_cylinder = current_cylinder->next;
	}
	return (false);
}

static bool	light_is_inside_object(t_data *data)
{
	t_hit_params	params;
	t_ray			ray;
	t_hit			*rec;

	ray.origin = data->light.origin;
	ray.direction = get_point(1, 1, 1);
	rec = get_hit_record();
	params = get_hit_params(LIGHT_RAY, rec);
	if (inside_sphere(data, &ray, &params))
	{
		free(rec);
		return (true);
	}
	if (inside_cylinder(data, &ray, &params))
	{
		free(rec);
		return (true);
	}
	return (false);
}

static bool	scene_is_valid(t_data *data)
{
	if (!data->camera.is_initialized)
		error("No camera", EXIT_FAILURE);
	else if (!data->light.is_initialized)
		error("No light", EXIT_FAILURE);
	else if (!data->ambient.is_initialized)
		error("No ambient light", EXIT_FAILURE);
	else if (data->window_width <= 0 || data->window_height <= 0)
		error("Invalid window size", EXIT_FAILURE);
	else if (data->plane == NULL && data->sphere == NULL
		&& data->cylinder == NULL)
		error("No objects", EXIT_FAILURE);
	else if (light_is_inside_object(data))
		error("Light is inside object", EXIT_FAILURE);
	return (true);
}

static bool	extension_is_valid(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (false);
	if (ft_strncmp(file + len - 3, ".rt", 3) != 0)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	else if (!extension_is_valid(argv[1]))
		error("Incorrect file extenstion", EXIT_FAILURE);
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
