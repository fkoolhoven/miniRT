/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:43 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 13:01:21 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*plane_new(char *data)
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
		error("Plane parameters are incorrect", 1);
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
		error("Sphere parameters are incorrect", 1);
	new->radius = ft_atod(items[1]) / 2;
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
		error("Cylinder parameters are incorrect", 1);
	new->radius = ft_atod(items[2]) / 2;
	new->height = ft_atod(items[3]);
	new->rotation = calculate_rotation_matrix(new->axis);
	new->inverse_rotation = transpose_matrix(new->rotation);
	new->next = NULL;
	frdp(items);
	return (new);
}