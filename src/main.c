#include "minirt.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(argv[1]); // also validates input?
	setup_mlx();
	// init mlx
	// init mlx hooks
	// image to window
	// draw image somehow
	// clean up
	return (EXIT_SUCCESS);
}
