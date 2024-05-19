/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/19 15:48:38 by felicia          ###   ########.fr       */
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

static bool	no_light_can_reach(t_hit *light_rec, t_data *data, t_ray ray) // check for cylinder caps?
{
	bool		wrong_side_of_plane;
	bool		inside_object;
	t_vector	camera_to_plane;
	t_vector	light_to_plane;
	t_vector	inverse_normal;
	double		dot_product;

	inside_object = false;
	wrong_side_of_plane = false;
	if (light_rec->object_type != PLANE)
		inside_object = dot(&light_rec->normal, &ray.direction) > 0;
	else if (light_rec->object_type == PLANE)
	{
		camera_to_plane = subtract_vectors(&light_rec->point, &data->camera.view_point);
		light_to_plane = subtract_vectors(&light_rec->point, &data->light.origin);
		dot_product = dot(&light_to_plane, &light_rec->normal);
		if (dot_product < 0) 
			wrong_side_of_plane = dot(&light_rec->normal, &camera_to_plane) > 0;
		else 
		{
			inverse_normal = multiply(&light_rec->normal, -1);
			wrong_side_of_plane = dot(&inverse_normal, &camera_to_plane) > 0;
		}
	}
	if (inside_object || wrong_side_of_plane)
		return (true);
	return (false);
}

static t_color	get_pixel_color(t_data *data, t_ray ray, \
	t_hit *light_rec, t_hit *shadow_rec)
{
	bool			object_was_hit;
	t_hit_params	light_params;
	bool			inside_object;
	t_color			color;
	t_color			black;

	inside_object = false;
	black = get_point(0, 0, 0);
	light_params = get_hit_params(LIGHT_RAY);
	object_was_hit = hit_objects(data, &ray, &light_params, light_rec);

	if (object_was_hit)
	{
		if (no_light_can_reach(light_rec, data, ray))
			return (black);
		check_if_shadow(data, light_rec, shadow_rec);
		color = apply_shading(data, light_rec, shadow_rec);
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
