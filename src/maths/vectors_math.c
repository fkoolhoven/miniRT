/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_math.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:52:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/22 17:17:42 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	length(t_vector *v)
{
	return (sqrt(length_squared(v)));
}

t_vector	normalize(t_vector *v)
{
	return (divide(v, length(v)));
}

double	dot(const t_vector *u, const t_vector *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

double	length_squared(const t_vector *v)
{
	return (dot(v, v));
}

t_vector	cross(const t_vector *u, const t_vector *v)
{
	t_vector	cross;

	cross.x = u->y * v->z - u->z * v->y;
	cross.y = u->z * v->x - u->x * v->z;
	cross.z = u->x * v->y - u->y * v->x;
	return (cross);
}
