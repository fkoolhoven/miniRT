/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:23 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 16:12:50 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_diffuse_light(t_data *data, t_hit *rec)
{
	t_vector	light_normal;
	double		diffuse_intensity;
	t_vector	diffuse;
	t_vector	light_direction;
	double		distance;

	if (rec->in_shadow)
		return (get_point(0.0, 0.0, 0.0));
	light_direction = subtract_vectors(&data->light.origin, &rec->point);
	distance = length(&light_direction);
	light_normal = normalize(&light_direction);
	diffuse_intensity = dot(&rec->normal, &light_normal);
	diffuse_intensity = diffuse_intensity / (1.0 + 0.05 * distance);
	diffuse_intensity = fmax(diffuse_intensity, 0.0);
	diffuse_intensity = data->light.brightness * diffuse_intensity;
	diffuse = multiply(&data->light.color, diffuse_intensity);
	diffuse = divide(&diffuse, 255.0);
	return (diffuse);
}

static t_vector	get_all_light(t_data *data, t_hit *rec)
{
	t_vector	diffuse_light;
	t_vector	ambient_light;
	t_vector	all_light;


	diffuse_light = get_diffuse_light(data, rec);
	ambient_light = data->ambient.ambient_light;
	all_light = add_vectors(&diffuse_light, &ambient_light);

	if (all_light.x > 1.0)
		all_light.x = 1.0;
	if (all_light.y > 1.0)
		all_light.y = 1.0;
	if (all_light.z > 1.0)
		all_light.z = 1.0;
	return (all_light);
}

t_color	apply_shading(t_data *data, t_hit *light_rec, t_hit *shadow_rec)
{
	t_vector	all_light;
	t_color		object_color;
	t_color		final_color;

	if (light_rec->in_shadow && shadow_rec->object_type == PLANE)
		return (get_point(0.0, 0.0, 0.0));
	all_light = get_all_light(data, light_rec);
	object_color = light_rec->color;
	final_color = multiply_vectors(&object_color, &all_light);
	final_color = divide(&final_color, 255.0);
	return (final_color);
}
