/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_arithmetic.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:08 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 11:54:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	divide(const t_vector *v1, double d)
{
	t_vector	new;

	new.x = v1->x / d;
	new.y = v1->y / d;
	new.z = v1->z / d;
	return (new);
}

t_vector	multiply(const t_vector *v1, double d)
{
	t_vector	new;

	new.x = v1->x * d;
	new.y = v1->y * d;
	new.z = v1->z * d;
	return (new);
}

t_vector	add(const t_vector *v1, double d)
{
	t_vector	new;

	new.x = v1->x + d;
	new.y = v1->y + d;
	new.z = v1->z + d;
	return (new);
}

t_vector	subtract(const t_vector *v1, double d)
{
	t_vector	new;

	new.x = v1->x - d;
	new.y = v1->y - d;
	new.z = v1->z - d;
	return (new);
}
