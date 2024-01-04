/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:02:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/04 14:13:37 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_color
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
}	t_color;

typedef struct s_ambient_light
{
	double		ratio;
	t_color		color;
}	t_ambient_light;

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef struct s_camera
{
	t_point		view_point;
	t_point		orientation;
	double		horizontal_field_of_view;
}	t_camera;

typedef struct s_light
{
	t_point		point;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_plane
{
	t_point	center;
	t_point	axis;
	t_color	color;
}	t_plane;

typedef struct s_sphere
{
	t_point	center;
	double	diameter;
	t_color	color;
}	t_sphere;

typedef struct s_cylinder
{
	t_point	center;
	t_point	axis;
	double	diameter;
	double	height;
	t_color	color;
}	t_cylinder;
