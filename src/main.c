/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:41:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/07 13:24:08 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static bool	hit_disk(t_plane *plane, t_ray *ray, t_hit_params *params, t_cylinder *cylinder, int cap, t_ray *normal_ray);
// // plane
// // ray
// // params
// // cylinder
// // cap
// // normal_ray

// static bool	find_cylinder_tube_hit(t_cylinder *rotated_cylinder, t_ray *rotated_ray, t_cylinder *cylinder, t_ray *ray, t_hit_params *params);
// // rotated_cylinder
// // rotated_ray
// // cylinder
// // ray
// // params

// void			record_cylinder_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vector *normal);
// // t
// // cylinder
// // ray
// // rec
// // normal


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

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(&data, argv[1]);
	setup_mlx(&data);
	mlx_key_hook(data.mlx_info->mlx_ptr, key_press, &data);
	mlx_resize_hook(data.mlx_info->mlx_ptr, resize, &data);
	render_image(&data);
	mlx_loop(data.mlx_info->mlx_ptr);
	free_all_data(&data);
	exit(EXIT_SUCCESS);
}
