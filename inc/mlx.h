/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 12:44:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 17:32:38 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_H
# define MLX_H

// setup.c
void	setup_mlx(t_data *data);

// hooks.c
void	key_press(mlx_key_data_t key_data, void *param);

#endif