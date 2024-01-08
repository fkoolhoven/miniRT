/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:55:39 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/08 15:19:19 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vector_divide(t_vector *v1, t_vector *v2, t_vector *new)
{
	new->x = v1->x / v2->x;
	new->y = v1->y / v2->y;
	new->z = v1->z / v2->z;
}

void	vector_multiply(t_vector *v1, t_vector *v2, t_vector *new)
{
	new->x = v1->x * v2->x;
	new->y = v1->y * v2->y;
	new->z = v1->z * v2->z;
}

void	vector_add(t_vector *v1, t_vector *v2, t_vector *new)
{
	new->x = v1->x + v2->x;
	new->y = v1->y + v2->y;
	new->z = v1->z + v2->z;
}

void	vector_subtract(t_vector *v1, t_vector *v2, t_vector *new)
{
	new->x = v1->x - v2->x;
	new->y = v1->y - v2->y;
	new->z = v1->z - v2->z;
}
