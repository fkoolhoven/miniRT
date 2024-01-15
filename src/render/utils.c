#include "minirt.h"

double	dot(const t_vector *u, const t_vector *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

unsigned int	get_rgba(int r, int g, int b, int a)
{
	return ((r & 0xFF) << 24) | ((g & 0xFF) << 16) | ((b & 0xFF) << 8) | (a & 0xFF);
}

double	length_squared(t_vector *v)
{
	return (v->x * v->x + v->y * v->y + v->z * v->z);
}

double	length(t_vector *v)
{
	return (sqrt(length_squared(v)));
}

t_vector	unit_vector(t_vector *v)
{
	return (divide(v, length(v)));
}
