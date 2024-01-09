#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "types.h"

// utils
int			ft_count_items(char **s);
void		frdp(char **s);

// lst
t_cylinder	*cylinder_new(char *data);
t_sphere	*sphere_new(char *data);
t_plane		*plane_new(char *data);

void		add_plane(t_plane **head, t_plane *new);
void		add_sphere(t_sphere **head, t_sphere *new);
void		add_cylinder(t_cylinder **head, t_cylinder *new);


// parse.c
int			store_xyz(char *s, t_point *xyz);
void		parse(t_data *data, char *file);

#endif