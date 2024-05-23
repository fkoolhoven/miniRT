/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:45 by felicia           #+#    #+#             */
/*   Updated: 2024/05/23 21:26:53 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

typedef struct s_point
{
	double	x;
	double	y;
	double	z;
}	t_point;

typedef t_point	t_vector;
typedef t_point	t_color;

typedef struct s_viewport
{
	t_vector	upper_left_corner;
	t_vector	horizontal_offset;
	t_vector	vertical_offset;
	t_vector	horizontal;
	t_vector	vertical;
	double		half_height;
	double		half_width;
	int			pixel_x;
	int			pixel_y;
}	t_viewport;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_hit
{
	int			object_type;
	t_point		point;
	t_vector	normal;
	double		t;
	t_color		color;
	bool		in_shadow;
}	t_hit;

typedef struct s_camera
{
	bool		is_initialized;
	t_point		view_point;
	t_vector	orientation;
	t_vector	inverse_orientation;
	double		horizontal_fov;
}	t_camera;

typedef struct s_ambient_light
{
	bool		is_initialized;
	double		brightness;
	t_color		color;
	t_vector	ambient_light;
}	t_ambient_light;

typedef struct s_light
{
	bool		is_initialized;
	t_point		origin;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_plane
{
	t_point			point;
	t_vector		normal;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	t_point			center;
	double			radius;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_sphere_params
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
}	t_sphere_params;

typedef struct s_matrix
{
	double	m[3][3];
}	t_matrix;

typedef struct s_cylinder
{
	t_point				center;
	t_vector			axis;
	double				radius;
	double				height;
	t_color				color;
	t_matrix			*rotation;
	t_matrix			*inverse_rotation;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_cyl_params
{
	double		a;
	double		b;
	double		c;
	double		discriminant;
	t_cylinder	rotated_cylinder;
	t_ray		normal_ray;
	t_ray		rotated_ray;
	t_point		local_normal;
	t_point		world_normal;
}	t_cyl_params;

typedef struct s_mlx_info
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*img_ptr;
}	t_mlx_info;

typedef struct s_data
{
	t_camera		camera;
	t_light			light;
	t_ambient_light	ambient;

	t_plane			*plane;
	t_cylinder		*cylinder;
	t_sphere		*sphere;

	int32_t			window_height;
	int32_t			window_width;

	t_mlx_info		*mlx_info;
}	t_data;

typedef struct s_hit_params
{
	t_hit	*rec;
	double	ray_tmin;
	double	closest_so_far;
	bool	hit_anything;
	int		ray_type;
}	t_hit_params;

#endif