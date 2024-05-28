/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:30 by felicia           #+#    #+#             */
/*   Updated: 2024/05/28 18:40:01 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define GREEN		"\033[32m"
# define RED 		"\033[31m"
# define BLUE		"\033[34m"
# define PURPLE		"\033[35m"
# define YELLOW		"\033[33m"
# define BOLD		"\033[1m"
# define OFF		"\033[0m"

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600

# define ROUNDING_CORRECTION 0.0001

# define ESCAPE 256

# define SPHERE 1
# define PLANE 2
# define CYLINDER_TUBE 3
# define CYLINDER_CAP 4

# define TOP 1
# define BOTTOM -1

# define LIGHT_RAY 0
# define SHADOW_RAY 1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <math.h>
# include <string.h>

# include "libft.h"

# include "../MLX42/include/MLX42/MLX42.h"

# include "types.h"
# include "mlx.h"
# include "parser.h"
# include "maths.h"
# include "render.h"
# include "hit.h"
# include "objects.h"

// free_data.c
void	free_planes(t_plane *plane);
void	free_spheres(t_sphere *sphere);
void	free_cylinders(t_cylinder *cylinder);
void	free_all_data(t_data *data);

// error.c
void	error(char *message, int code);

#endif