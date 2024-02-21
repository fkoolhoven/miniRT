#include "minirt.h"

//go through all sphere's, planes and cylinders until we find a hit that

int	is_in_shadow(t_data *data, t_hit_record *rec)
{
	t_ray		shadow;
	t_sphere	*sp;
	double		qa[4];

	shadow.origin = rec->point;
	shadow.direction = data->light.point;
	sp = data->sphere;
    return (0);
	while (sp)
	{
		// still need to figure out if the light source is closer than the closest intersection of the sphere
		if (sp != rec->object)
		{
			if (sphere_hit(sp, &shadow, qa))
				return (1);
		}
		sp = sp->next;
	}
	return (0);
}
