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
	t_vector	horizontal_direction;
	t_vector	vertical_direction;
	double		half_height;
	double		half_width;
}	t_viewport;

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_hit_record
{
	t_point		point;
	t_vector	normal;
	double		t;
	t_color		color;
}	t_hit_record;

typedef struct s_camera
{
	t_point		view_point;
	t_vector	orientation;
	double		horizontal_fov;
}	t_camera;

typedef struct s_ambient_light
{
	double		ratio;
	t_color		color;
	t_vector	ambient_light;
}	t_ambient_light;

typedef struct s_light
{
	t_point		point;
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

typedef struct s_cylinder
{
	t_point				center;
	t_vector			axis;
	double				radius;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}	t_cylinder;

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

	t_mlx_info		*mlx_info;
}	t_data;

typedef struct s_hit_params
{
	t_hit_record	*temp_rec;
	double			ray_tmin;
	double			closest_so_far;
	bool			hit_anything;
}	t_hit_params;

#endif