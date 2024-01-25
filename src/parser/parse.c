#include "minirt.h"
#include "parser.h"

void	store_L(t_data *data, char *input)
{
	char	**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(input, 1);
	if (store_xyz(items[0], &data->light.point) ||
		store_xyz(items[2], &(data->light.color)))
		error("Light parameters are incorrect", 1);
	data->light.brightness = ft_atod(items[1]);
	frdp(items);
}

void	store_C(t_data *data, char *input)
{
	char	**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 3)
		error(input, 1);
	if (store_xyz(items[0], &data->camera.view_point) ||
		store_xyz(items[1], &data->camera.orientation))
		error("Camera parameters are incorrect", 1);
	data->camera.horizontal_field_of_view = ft_atod(items[2]);
	frdp(items);
}
void	store_A(t_data *data, char *input)
{
	t_vector	ambient;
	char		**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 2)
		error(input, 1);
	if (store_xyz(items[1], &(data->ambient.color)))
		error("Ambient light parameters are incorrect", 1);
	data->ambient.ratio = ft_atod(items[0]);
	ambient = multiply(&data->ambient.color, data->ambient.ratio);
	ambient = divide(&ambient, 255.0);
	data->ambient.ambient_light = ambient;
	frdp(items);
}

void	store_data(t_data *data, char *input)
{
	if (!ft_strncmp("A ", input, 2))
		store_A(data, input + 2);
	else if (!ft_strncmp("C ", input, 2))
		store_C(data, input + 2);
	else if (!ft_strncmp("L ", input, 2))
		store_L(data, input + 2);
	else if (!ft_strncmp("sp ", input, 3))
		add_sphere(&(data->sphere), sphere_new(input + 3));
	else if (!ft_strncmp("pl ", input, 3))
		add_plane(&(data->plane), plane_new(input + 3));
	else if (!ft_strncmp("cy ", input, 3))
		add_cylinder(&(data->cylinder), cylinder_new(input + 3));
	else if (*input != '\n')
		printf("line: -> %s\twas ignored\n", input);
}

void	print_sphere(t_sphere *sp)
{
	printf("spheres:\n");
	while (sp)
	{
		printf("\t%.2f,%.2f,%.2f | %.2f | %.2f,%.2f,%.2f\n", sp->center.x, sp->center.y, sp->center.z, sp->radius * 2, sp->color.x,  sp->color.y, sp->color.z);
		sp = sp->next;
	}
}
void	print_cylinder(t_cylinder *cy)
{
	printf("cylinders:\n");
	while (cy)
	{
		printf("\t%.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %.2f | %.2f | %.2f,%.2f,%.2f\n", cy->center.x, cy->center.y, cy->center.z, cy->axis.x,  cy->axis.y, cy->axis.z, cy->radius * 2, cy->height, cy->color.x, cy->color.y, cy->color.z);
		cy = cy->next;
	}
}
void	print_plane(t_plane *pl)
{
	printf("planes:\n");
	while (pl)
	{
		printf("\t%.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %.2f,%.2f,%.2f\n", pl->point.x, pl->point.y, pl->point.z, pl->normal.x, pl->normal.y, pl->normal.z, pl->color.x,  pl->color.y, pl->color.z);
		pl = pl->next;
	}
}

void	print_info(t_data *data)
{
	printf("A: %.2f | %.2f,%.2f,%.2f\n", data->ambient.ratio, data->ambient.color.x,  data->ambient.color.y, data->ambient.color.z);
	printf("C: %.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %.2f\n", data->camera.view_point.x, data->camera.view_point.y, data->camera.view_point.z, data->camera.orientation.x,  data->camera.orientation.y, data->camera.orientation.z, data->camera.horizontal_field_of_view);
	printf("L: %.2f,%.2f,%.2f | %.2f | %.2f,%.2f,%.2f\n\n", data->light.point.x, data->light.point.y, data->light.point.z, data->light.brightness, data->light.color.x,  data->light.color.y, data->light.color.z);
	print_sphere(data->sphere);
	print_plane(data->plane);
	print_cylinder(data->cylinder);
	
}

void	parse(t_data *data, char *file)
{
	int		fd;
	int		i;
	char	*input;

	/*if we want to be fancy we can prompt user for different map that is legit*/
	fd = open(file, O_RDONLY);
	if (fd == -1)
		error(strerror(errno), errno);
	data->cylinder = NULL;
	data->plane = NULL;
	data->sphere = NULL;
	// also need to check if A C and L are found otherwise maybe error
	while (1)
	{
		i = 0;
		input = get_next_line(fd);
		if (!input)
			break ;
		while (input[i] && ft_iswhitespace(input[i]) && input[i] != '\n')
			i++;
		if (input[i] != '#')
			store_data(data, input + i);
		free(input);
	}
	close(fd);
	print_info(data);
}
