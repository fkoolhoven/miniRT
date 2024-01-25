#include "minirt.h"
// Calculations shouldn't be done for each pixel, calculating ambient light color should be done only once
// Get shadows based on other objects in the scene

t_color apply_shading(t_data *data, t_hit_record *rec)
{
	// calculate the diffuse light component
	t_light light = data->light;
	t_vector temp = vector_subtract(&light.point, &rec->point);
	t_vector light_direction_normal = normalize(&temp);
	double diffuse_intensity = fmax(dot(&rec->normal, &light_direction_normal), 0.0);
	diffuse_intensity = light.brightness * diffuse_intensity;
	t_vector diffuse_light = multiply(&light.color, diffuse_intensity);
	diffuse_light = divide(&diffuse_light, 255.0);

	// calculate the ambient light component
	t_ambient_light	ambient_light;
	ambient_light = data->ambient;
	ambient_light.color = multiply(&ambient_light.color, ambient_light.ratio);
	ambient_light.color = divide(&ambient_light.color, 255.0);


	// calculate the final color
	t_color 		object_color;
	object_color = rec->color;
	t_color			final_color;
	t_color		all_light;

	all_light = vector_add(&diffuse_light, &ambient_light.color);
	if (all_light.x > 1.0)
		all_light.x = 1.0;
	if (all_light.y > 1.0)
		all_light.y = 1.0;
	if (all_light.z > 1.0)
		all_light.z = 1.0;
	final_color = vector_multiply(&object_color, &all_light);
	final_color = divide(&final_color, 255.0);
    return (final_color);
}
