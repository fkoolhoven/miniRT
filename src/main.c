#include "minirt.h"

void	key_press(mlx_key_data_t key_data, void *param)
{
	(void)param;
	printf("keycode = %i\n", key_data.key);
	param = NULL;
	if (key_data.key == ESCAPE)
	{
		printf("Bye bye!\n");
		exit(EXIT_SUCCESS);
	}
}

t_mlx_info	*setup_mlx(void)
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
	mlx_key_hook(mlx_ptr, key_press, NULL);
	mlx_info->mlx_ptr = mlx_ptr;
	mlx_info->img_ptr = img_ptr;
	return (mlx_info);
}

int	main(int argc, char **argv)
{
	t_data		data;
	t_mlx_info	*mlx_info;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(&data, argv[1]); // check return for input validation or no?
	mlx_info = setup_mlx();
	render_image(&data, mlx_info->img_ptr);
	mlx_loop(mlx_info->mlx_ptr);
	return (EXIT_SUCCESS);
}
