#include "minirt.h"

void	key_press(mlx_key_data_t key_data, void *param)
{
	(void)param;
	printf("keycode = %i\n", key_data.key);
	param = NULL;
	if (key_data.key == ESCAPE)
	{
		printf("Bye bye!\n");
		exit(0);
	}
}

void	setup_mlx(void)
{
	mlx_t		*mlx_ptr;
	mlx_image_t	*img_ptr;

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
	test(img_ptr);
	mlx_loop(mlx_ptr);
}
