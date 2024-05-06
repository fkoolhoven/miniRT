/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:41:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 16:10:25 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// static bool	hit_disk(t_plane *plane, t_ray *ray, t_hit_params *params, t_cylinder *cylinder, int cap, t_ray *normal_ray);
// static bool	find_cylinder_tube_hit(t_cylinder *rotated_cylinder, t_ray *rotated_ray, t_cylinder *cylinder, t_ray *ray, t_hit_params *params);
// void		record_cylinder_hit(double t, t_cylinder *cylinder, t_ray *ray, t_hit_record *rec, t_vector *normal);

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
	exit(EXIT_SUCCESS);
}
