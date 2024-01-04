/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 12:51:37 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/04 15:04:20 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
		error("Incorrect number of arguments", EXIT_FAILURE);
	parse(argv[1]); // also validates input?
	// init mlx
	// init mlx hooks
	// image to window
	// draw image somehow
	// clean up
	return (EXIT_SUCCESS);
}
