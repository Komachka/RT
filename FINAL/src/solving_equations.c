/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_equations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:52:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/16 15:52:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		check_solving(double *t, double t0)
{
	int i;

	i = 0;
	if (t0 > PRECISION)
	{
		*t = t0;
		i = 1;
	}
	return (i);
}

double	select_value(double *array, int len)
{
	double	x;
	int		i;

	i = -1;
	x = -1;
	while (++i < len)
		if (array[i] > PRECISION)
			x = array[i];
	i = -1;
	if (x > PRECISION)
		while (++i < len)
			if (array[i] > PRECISION && x > array[i])
				x = array[i];
	return (x);
}

int		quadratic_equation(t_equation *n)
{
	n->root[0] = -1;
	n->root[1] = -1;
	n->discr = n->b * n->b - 4.0 * n->a * n->c;
	if (n->discr < 0)
		return (0);
	n->sqdiscr = sqrt(n->discr);
	n->root[0] = (-n->b + n->sqdiscr) / (2.0 * n->a);
	n->root[1] = (-n->b - n->sqdiscr) / (2.0 * n->a);
	return (2);
}
