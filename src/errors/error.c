#include "minirt.h"

void	error(char *message, int code)
{
	unsigned	i;

	i = 0;
	while (message[i])
		i++;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, message, i);
	write(STDERR_FILENO, "\n", 1);
	exit(code);
}
