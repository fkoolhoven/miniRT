#include "minirt.h"

void	parse(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	printf("fd = %i\n", fd);
}
