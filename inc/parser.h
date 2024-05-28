/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:22 by felicia           #+#    #+#             */
/*   Updated: 2024/05/28 18:24:03 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>

# define CY 1
# define SP 2
# define PL 3

// parse.c
int			store_xyz(char *s, t_point *xyz);
void		parse(t_data *data, char *file);

// parser_utils.c
int			ft_count_items(char **s);
void		frdp(char **s);

// new_node.c
t_cylinder	*cylinder_new(char *data);
t_sphere	*sphere_new(char *data);
t_plane		*plane_new(char *data);

// add_node.c
void		add_back(void **head, void *new, int type);
void		add_plane(t_plane **head, t_plane *new);
void		add_sphere(t_sphere **head, t_sphere *new);
void		add_cylinder(t_cylinder **head, t_cylinder *new);

// print_info.c
void		print_info(t_data *data);

// store_data.c
void		store_data(t_data *data, char *input);

// valid_object.c
bool		plane_parameters_are_valid(t_plane plane);
bool		sphere_parameters_are_valid(t_sphere sphere);
bool		cylinder_parameters_are_valid(t_cylinder cylinders);

// valid_ALC.c
bool		ambient_parameters_are_valid(t_ambient_light ambient);
bool		camera_parameters_are_valid(t_camera camera);
bool		light_parameters_are_valid(t_light light);

#endif