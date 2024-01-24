#ifndef RENDER_H
# define RENDER_H

// get_objects.c
t_viewport		get_viewport(void);
t_hit_record *	get_hit_record(void);
t_point			get_point(double x, double y, double z);

// render.c
void			render_image(t_data *data, mlx_image_t *img_ptr);

// utils.c
double			dot(const t_vector *u, const t_vector *v);
unsigned int	get_rgba(int r, int g, int b, int a);
t_vector 		normalize(t_vector *v);
double			length(t_vector *v);

#endif