#ifndef MATH_H
# define MATH_H

// vectors_arithmetic.c
t_vector	divide_vectors(const t_vector *v1, const t_vector *v2);
t_vector	multiply_vectors(const t_vector *v1, const t_vector *v2);
t_vector	add_vectors(const t_vector *v1, const t_vector *v2);
t_vector	subtract_vectors(const t_vector *v1, const t_vector *v2);

// double_arithmetic.c
t_vector	divide(const t_vector *v1, double d);
t_vector	multiply(const t_vector *v1, double d);
t_vector	add(const t_vector *v1, double d);
t_vector	subtract(const t_vector *v1, double d);

// vectors_math.c
double		length(t_vector *v);
t_vector	normalize(t_vector *v);
double		dot(const t_vector *u, const t_vector *v);

#endif