#include "minirt.h"

double	dot(const t_vector *u, const t_vector *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
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
