#include "minirt.h"

// Calculations shouldn't be done for each pixel, but for each object.
// Question, how should ambient light color affect the object color?
// If the color is white and ratio 1.0 should everything be entirely white?
t_color apply_shading(t_data *data, t_color *object_color)
{
	t_ambient_light	ambient_light;
	t_color			final_color;

	ambient_light = data->ambient;
	ambient_light.color = multiply(&ambient_light.color, ambient_light.ratio);
	ambient_light.color = divide(&ambient_light.color, 255);
	*object_color = divide(object_color, 255);
	final_color = vector_multiply(object_color, &ambient_light.color);
    return (final_color);
}
