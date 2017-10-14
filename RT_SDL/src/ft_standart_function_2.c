/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_standart_function_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:27:55 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 16:03:22 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	malloc_error(void)
{
	write(1,"Can't allocate memory\n", 22);
	exit(1);
}

void	put_error(const char *message, const char *second_message)
{
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	if (second_message)
	{
		write(1, second_message, ft_strlen(second_message));
		write(1, "\n", 1);
	}
	exit(1);
}

size_t	ft_strlen(char const *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
