/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 14:57:57 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/01/04 15:06:16 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	error(char *message, int code)
{
	unsigned	i;

	i = 0;
	while (message[i])
		i++;
	write(STDERR_FILENO, "Error: ", 7);
	write(STDERR_FILENO, message, i);
	write(STDERR_FILENO, "\n", 1);
	exit(code);
}
