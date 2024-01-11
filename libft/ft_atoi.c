/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cristje <cristje@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 20:46:58 by cvan-sch          #+#    #+#             */
/*   Updated: 2023/01/26 13:45:51 by cristje          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		res;
	char	*s;
	int		sign;

	s = (char *)str;
	res = 0;
	while (ft_iswhitespace(*s))
		s++;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	while (ft_isdigit(*s))
		res *= 10 + (*s - '0');
	return (res * sign);
}

int	ft_iswhitespace(int c)
{
	return (c == ' ' || (c >= '\t'&& c <= '\r'));
}

double	ft_atod(char *s)
{
	double	result;
	double	factor;
	int		sign;

	sign = 1;
	result = 0.0;
	factor = 0.1;
	while (ft_iswhitespace(*s))
		s++;
	if ((*s == '+' || *s == '-') && *(s++) == '-')
		sign = -1;
	while (ft_isdigit(*s))
		result = result * 10.0 + (*(s++) - '0');
	if (*s == '.')
		s++;
	while (ft_isdigit(*s))
	{
		result = result + (factor * (*(s++) - '0'));
		factor = factor * 0.1;
	}
	return (result * sign);
}
