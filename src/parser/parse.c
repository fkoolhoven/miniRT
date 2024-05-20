/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:34 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/20 14:10:55 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	initialize_data_struct(t_data *data)
{
	data->cylinder = NULL;
	data->plane = NULL;
	data->sphere = NULL;
	data->window_width = WINDOW_WIDTH;
	data->window_height = WINDOW_HEIGHT;
}

void	parse(t_data *data, char *file)
{
	int		fd;
	int		i;
	char	*input;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error(strerror(errno), errno);
	initialize_data_struct(data);
	while (true)
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
