#include "minirt.h"

double	dot(const t_vector *u, const t_vector *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

double	length(t_vector *v)
{
	return (sqrt(dot(v, v)));
}

t_vector	normalize(t_vector *v)
{
	return (divide(v, length(v)));
}
