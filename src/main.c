/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:41:58 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 17:35:45 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		mlx_set_setting(MLX_STRETCH_IMAGE, true);
		mlx_key_hook(data.mlx_info->mlx_ptr, key_press, &data);
		render_image(&data);
		mlx_loop(data.mlx_info->mlx_ptr);
		mlx_delete_image(data.mlx_info->mlx_ptr, data.mlx_info->img_ptr);
		mlx_terminate(data.mlx_info->mlx_ptr);
		free_all_data(&data);
		exit(EXIT_SUCCESS);
	}
}
