/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvan-sch <cvan-sch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:51:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/08 15:56:15 by cvan-sch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(&data, argv[1]); // also validates input? yes!
	// init mlx
	// init mlx hooks
	// image to window
	// draw image somehow
	// clean up
	return (EXIT_SUCCESS);
}
