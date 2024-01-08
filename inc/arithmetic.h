/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arithmetic.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 15:13:33 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/08 15:18:00 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARITHMETIC_H
# define ARITHMETIC_H

// vector_vector.c
void	vector_divide(t_vector *v1, t_vector *v2, t_vector *new);
void	vector_multiply(t_vector *v1, t_vector *v2, t_vector *new);
void	vector_add(t_vector *v1, t_vector *v2, t_vector *new);
void	vector_subtract(t_vector *v1, t_vector *v2, t_vector *new);

// vector_double.c
void	divide(t_vector *v1, double d);
void	multiply(t_vector *v1, double d);
void	add(t_vector *v1, double d);
void	subtract(t_vector *v1, double d);

#endif