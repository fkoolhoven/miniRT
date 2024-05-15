/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/15 17:07:42 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	color_pixel(t_color *pixel_color, \
	t_viewport *viewport, mlx_image_t *image)
{
	unsigned int	rgba;

	rgba = 0;
	rgba |= ((int)(255.999 * pixel_color->x) & 0xFF) << 24;
	rgba |= ((int)(255.999 * pixel_color->y) & 0xFF) << 16;
	rgba |= ((int)(255.999 * pixel_color->z) & 0xFF) << 8;
	rgba |= (255 & 0xFF);
	mlx_put_pixel(image, viewport->pixel_x, viewport->pixel_y, rgba);
}

static bool	object_is_in_shadow(t_data *data, \
	t_hit *light_rec, t_hit *shadow_rec)
{
	t_vector		rounding_correction;
	t_ray			shadow_ray;
	double			distance_to_light;
	bool			in_shadow;
	t_hit_params	shadow_params;

	rounding_correction = multiply(&light_rec->normal, 0.0001);
	shadow_ray.origin = add_vectors(&light_rec->point, &rounding_correction);
	shadow_ray.direction = subtract_vectors(&data->light.origin, \
		&light_rec->point);
	distance_to_light = length(&shadow_ray.direction);
	shadow_ray.direction = normalize(&shadow_ray.direction);
	shadow_params = get_hit_params();
	shadow_params.closest_so_far = distance_to_light;
	in_shadow = hit_objects(data, &shadow_ray, &shadow_params, shadow_rec);
	return (in_shadow);
}

static t_color	get_pixel_color(t_data *data, t_ray ray, \
	t_hit *light_rec, t_hit *shadow_rec)
{
	bool			object_was_hit;
	t_hit_params	light_params;
	bool			inside_object;
	t_color			color;
	t_color			black;

	black = get_point(0, 0, 0);
	light_params = get_hit_params();
	object_was_hit = hit_objects(data, &ray, &light_params, light_rec);
	if (object_was_hit)
	{
		inside_object = dot(&light_rec->normal, &ray.direction) > 0;
		if (inside_object)
			return (black);
		light_rec->in_shadow = object_is_in_shadow(data, light_rec, shadow_rec);
		color = apply_shading(data, light_rec);
		return (color);
	}
	else
		return (black);
}

static void	free_render_data(t_hit *light_rec, t_hit *shadow_rec)
{
	free(light_rec);
	free(shadow_rec);
}

void	render_image(t_data *data)
{
	t_viewport		viewport;
	t_hit			*light_rec;
	t_hit			*shadow_rec;
	t_ray			light_ray;
	t_color			pixel_color;

	viewport = set_up_viewport(data);
	light_rec = get_hit_record();
	shadow_rec = get_hit_record();
	light_ray.origin = data->camera.view_point;
	viewport.pixel_y = 0;
	while (viewport.pixel_y < data->window_height)
	{
		viewport.pixel_x = 0;
		while (viewport.pixel_x < data->window_width)
		{
			set_ray_direction(&viewport, &light_ray, data);
			pixel_color = get_pixel_color(data, light_ray, \
				light_rec, shadow_rec);
			color_pixel(&pixel_color, &viewport, data->mlx_info->img_ptr);
			viewport.pixel_x++;
		}
		viewport.pixel_y++;
	}
	free_render_data(light_rec, shadow_rec);
}
