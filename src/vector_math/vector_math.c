/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:52:38 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 13:14:18 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	length(t_vector *v)
{
	return (sqrt(dot(v, v)));
}

t_vector	normalize(t_vector *v)
{
	return (divide(v, length(v)));
}

double	dot(const t_vector *u, const t_vector *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

t_vector	cross(const t_vector *u, const t_vector *v)
{
	t_vector	cross;

	cross.x = u->y * v->z - u->z * v->y;
	cross.y = u->z * v->x - u->x * v->z;
	cross.z = u->x * v->y - u->y * v->x;
	return (cross);
}
