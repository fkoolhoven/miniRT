/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:31:19 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/08 15:58:20 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse(t_data *data, char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	/*if we want to be fancy we can prompt user for different map that is legit*/
	if (fd == -1)
		error(strerror(errno), errno);
	(void)data;
}
