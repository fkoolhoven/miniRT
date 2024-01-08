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

typedef struct s_ray
{
	const t_point	origin; // = camera view point
	t_vector		direction; // = a point on viewport
}	t_ray;

typedef struct s_camera
{
	const t_point	view_point; // 0, 0, -1
	const t_vector	orientation; // 0, 0, 0
	const double	horizontal_field_of_view; // 90
}	t_camera;

typedef struct s_ambient_light
{
	double		ratio;
	t_color		color;
}	t_ambient_light;

typedef struct s_light
{
	t_point		point;
	double		brightness;
	t_color		color;
}	t_light;

typedef struct s_plane
{
	t_point			center;
	t_point			axis;
	t_color			color;
	struct s_plane	*next;
}	t_plane;

typedef struct s_sphere
{
	t_point			center;
	double			diameter;
	t_color			color;
	struct s_sphere	*next;
}	t_sphere;

typedef struct s_cylinder
{
	t_point				center;
	t_point				axis;
	double				diameter;
	double				height;
	t_color				color;
	struct s_cylinder	*next;
}	t_cylinder;

typedef struct s_data
{
	t_camera		camera;
	t_light			light;
	t_ambient_light	ambient;

	t_plane		*plane;
	t_cylinder	*cylinder;
	t_sphere	*sphere;
}	t_data;

#endif