#ifndef MINIRT_H
# define MINIRT_H

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define IMAGE_WIDTH WINDOW_WIDTH
# define IMAGE_HEIGHT WINDOW_HEIGHT
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
# include "shading.h"
# include "hit_objects.h"
# include "objects.h"

#endif