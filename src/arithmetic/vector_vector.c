#include "minirt.h"

t_vector	vector_divide(const t_vector *v1, const t_vector *v2)
{
	t_vector new;

	new.x = v1->x / v2->x;
	new.y = v1->y / v2->y;
	new.z = v1->z / v2->z;
	return (new);
}

t_vector	vector_multiply(const t_vector *v1, const t_vector *v2)
{
	t_vector new;

	new.x = v1->x * v2->x;
	new.y = v1->y * v2->y;
	new.z = v1->z * v2->z;
	return (new);
}

t_vector	vector_add(const t_vector *v1, const t_vector *v2)
{
	t_vector new;

	new.x = v1->x + v2->x;
	new.y = v1->y + v2->y;
	new.z = v1->z + v2->z;
	return (new);
}

t_vector	vector_subtract(const t_vector *v1, const t_vector *v2)
{
	t_vector new;

	new.x = v1->x - v2->x;
	new.y = v1->y - v2->y;
	new.z = v1->z - v2->z;
	return (new);
}
