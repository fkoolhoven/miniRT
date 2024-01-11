#ifndef MINIRT_H
# define MINIRT_H

# define WINDOW_WIDTH 1800
# define WINDOW_HEIGHT 900
# define IMAGE_WIDTH WINDOW_WIDTH
# define IMAGE_HEIGHT WINDOW_HEIGHT
# define ESCAPE 256

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
# include "errors.h"
# include "arithmetic.h"
# include "render.h"

#endif