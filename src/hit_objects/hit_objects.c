#include "minirt.h"

// Loops through all the spheres and finds the closest hit (if any). Updates the hit record with the closest hit.
bool	check_all_spheres(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	t_sphere	*current_sphere = data->sphere;

	while (current_sphere != NULL)
	{
		if (find_closer_sphere_hit(current_sphere, ray, params)) 
		{
			params->hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
			*rec = *params->temp_rec;
		}
		current_sphere = current_sphere->next;
	}
	return (params->hit_anything);
}

// Loops through all the planes and finds the closest hit (if any). Updates the hit record with the closest hit.
bool	check_all_planes(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	t_plane	*current_plane = data->plane;

	while (current_plane != NULL)
	{
		if (find_closer_plane_hit(current_plane, ray, params))
		{
			params->hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
			*rec = *params->temp_rec;
		}
		current_plane = current_plane->next;
	}
	return (params->hit_anything);
}

// Loops through all the cylinders and finds the closest hit (if any). Updates the hit record with the closest hit.
bool	check_all_cylinders(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	t_cylinder	*current_cylinder = data->cylinder;

	while (current_cylinder != NULL)
	{
		if (find_closer_cylinder_hit(current_cylinder, ray, params))
		{
			params->hit_anything = true;
			params->closest_so_far = params->temp_rec->t;
			*rec = *params->temp_rec;
		}
		current_cylinder = current_cylinder->next;
	}
	return (params->hit_anything);
}

// This function makes sure we try to hit all objects in the scene with every ray.
// Let's the calling fuction know if any object was hit, so the color can be determined.
bool hit_objects(t_data *data, t_ray *ray, t_hit_params *params, t_hit_record *rec)
{
	params->hit_anything = check_all_spheres(data, ray, params, rec);
	params->hit_anything = check_all_planes(data, ray, params, rec);
	params->hit_anything = check_all_cylinders(data, ray, params, rec);

	free(params->temp_rec);
	free(params);
	return (params->hit_anything);
}