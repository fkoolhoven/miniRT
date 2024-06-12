/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shading.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:23 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/12 11:14:54 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vector	get_diffuse_light(bool in_shadow, t_data *data, t_hit *rec)
{
	t_vector	light_normal;
	double		diffuse_intensity;
	t_vector	diffuse;
	t_vector	light_direction;
	double		distance;

	if (in_shadow)
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

static t_vector	get_all_light(bool in_shadow, t_data *data, t_hit *rec)
{
	t_vector	diffuse_light;
	t_vector	ambient_light;
	t_vector	all_light;

	diffuse_light = get_diffuse_light(in_shadow, data, rec);
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

static bool	check_if_shadow(t_data *data, t_hit *light_rec, t_hit *shadow_rec)
{
	t_vector		rounding_correction;
	t_ray			shadow_ray;
	double			distance_to_light;
	t_hit_params	shadow_params;
	bool			in_shadow;

	rounding_correction = multiply(&light_rec->normal, ROUNDING_CORRECTION);
	shadow_ray.origin = add_vectors(&light_rec->point, &rounding_correction);
	shadow_ray.direction = subtract_vectors(&data->light.origin, &light_rec->point);
	distance_to_light = length(&shadow_ray.direction);
	shadow_ray.direction = normalize(&shadow_ray.direction);
	shadow_params = get_hit_params(SHADOW_RAY, shadow_rec);
	shadow_params.closest_so_far = distance_to_light;
	in_shadow = hit_objects(data, &shadow_ray, &shadow_params);
	return (in_shadow);
}

t_color	apply_shading(t_data *data, t_hit *light_rec, t_hit *shadow_rec)
{
	t_vector	all_light;
	t_color		object_color;
	t_color		final_color;
	bool		in_shadow;

	in_shadow = check_if_shadow(data, light_rec, shadow_rec);
	if (in_shadow && shadow_rec->object_type == PLANE)
		return (get_point(0, 0, 0));
	all_light = get_all_light(in_shadow, data, light_rec);
	object_color = light_rec->color;
	final_color = multiply_vectors(&object_color, &all_light);
	final_color = divide(&final_color, 255.0);
	return (final_color);
}
