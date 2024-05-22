/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_arithmetic.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:04 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 11:55:05 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	divide_vectors(const t_vector *v1, const t_vector *v2)
{
	t_vector	new;

	new.x = v1->x / v2->x;
	new.y = v1->y / v2->y;
	new.z = v1->z / v2->z;
	return (new);
}

t_vector	multiply_vectors(const t_vector *v1, const t_vector *v2)
{
	t_vector	new;

	new.x = v1->x * v2->x;
	new.y = v1->y * v2->y;
	new.z = v1->z * v2->z;
	return (new);
}

t_vector	add_vectors(const t_vector *v1, const t_vector *v2)
{
	t_vector	new;

	new.x = v1->x + v2->x;
	new.y = v1->y + v2->y;
	new.z = v1->z + v2->z;
	return (new);
}

t_vector	subtract_vectors(const t_vector *v1, const t_vector *v2)
{
	t_vector	new;

	new.x = v1->x - v2->x;
	new.y = v1->y - v2->y;
	new.z = v1->z - v2->z;
	return (new);
}
