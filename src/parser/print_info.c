/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:50:22 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/06 16:33:18 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_spheres(t_sphere *sp)
{
	t_point	center;
	t_color	color;

	while (sp)
	{
		printf(BLUE BOLD"SPHERE\n"OFF);
		center = sp->center;
		color = sp->color;
		printf("center: %.2f,%.2f,%.2f\n", center.x, center.y, center.z);
		printf("radius: %.2f\n", sp->radius * 2);
		printf("color: %.2f,%.2f,%.2f\n", color.x, color.y, color.z);
		sp = sp->next;
	}
}

static void	print_cylinders(t_cylinder *cy)
{
	t_point		center;
	t_color		color;
	t_vector	axis;

	while (cy)
	{
		printf(RED BOLD"CYLINDER\n"OFF);
		center = cy->center;
		color = cy->color;
		axis = cy->axis;
		printf("center: %.2f,%.2f,%.2f\n", center.x, center.y, center.z);
		printf("axis: %.2f,%.2f,%.2f\n", axis.x, axis.y, axis.z);
		printf("radius: %.2f\n", cy->radius);
		printf("height: %.2f\n", cy->height);
		printf("color: %.2f,%.2f,%.2f\n", color.x, color.y, color.z);
		cy = cy->next;
	}
}

static void	print_planes(t_plane *pl)
{
	t_point		point;
	t_color		color;
	t_vector	normal;

	while (pl)
	{
		printf(PURPLE BOLD"PLANE\n"OFF);
		point = pl->point;
		color = pl->color;
		normal = pl->normal;
		printf("point: %.2f,%.2f,%.2f\n", point.x, point.y, point.z);
		printf("normal: %.2f,%.2f,%.2f\n", normal.x, normal.y, normal.z);
		printf("color: %.2f,%.2f,%.2f\n", color.x, color.y, color.z);
		pl = pl->next;
	}
}

static void	print_acl(t_ambient_light ambient, t_camera camera, t_light light)
{
	t_color	color;
	t_point	point;

	color = ambient.color;
	printf(GREEN BOLD"AMBIENT\n"OFF);
	printf("brightness: %.2f\n", ambient.ratio);
	printf("color: %.2f, %.2f, %.2f\n", color.x, color.y, color.z);
	printf(BOLD"CAMERA\n"OFF);
	point = camera.view_point;
	printf("view point: %.2f, %.2f, %.2f\n", point.x, point.y, point.z);
	point = camera.orientation;
	printf("orientation: %.2f, %.2f, %.2f\n", point.x, point.y, point.z);
	printf("horizontal fov: %.2f\n", camera.horizontal_fov);
	printf(YELLOW"LIGHT\n"OFF);
	point = light.point;
	printf("point: %.2f, %.2f, %.2f\n", point.x, point.y, point.z);
	printf("brightness: %.2f\n", light.brightness);
	color = light.color;
	printf("color: %.2f, %.2f, %.2f\n", color.x, color.y, color.z);
}

void	print_info(t_data *data)
{
	print_acl(data->ambient, data->camera, data->light);
	print_spheres(data->sphere);
	print_planes(data->plane);
	print_cylinders(data->cylinder);
}
