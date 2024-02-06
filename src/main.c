#include "minirt.h"

void	key_press(mlx_key_data_t key_data, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	printf("keycode = %i\n", key_data.key);
	if (key_data.key == ESCAPE)
	{
		exit(EXIT_SUCCESS);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_RIGHT))
	{
		data->camera.view_point.x += 0.5;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_LEFT))
	{
		data->camera.view_point.x -= 0.5;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_UP))
	{
		data->camera.view_point.y += 0.5;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_DOWN))
	{
		data->camera.view_point.y -= 0.5;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_P))
	{
		data->camera.view_point.z += 0.5;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_L))
	{
		data->camera.view_point.z -= 0.5;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_A) && data->camera.orientation.x >= -0.9)
	{
		data->camera.orientation.x -= 0.1;
		printf("orientation = %f, %f, %f\n", data->camera.orientation.x, data->camera.orientation.y, data->camera.orientation.z);
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_D) && data->camera.orientation.x <= 0.9)
	{
		data->camera.orientation.x += 0.1;
		printf("orientation = %f, %f, %f\n", data->camera.orientation.x, data->camera.orientation.y, data->camera.orientation.z);
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_W) && data->camera.orientation.y <= 0.9)
	{
		data->camera.orientation.y += 0.1;
		printf("orientation = %f, %f, %f\n", data->camera.orientation.x, data->camera.orientation.y, data->camera.orientation.z);
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_S) && data->camera.orientation.y >= -0.9)
	{
		data->camera.orientation.y -= 0.1;
		printf("orientation = %f, %f, %f\n", data->camera.orientation.x, data->camera.orientation.y, data->camera.orientation.z);
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_R) && data->camera.orientation.z >= -0.9)
	{
		data->camera.orientation.z -= 0.1;
		printf("orientation = %f, %f, %f\n", data->camera.orientation.x, data->camera.orientation.y, data->camera.orientation.z);
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_F) && data->camera.orientation.z <= 0.9)
	{
		data->camera.orientation.z += 0.1;
		printf("orientation = %f, %f, %f\n", data->camera.orientation.x, data->camera.orientation.y, data->camera.orientation.z);
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_LEFT_BRACKET) && data->camera.horizontal_field_of_view > 0)
	{
		data->camera.horizontal_field_of_view -= 10;
		render_image(data);
	}
	if (mlx_is_key_down(data->mlx_info->mlx_ptr, MLX_KEY_RIGHT_BRACKET) && data->camera.horizontal_field_of_view < 180)
	{
		data->camera.horizontal_field_of_view += 10;
		render_image(data);
	}
}

void	setup_mlx(t_data *data)
{
	t_mlx_info	*mlx_info;
	mlx_t		*mlx_ptr;
	mlx_image_t	*img_ptr;

	mlx_info = malloc(sizeof(t_mlx_info));
	if (mlx_info == NULL)
	{
		// handle error
	}
	mlx_ptr = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "MiniRT", true);
	if (mlx_ptr == NULL)
	{
		// handle error
	}
	img_ptr = mlx_new_image(mlx_ptr, IMAGE_WIDTH, IMAGE_HEIGHT);
	if (img_ptr == NULL)
	{
		// handle error
	}
	mlx_image_to_window(mlx_ptr, img_ptr, 0, 0);
	mlx_info->mlx_ptr = mlx_ptr;
	mlx_info->img_ptr = img_ptr;
	data->mlx_info = mlx_info;
}

int	main(int argc, char **argv)
{
	t_data		data;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(&data, argv[1]); // check return for input validation or no?
	setup_mlx(&data);
	mlx_key_hook(data.mlx_info->mlx_ptr, key_press, &data);
	render_image(&data);
	mlx_loop(data.mlx_info->mlx_ptr);
	return (EXIT_SUCCESS);
}
