#include "minirt.h"

void	render_image(mlx_image_t *img_ptr)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			mlx_put_pixel(img_ptr, x, y, 0x00FF00FF);
			x++;
		}
		y++;
	}
}

void	key_press(mlx_key_data_t key_data, void *param)
{
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
	img_ptr = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (img_ptr == NULL)
	{
		// handle error
	}
	mlx_image_to_window(mlx_ptr, img_ptr, 0, 0);
	mlx_key_hook(mlx_ptr, key_press, NULL);
	render_image(img_ptr);
	mlx_loop(mlx_ptr);
}
