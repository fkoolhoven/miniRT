#include "minirt.h"

void	test(mlx_image_t *img_ptr)
{
	t_camera camera = get_test_camera();
	render_image(img_ptr, &camera);
}