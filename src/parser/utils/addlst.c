/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_lists.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:09:23 by cvan-sch          #+#    #+#             */
/*   Updated: 2024/01/08 15:20:39 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	addplane(t_plane **head, t_plane *new)
{
	t_plane	*tmp;

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

void	addsphere(t_sphere **head, t_sphere *new)
{
	t_sphere	*tmp;

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

void	addcylinder(t_cylinder **head, t_cylinder *new)
{
	t_cylinder	*tmp;

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