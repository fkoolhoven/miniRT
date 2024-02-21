#ifndef SHADING_H
# define SHADING_H

# include "types.h"

// shading.c
t_color	apply_shading(t_data *data, t_hit_record *rec);
int		is_in_shadow(t_data *data, t_hit_record *rec);

#endif