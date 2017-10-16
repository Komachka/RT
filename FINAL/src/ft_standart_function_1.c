/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_standart_function_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 16:27:49 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 16:00:34 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline int	check(char c, int base)
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

int					ft_atoi_base(const char *str, int base)
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

_Bool				cmp(const char *str1, const char *str2)
{
	VAR_INT(index, 0);
	if (str1 && str2 && ft_strlen(str1) == ft_strlen(str2))
	{
		while (str1[index])
		{
			if ((unsigned char)str1[index] != (unsigned char)str2[index])
				return (0);
			index++;
		}
		return (1);
	}
	return (0);
}

char				*join(char const *str1, char const *str2)
{
	char	*str;

	VAR_INT(index1, 0);
	VAR_INT(index2, 0);
	str = (char*)malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	while (str1[index1])
	{
		str[index1] = str1[index1];
		index1++;
	}
	while (str2[index2])
	{
		str[index1] = str2[index2];
		index1++;
		index2++;
	}
	str[index1] = '\0';
	return (str);
}
