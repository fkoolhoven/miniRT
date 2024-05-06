/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:44:04 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 12:44:16 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	setup_mlx(t_data *data)
{
	t_mlx_info	*mlx_info;
	mlx_t		*mlx_ptr;
	mlx_image_t	*img_ptr;

	mlx_info = malloc(sizeof(t_mlx_info));
	if (mlx_info == NULL)
		error("malloc failure in setup_mlx()", EXIT_FAILURE);
	mlx_ptr = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT", true);
	if (mlx_ptr == NULL)
		error("malloc failure in setup_mlx()", EXIT_FAILURE);
	img_ptr = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img_ptr == NULL)
		error("malloc failure in setup_mlx()", EXIT_FAILURE);
	mlx_image_to_window(mlx_ptr, img_ptr, 0, 0);
	mlx_info->mlx_ptr = mlx_ptr;
	mlx_info->img_ptr = img_ptr;
	data->mlx_info = mlx_info;
}
