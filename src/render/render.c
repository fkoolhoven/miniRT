/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/06/01 18:06:52 by fkoolhov         ###   ########.fr       */
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

static void	render_image_black(t_data *data, t_viewport *viewport)
{
	t_color	black;

	black = get_point(0, 0, 0);
	viewport->pixel_y = 0;
	while (viewport->pixel_y < data->window_height)
	{
		viewport->pixel_x = 0;
		while (viewport->pixel_x < data->window_width)
		{
			color_pixel(&black, viewport, data->mlx_info->img_ptr);
			viewport->pixel_x++;
		}
		viewport->pixel_y++;
	}
}

static t_color	get_pixel_color(t_data *data, t_ray ray, t_viewport *viewport)
{
	bool			object_was_hit;
	t_hit_params	light_params;
	bool			inside_object;
	t_color			color;
	t_color			black;

	inside_object = false;
	black = get_point(0, 0, 0);
	light_params = get_hit_params(LIGHT_RAY, data->light_rec);
	object_was_hit = hit_objects(data, &ray, &light_params);
	if (light_params.inside_object)
		render_image_black(data, viewport);
	else if (object_was_hit)
	{
		color = apply_shading(data, data->light_rec, data->shadow_rec);
		return (color);
	}
	return (black);
}

static void	free_render_data(t_data *data)
{
	free(data->light_rec);
	free(data->shadow_rec);
}

void	render_image(t_data *data)
{
	t_viewport		viewport;
	t_ray			light_ray;
	t_color			pixel_color;

	viewport = set_up_viewport(data);
	data->light_rec = get_hit_record();
	data->shadow_rec = get_hit_record();
	light_ray.origin = data->camera.view_point;
	viewport.pixel_y = 0;
	while (viewport.pixel_y < data->window_height)
	{
		viewport.pixel_x = 0;
		while (viewport.pixel_x < data->window_width)
		{
			set_ray_direction(&viewport, &light_ray, data);
			pixel_color = get_pixel_color(data, light_ray, &viewport);
			if (viewport.pixel_x == data->window_width)
				break ;
			color_pixel(&pixel_color, &viewport, data->mlx_info->img_ptr);
			viewport.pixel_x++;
		}
		viewport.pixel_y++;
	}
	free_render_data(data);
}
