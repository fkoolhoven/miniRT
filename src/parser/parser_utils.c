/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:53:47 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/05/21 18:57:32 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_count_items(char **s)
{
	int	count;

	if (!s)
		return (-1);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

int	store_xyz(char *s, t_point *xyz)
{
	char	**arg;

	arg = ft_split(s, ',');
	if (!arg)
		error(strerror(errno), errno);
	if (ft_count_items(arg) != 3)
	{
		frdp(arg);
		return (EXIT_FAILURE);
	}
	xyz->x = ft_atod(arg[0]);
	xyz->y = ft_atod(arg[1]);
	xyz->z = ft_atod(arg[2]);
	frdp(arg);
	return (EXIT_SUCCESS);
}
