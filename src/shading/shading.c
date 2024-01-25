#include "minirt.h"

// Get shadows based on other objects in the scene, right now objects cast no shadows

// Calculate the diffuse portion of the light (depends on the angle between the light and the surface normal)
t_vector	get_diffuse_light(t_data *data, t_hit_record *rec)
{
	t_light		light;
	t_vector	light_direction_normal;
	double		diffuse_intensity;
	t_vector	diffuse;
	t_vector	light_direction;

	light = data->light;
	light_direction = subtract_vectors(&light.point, &rec->point);
	light_direction_normal = normalize(&light_direction);
	diffuse_intensity = fmax(dot(&rec->normal, &light_direction_normal), 0.0);
	diffuse_intensity = light.brightness * diffuse_intensity;
	diffuse = multiply(&light.color, diffuse_intensity);
	diffuse = divide(&diffuse, 255.0);
	return (diffuse);
}

t_vector	get_all_light(t_data *data, t_hit_record *rec)
{
	t_vector	diffuse_light;
	t_vector	ambient_light;
	t_vector	all_light;

	diffuse_light = get_diffuse_light(data, rec);
	ambient_light = data->ambient.ambient_light; // Calculated during parsing
	all_light = add_vectors(&diffuse_light, &ambient_light);
	if (all_light.x > 1.0)
		all_light.x = 1.0;
	if (all_light.y > 1.0)
		all_light.y = 1.0;
	if (all_light.z > 1.0)
		all_light.z = 1.0;
	return (all_light);
}

t_color apply_shading(t_data *data, t_hit_record *rec)
{
	t_vector	all_light;
	t_color 	object_color;
	t_color		final_color;

	all_light = get_all_light(data, rec);
	object_color = rec->color;
	final_color = multiply_vectors(&object_color, &all_light);
	final_color = divide(&final_color, 255.0);
    return (final_color);
}
