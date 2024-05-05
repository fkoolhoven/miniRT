/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:17 by felicia           #+#    #+#             */
/*   Updated: 2024/05/06 00:03:29 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

// get_objects.c
t_hit_record	*get_hit_record(void);
t_point			get_point(double x, double y, double z);
t_hit_params	*get_hit_params();

// render.c
void			render_image(t_data *data);

// viewport.c
t_viewport		set_up_viewport(t_camera *camera, int32_t image_width, int32_t image_height);

// shading.c
t_color			apply_shading(t_data *data, t_hit_record *rec, bool in_shadow);

#endif