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
	char	**items;

	items = ft_split(input, ' ');
	if (!items)
		error(strerror(errno), errno);
	if (ft_count_items(items) != 2)
		error(input, 1);
	if (store_xyz(items[1], &(data->ambient.color)))
		error("Ambient light parameters are incorrect", 1);
	data->ambient.ratio = ft_atod(items[0]);
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
		printf("found a line that was ignored: %s", input);
}

void	print_info(t_data *data)
{
	printf("A: %.2f | %.2f,%.2f,%.2f\n", data->ambient.ratio, data->ambient.color.x,  data->ambient.color.y, data->ambient.color.z);
	printf("C: %.2f,%.2f,%.2f | %.2f,%.2f,%.2f | %.2f\n", data->camera.view_point.x, data->camera.view_point.y, data->camera.view_point.z, data->camera.orientation.x,  data->camera.orientation.y, data->camera.orientation.z, data->camera.horizontal_field_of_view);
	printf("L: %.2f,%.2f,%.2f | %.2f | %.2f,%.2f,%.2f\n", data->light.point.x, data->light.point.y, data->light.point.z, data->light.brightness, data->light.color.x,  data->light.color.y, data->light.color.z);
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
	while (1)
	{
		i = 0;
		input = get_next_line(fd);
		if (!input)
			break ;
		while (ft_iswhitespace(input[i]) && input[i] != '\n')
			i++;
		if (input[i] != '#')
			store_data(data, input + i);
		free(input);
	}
	close(fd);
	// print_info(data);
}
