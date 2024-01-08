/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_double.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:08:21 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/08 15:15:07 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	divide(t_vector *v1, double d)
{
	v1->x /= d;
	v1->y /= d;
	v1->z /= d;
}

void	multiply(t_vector *v1, double d)
{
	v1->x *= d;
	v1->y *= d;
	v1->z *= d;
}

void	add(t_vector *v1, double d)
{
	v1->x += d;
	v1->y += d;
	v1->z += d;
}

void	subtract(t_vector *v1, double d)
{
	v1->x -= d;
	v1->y -= d;
	v1->z -= d;
}
