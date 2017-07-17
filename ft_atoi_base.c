/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 16:27:49 by kzahreba          #+#    #+#             */
/*   Updated: 2017/02/02 16:48:59 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		check(char c, int base)
{
	if (c >= '0' && c <= '9')
	{
		if (c - 48 < base)
			return (1);
	}
	else if (c >= 'A' && c <= 'F')
	{
		if (c - 55 < base)
			return (1);
	}
	else if (c >= 'a' && c <= 'f')
	{
		if (c - 87 < base)
			return (1);
	}
	return (0);
}

int				ft_atoi_base(const char *str, int base)
{
	int				sign;
	unsigned int	value;
	int				i;

	value = 0;
	sign = 1;
	i = 0;
	if (base < 2 || base > 16)
		return (0);
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (str[i] && check(str[i], base))
	{
		if (str[i] >= '0' && str[i] <= '9')
			value = value * base + (str[i] - 48);
		else if (str[i] >= 'A' && str[i] <= 'F')
			value = value * base + (str[i] - 55);
		else if (str[i] >= 'a' && str[i] <= 'f')
			value = value * base + (str[i] - 87);
		i++;
	}
	return ((int)(value * sign));
}
