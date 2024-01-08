#include "minirt.h"

void	parse(t_data *data, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	/*if we want to be fancy we can prompt user for different map that is legit*/
	if (fd == -1)
		error(strerror(errno), errno);
	(void)data;
}
