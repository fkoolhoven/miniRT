#include "minirt.h"

void	divide(t_vector *v1, double d)
{
	v1->x /= d;
	v1->y /= d;
	v1->z /= d;
}

void	multiply(t_vector *v1, double d)
{
	v1->x *= d;
	v1->y *= d;
	v1->z *= d;
}

void	add(t_vector *v1, double d)
{
	v1->x += d;
	v1->y += d;
	v1->z += d;
}

void	subtract(t_vector *v1, double d)
{
	v1->x -= d;
	v1->y -= d;
	v1->z -= d;
}
