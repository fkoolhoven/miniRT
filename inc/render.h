/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:17 by felicia           #+#    #+#             */
/*   Updated: 2024/05/16 19:24:29 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

// get_objects.c
t_hit			*get_hit_record(void);
t_point			get_point(double x, double y, double z);
t_hit_params	get_hit_params(int ray_type);

// render.c
void			render_image(t_data *data);

// ray_direction.c
void			set_ray_direction(t_viewport *view, t_ray *ray, t_data *data);

// viewport.c
t_viewport		set_up_viewport(t_data *data);

// shading.c
t_color	        apply_shading(t_data *data, t_hit *light_rec, t_hit *shadow_rec);

#endif