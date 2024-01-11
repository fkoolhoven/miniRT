#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(&data, argv[1]); // also validates input? yes!
	setup_mlx();
	// init mlx
	// init mlx hooks
	// image to window
	// draw image somehow
	// clean up
	return (EXIT_SUCCESS);
}
