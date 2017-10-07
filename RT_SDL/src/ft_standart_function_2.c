/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_standart_function_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 14:27:55 by kzahreba          #+#    #+#             */
/*   Updated: 2017/09/28 17:23:05 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	malloc_error(void)
{
	ft_putendl("Cann't alocate memory\n");
	exit(1);
}

void	put_error(const char *message, const char *second_message)
{
	write(1, message, ft_strlen(message));
	write(1, "\n", 1);
	if (second_message)
		write(1, second_message, ft_strlen(second_message));
	write(1, "\n", 1);
	exit(1);
}

void	ft_putendl(char const *s)
{
	size_t i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			write(1, &s[i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
}

size_t	ft_strlen(char const *str)
{
	size_t i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}


char	*ft_strdup(char const *s1) //переписати на норм функцію
{
	char		*str;
	size_t		i;

	i = -1;
	str = (char *)malloc(ft_strlen(s1) + 1);
	if (!str)
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}