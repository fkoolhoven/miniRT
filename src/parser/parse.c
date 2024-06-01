/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:34 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 17:34:56 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	initialize_data_struct(t_data *data)
{
	data->cylinder = NULL;
	data->plane = NULL;
	data->sphere = NULL;
	data->window_width = WINDOW_WIDTH;
	data->window_height = WINDOW_HEIGHT;
	data->camera.is_initialized = false;
	data->light.is_initialized = false;
	data->ambient.is_initialized = false;
}

static void	get_true_plane_normals(t_plane *plane, t_data *data)
{
	t_vector	plane_to_light;
	double		dot_product;

	while (plane)
	{
		plane_to_light = subtract_vectors(&plane->point, &data->light.origin);
		dot_product = dot(&plane_to_light, &plane->normal);
		if (dot_product >= 0)
			plane->normal = multiply(&plane->normal, -1);
		plane = plane->next;
	}
}

static bool	no_light_or_camera(t_data *data)
{
	if (!data->light.is_initialized)
		return (true);
	else if (!data->camera.is_initialized)
		return (true);
	else if (!data->ambient.is_initialized)
		return (true);
	return (false);
}

void	parse(t_data *data, char *file)
{
	int		fd;
	int		i;
	char	*input;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error(strerror(errno), errno);
	initialize_data_struct(data);
	while (true)
	{
		i = 0;
		input = get_next_line(fd);
		if (!input)
			break ;
		while (input[i] && ft_iswhitespace(input[i]) && input[i] != '\n')
			i++;
		if (input[i] != '#')
			store_data(data, input + i);
		free(input);
	}
	if (no_light_or_camera(data))
		error("No light or camera in the scene", EXIT_FAILURE);
	get_true_plane_normals(data->plane, data);
	close(fd);
	print_info(data);
}
