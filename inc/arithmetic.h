#ifndef ARITHMETIC_H
# define ARITHMETIC_H

// vector_vector.c
void	vector_divide(t_vector *v1, t_vector *v2, t_vector *new);
void	vector_multiply(t_vector *v1, t_vector *v2, t_vector *new);
void	vector_add(t_vector *v1, t_vector *v2, t_vector *new);
void	vector_subtract(t_vector *v1, t_vector *v2, t_vector *new);

// vector_double.c
void	divide(t_vector *v1, double d);
void	multiply(t_vector *v1, double d);
void	add(t_vector *v1, double d);
void	subtract(t_vector *v1, double d);

#endif