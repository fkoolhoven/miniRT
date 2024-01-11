#ifndef TEST_H
# define TEST_H

// get_test_objects.c
t_sphere	get_test_sphere(double x, double y, double z, double diameter);
t_camera	get_test_camera();
t_viewport	get_test_viewport();
t_hit_record *get_test_hit_record();

// render.c
void		render_image(mlx_image_t *img_ptr, t_camera *camera);

// test.c
void		test(mlx_image_t *img_ptr);

// utils.c
t_point		get_point(double x, double y, double z);
double		dot(const t_vector *u, const t_vector *v);
int 		get_rgba(int r, int g, int b, int a);
t_vector 	unit_vector(t_vector *v);
double 		length_squared(t_vector *v);

// ray.c
t_point 	trace_ray(t_ray *ray, double t);


#endif