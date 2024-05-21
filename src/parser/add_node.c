/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/21 18:37:39 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	no_light_or_camera(t_data *data)
{
	if (!data->light.is_initialized)
		return (true);
	else if (!data->camera.is_initialized)
		return (true);
	else if (!data->ambient.is_initialized)
		return (true);
	return (false);
}

void	add_plane(t_plane **head, t_plane *new, t_data *data)
{
	t_plane	*tmp;

	if (no_light_or_camera(data))
		error("No light, camera or ambient light", EXIT_FAILURE);
	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_sphere(t_sphere **head, t_sphere *new, t_data *data)
{
	t_sphere	*tmp;

	if (no_light_or_camera(data))
		error("No light, camera or ambient light", EXIT_FAILURE);
	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_cylinder(t_cylinder **head, t_cylinder *new, t_data *data)
{
	t_cylinder	*tmp;

	if (no_light_or_camera(data))
		error("No light, camera or ambient light", EXIT_FAILURE);
	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
