#ifndef ARITHMETIC_H
# define ARITHMETIC_H

// vector_vector.c
t_vector	vector_divide(const t_vector *v1, const t_vector *v2);
t_vector	vector_multiply(const t_vector *v1, const t_vector *v2);
t_vector	vector_add(const t_vector *v1, const t_vector *v2);
t_vector	vector_subtract(const t_vector *v1, const t_vector *v2);

// vector_double.c
t_vector	divide(const t_vector *v1, double d);
t_vector	multiply(const t_vector *v1, double d);
t_vector	add(const t_vector *v1, double d);
t_vector	subtract(const t_vector *v1, double d);

#endif