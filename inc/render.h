#ifndef RENDER_H
# define RENDER_H

// get_objects.c
t_hit_record *	get_hit_record(void);
t_point			get_point(double x, double y, double z);

// render.c
void			render_image(t_data *data);

// utils.c
unsigned int	get_rgba(int r, int g, int b, int a);

#endif