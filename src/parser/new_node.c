/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:43 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 16:52:38 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_true_plane_normal(t_plane *new, t_data *data)
{
	t_vector	plane_to_light;
	double		dot_product;

	plane_to_light = subtract_vectors(&new->point, &data->light.origin);
	dot_product = dot(&plane_to_light, &new->normal);
	if (dot_product >= 0)
		new->normal = multiply(&new->normal, -1);
}

t_plane	*plane_new(char *data, t_data *data_struct)
{
	t_plane	*new;
	char	**items;

	items = ft_split(data, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(data, 1);
	new = malloc(sizeof(t_plane));
	if (!new)
		error("Malloc failure", errno);
	if (store_xyz(items[0], &new->point) || \
		store_xyz(items[1], &new->normal) || \
		store_xyz(items[2], &(new->color)))
		error("Plane parameters are incorrect", EXIT_FAILURE);
	if (!plane_parameters_are_valid(*new))
		error("Plane parameters are incorrect", EXIT_FAILURE);
	get_true_plane_normal(new, data_struct);
	new->next = NULL;
	frdp(items);
	return (new);
}

t_sphere	*sphere_new(char *data)
{
	t_sphere	*new;
	char		**items;

	items = ft_split(data, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(data, 1);
	new = malloc(sizeof(t_sphere));
	if (!new)
		error("Malloc failure", errno);
	if (store_xyz(items[0], &new->center) || \
		store_xyz(items[2], &(new->color)))
		error("Sphere parameters are incorrect", EXIT_FAILURE);
	new->radius = ft_atod(items[1]) / 2;
	if (!sphere_parameters_are_valid(*new))
		error("Sphere parameters are incorrect", EXIT_FAILURE);
	new->next = NULL;
	frdp(items);
	return (new);
}

t_cylinder	*cylinder_new(char *data)
{
	t_cylinder	*new;
	char		**items;

	items = ft_split(data, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 5)
		error(data, 1);
	new = malloc(sizeof(t_cylinder));
	if (!new)
		error("Malloc failure", errno);
	if (store_xyz(items[0], &new->center) || \
		store_xyz(items[1], &new->axis) || \
		store_xyz(items[4], &(new->color)))
		error("Cylinder parameters are incorrect", EXIT_FAILURE);
	new->radius = ft_atod(items[2]) / 2;
	new->height = ft_atod(items[3]);
	if (!cylinder_parameters_are_valid(*new))
		error("Cylinder parameters are incorrect", EXIT_FAILURE);
	new->rotation = calculate_rotation_matrix(new->axis);
	new->inverse_rotation = transpose_matrix(new->rotation);
	new->next = NULL;
	frdp(items);
	return (new);
}
