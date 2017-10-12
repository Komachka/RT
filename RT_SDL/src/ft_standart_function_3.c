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

static inline int	ft_count(int nb)
{
	int		c;

	c = 0;
	if (nb <= 0)
		c = 1;
	while (nb != 0)
	{
		nb = nb / 10;
		c++;
	}
	return (c);
}

static inline char	*ft_action(char *res, int nb)
{
	int		i;
	long	nbr;

	nbr = nb;
	if (nb < 0)
		nbr = nbr * -1;
	i = ft_count(nb);
	res[i] = '\0';
	i--;
	while (nbr > 0)
	{
		res[i] = nbr % 10 + '0';
		i--;
		nbr = nbr / 10;
	}
	if (nb < 0)
		res[0] = '-';
	return (res);
}

char				*ft_itoa(int n)
{
	char	*res;

	res = (char*)malloc(sizeof(*res) * (ft_count(n) + 1));
	if (res == NULL)
		return (NULL);
	if (n == 0)
	{
		res[0] = '0';
		res[1] = '\0';
		return (res);
	}
	ft_action(res, n);
	return (res);
}
