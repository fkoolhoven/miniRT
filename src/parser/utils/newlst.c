#include "minirt.h"

t_plane	*plane_new(char *data)
{
	t_plane	*new;
	char	**items;

	items = ft_split(data, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(data, 1);
	new = malloc(sizeof(t_plane));
	if (!new)
		error("Malloc failure", errno);
	if (store_xyz(items[0], &new->point) ||
		store_xyz(items[1], &new->normal) ||
		store_xyz(items[2], &(new->color)))
		error("Plane parameters are incorrect", 1);
	new->next = NULL;
	frdp(items);
	return (new);
}

t_sphere	*sphere_new(char *data)
{
	t_sphere	*new;
	char		**items;

	items = ft_split(data, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(data, 1);
	new = malloc(sizeof(t_sphere));
	if (!new)
		error("Malloc failure", errno);
	if (store_xyz(items[0], &new->center) ||
		store_xyz(items[2], &(new->color)))
		error("Sphere parameters are incorrect", 1);
	new->radius = ft_atod(items[1]) / 2;
	new->next = NULL;
	frdp(items);
	return (new);
}

t_cylinder	*cylinder_new(char *data)
{
	t_cylinder	*new;
	char	**items;

	items = ft_split(data, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 5)
		error(data, 1);
	new = malloc(sizeof(t_cylinder));
	if (!new)
		error("Malloc failure", errno);
	if (store_xyz(items[0], &new->center) ||
		store_xyz(items[1], &new->axis) ||
		store_xyz(items[4], &(new->color)))
		error("Cylinder parameters are incorrect", 1);
	new->radius = ft_atod(items[2]) / 2;
	new->height = ft_atod(items[3]);
	new->next = NULL;
	frdp(items);
	return (new);
}
