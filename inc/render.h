#ifndef RENDER_H
# define RENDER_H

// get_objects.c
t_hit_record	*get_hit_record(void);
t_point			get_point(double x, double y, double z);
t_hit_params	*get_hit_params();

// render.c
void			render_image(t_data *data);

// viewport.c
t_viewport		set_up_viewport(t_camera *camera);

#endif