/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:30 by felicia           #+#    #+#             */
/*   Updated: 2024/05/06 00:00:51 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define ESCAPE 256
# define RIGHT_ARROW 262
# define LEFT_ARROW 263
# define UP_ARROW 265
# define DOWN_ARROW 264

# define SPHERE 1
# define PLANE 2
# define CYLINDER 3

# define A 0
# define B 1
# define C 2
# define DISCRIMINANT 3

# define TOP_CAP 1
# define BOTTOM_CAP -1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <math.h>
# include <float.h>

# include "libft.h"

# include "../MLX42/include/MLX42/MLX42.h"
# include "types.h"
# include "parser.h"
# include "vector_math.h"
# include "errors.h"
# include "render.h"
# include "hit_objects.h"
# include "objects.h"

#endif