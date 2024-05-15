/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 23:09:30 by felicia           #+#    #+#             */
/*   Updated: 2024/05/15 18:24:55 by fkoolhov         ###   ########.fr       */
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
# define ESCAPE 256

# define SPHERE 1
# define PLANE 2
# define CYLINDER 3

# define TOP 1
# define BOTTOM -1

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/errno.h>
# include <math.h>

# include "libft.h"

# include "../MLX42/include/MLX42/MLX42.h"

# include "types.h"
# include "mlx.h"
# include "parser.h"
# include "vectors_math.h"
# include "errors.h"
# include "render.h"
# include "hit_objects.h"
# include "objects.h"

#endif