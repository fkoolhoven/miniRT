#include "minirt.h"

void	error(char *message, int code)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(code);
}


