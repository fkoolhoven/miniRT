#include "minirt.h"

double	length(t_vector *v)
{
	return (sqrt(dot(v, v)));
}

t_vector	normalize(t_vector *v)
{
	return (divide(v, length(v)));
}

double	dot(const t_vector *u, const t_vector *v)
{
	return (u->x * v->x + u->y * v->y + u->z * v->z);
}
