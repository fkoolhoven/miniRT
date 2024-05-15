/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 16:55:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/15 19:21:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	store_light(t_data *data, char *input)
{
	char	**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(input, 1);
	if (store_xyz(items[0], &data->light.origin) || \
		store_xyz(items[2], &(data->light.color)))
		error("Light parameters are incorrect", 1);
	data->light.brightness = ft_atod(items[1]);
	frdp(items);
}

static void	store_camera(t_data *data, char *input)
{
	char	**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(input, 1);
	if (store_xyz(items[0], &data->camera.view_point) || \
		store_xyz(items[1], &data->camera.orientation))
		error("Camera parameters are incorrect", 1);
	data->camera.horizontal_fov = ft_atod(items[2]);
	frdp(items);
}

static void	store_ambient(t_data *data, char *input)
{
	t_vector	ambient;
	char		**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 2)
		error(input, 1);
	if (store_xyz(items[1], &(data->ambient.color)))
		error("Ambient light parameters are incorrect", 1);
	data->ambient.brightness = ft_atod(items[0]);
	ambient = multiply(&data->ambient.color, data->ambient.brightness);
	ambient = divide(&ambient, 255.0);
	data->ambient.ambient_light = ambient;
	frdp(items);
}

void	store_data(t_data *data, char *input)
{
	if (!ft_strncmp("A ", input, 2))
		store_ambient(data, input + 2);
	else if (!ft_strncmp("C ", input, 2))
		store_camera(data, input + 2);
	else if (!ft_strncmp("L ", input, 2))
		store_light(data, input + 2);
	else if (!ft_strncmp("sp ", input, 3))
		add_sphere(&(data->sphere), sphere_new(input + 3));
	else if (!ft_strncmp("pl ", input, 3))
		add_plane(&(data->plane), plane_new(input + 3));
	else if (!ft_strncmp("cy ", input, 3))
		add_cylinder(&(data->cylinder), cylinder_new(input + 3));
	else if (*input != '\n')
		printf("line: -> %s\twas ignored\n", input);
}
