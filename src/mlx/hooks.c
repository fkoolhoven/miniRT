/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:43:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 17:34:38 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	camera_field_of_view_keys(t_data *data)
{
	double	*fov;
	mlx_t	*mlx_ptr;

	fov = &data->camera.horizontal_fov;
	mlx_ptr = data->mlx_info->mlx_ptr;
	if (mlx_is_key_down(mlx_ptr, MLX_KEY_LEFT_BRACKET) && *fov > 0)
		*fov -= 10;
	else if (mlx_is_key_down(mlx_ptr, MLX_KEY_RIGHT_BRACKET) && *fov < 180)
		*fov += 10;
	else
		return ;
	printf("fov: %f\n", *fov);
	render_image(data);
}

static void	camera_orientation_keys(t_data *data)
{
	t_vector	*orientation;
	mlx_t		*mlx_ptr;

	orientation = &data->camera.orientation;
	mlx_ptr = data->mlx_info->mlx_ptr;
	if (mlx_is_key_down(mlx_ptr, MLX_KEY_A) && orientation->x >= -0.9)
		orientation->x -= 0.1;
	else if (mlx_is_key_down(mlx_ptr, MLX_KEY_D) && orientation->x <= 0.9)
		orientation->x += 0.1;
	else if (mlx_is_key_down(mlx_ptr, MLX_KEY_W) && orientation->y <= 0.9)
		orientation->y += 0.1;
	else if (mlx_is_key_down(mlx_ptr, MLX_KEY_S) && orientation->y >= -0.9)
		orientation->y -= 0.1;
	else if (mlx_is_key_down(mlx_ptr, MLX_KEY_R) && orientation->z >= -0.9)
		orientation->z -= 0.1;
	else if (mlx_is_key_down(mlx_ptr, MLX_KEY_F) && orientation->z <= 0.9)
		orientation->z += 0.1;
	else
		return ;
	printf("orientation: %f %f %f\n", \
		orientation->x, orientation->y, orientation->z);
	render_image(data);
}

static void	camera_view_point_keys(t_data *data)
{
	t_point	*view_point;

	view_point = &data->camera.view_point;
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_RIGHT))
		view_point->x += 0.5;
	else if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_LEFT))
		view_point->x -= 0.5;
	else if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_UP))
		view_point->y += 0.5;
	else if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_DOWN))
		view_point->y -= 0.5;
	else if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_P))
		view_point->z += 0.5;
	else if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_L))
		view_point->z -= 0.5;
	else
		return ;
	printf("view point: %f %f %f\n", \
		view_point->x, view_point->y, view_point->z);
	render_image(data);
}

void	key_press(mlx_key_data_t key_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (key_data.key == ESCAPE)
		exit(EXIT_SUCCESS);
	camera_view_point_keys(data);
	camera_orientation_keys(data);
	camera_field_of_view_keys(data);
}
