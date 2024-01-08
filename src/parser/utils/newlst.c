/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:22:35 by cvan-sch          #+#    #+#             */
/*   Updated: 2024/01/08 15:58:48 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_plane	*plane_new(char *data)
{
	t_plane	*new;

	new = malloc(sizeof(t_plane));
	if (!new)
		error("Malloc failure", errno);
	// do something with data
	(void)data;
	new->next = NULL;
	return (new);
}

t_sphere	*sphere_new(char *data)
{
	t_sphere	*new;

	new = malloc(sizeof(t_sphere));
	if (!new)
		error("Malloc failure", errno);
	// do something with data
	(void)data;
	new->next = NULL;
	return (new);
}

t_cylinder	*cylinder_new(char *data)
{
	t_cylinder	*new;

	new = malloc(sizeof(t_cylinder));
	if (!new)
		error("Malloc failure", errno);
	// do something with data
	(void)data;
	new->next = NULL;
	return (new);
}
