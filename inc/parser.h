/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:22 by felicia           #+#    #+#             */
/*   Updated: 2024/05/06 13:58:06 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <fcntl.h>
# include "types.h"

# define CY 1
# define SP 2
# define PL 3

// utils
int			ft_count_items(char **s);
void		frdp(char **s);

// lst
t_cylinder	*cylinder_new(char *data);
t_sphere	*sphere_new(char *data);
t_plane		*plane_new(char *data);

void		add_back(void **head, void *new, int type);
void		add_plane(t_plane **head, t_plane *new);
void		add_sphere(t_sphere **head, t_sphere *new);
void		add_cylinder(t_cylinder **head, t_cylinder *new);

// parse.c
int			store_xyz(char *s, t_point *xyz);
void		parse(t_data *data, char *file);

// print_info.c
void		print_info(t_data *data);

#endif