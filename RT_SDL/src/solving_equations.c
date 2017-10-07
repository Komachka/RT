/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_equations_1.c                                :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 21:13:39 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/04 16:36:58 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double		find_positive(double *array, int len)
{
	int i;

	i = -1;
	while (++i < len)
	{
		if (array[i] > PRECISION)
			return (array[i]);
	}
	return (-1);
}

double		select_value(double *array, int len)
{
	double	x;
	int		i;

	i = -1;
	x = find_positive(array, len);
	if (x > PRECISION)
	{
		while (++i < len)
			if (array[i] > PRECISION && x > array[i])
				x = array[i];
	}
	return (x);
}

int			quadratic_equation(t_equation *n)
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

double		cubic_resolvent(double p, double q, double r)
{
	double i;
	double rr;
	double i_3;
	double s_i;

	i = (p * p - 3.0 * q) / 9.0;
	rr = (p * (p * p - 4.5 * q) + 13.5 * r) / 27.0;
	i_3 = i * i * i;
	if (i_3 - rr * rr >= 0)
		return (-2.0 * sqrt(i) * cos(acos(rr / sqrt(i_3)) / 3.0) - p / 3.0);
	else
	{
		s_i = cbrt(sqrt(rr * rr - i_3) + fabs(rr));
		if (rr < 0)
			return ((s_i + i / s_i) - p / 3.0);
		else
			return (-(s_i + i / s_i) - p / 3.0);
	}
}

int			calculating_roots(t_quartic_eq *n, t_cubic_resv *c, double *d)
{
	double q[2];
	double pm;
	double pp;

	q[0] = d[0] * d[0];
	q[1] = -0.25 * n->b;
	pm = q[0] - 4.0 * (c->z - d[1]);
	pp = q[0] - 4.0 * (c->z + d[1]);
	if (pm >= 0 && pp >= 0)
	{
		pm = sqrt(pm);
		pp = sqrt(pp);
		n->root[0] = -0.5 * (d[0] + pm) + q[1];
		n->root[1] = -0.5 * (d[0] - pm) + q[1];
		n->root[2] = 0.5 * (d[0] + pp) + q[1];
		n->root[3] = 0.5 * (d[0] - pp) + q[1];
		return (4);
	}
	else if (pm >= 0)
	{
		pm = sqrt(pm);
		n->root[0] = -0.5 * (d[0] + pm) + q[1];
		n->root[1] = -0.5 * (d[0] - pm) + q[1];
		return (2);
	}
	else if (pp >= 0)
	{
		pp = sqrt(pp);
		n->root[0] = 0.5 * (d[0] - pp) + q[1];
		n->root[1] = 0.5 * (d[0] + pp) + q[1];
		return (2);
	}
	return (0);
}

int			quartic_equation(t_quartic_eq *n)
{
	t_cubic_resv	c;
	double			d[2];

	n->b /= n->a;
	n->c /= n->a;
	n->d /= n->a;
	n->e /= n->a;
	n->a = 1;
	VAR_INT(i, -1);
	while (++i < 3)
		n->root[i] = -1;
	c.p = -3.0 / 8.0 * n->b * n->b + n->c;
	c.q = 1.0 / 8.0 * n->b * n->b * n->b - \
		1.0 / 2.0 * n->b * n->c + n->d;
	c.r = -3.0 / 256.0 * n->b * n->b * n->b * n->b + 1.0 / \
		16.0 * n->b * n->b * n->c - 1.0 / 4.0 * n->b * n->d + n->e;
	c.z = cubic_resolvent(-c.p / 2.0, -c.r,
			(4.0 * c.r * c.p - c.q * c.q) / 8.0);
	d[0] = 2.0 * c.z - c.p;
	if (d[0] < 0.0f)
	{
		if (d[0] > PRECISION)
			d[0] = 0;
		else
			return (0);
	}
	if (d[0] < PRECISION)
	{
		d[1] = c.z * c.z - c.r;
		if (d[1] < 0)
			return (0);
		d[1] = sqrt(d[1]);
	}
	else
	{
		d[0] = sqrt(d[0]);
		d[1] = 0.5 * c.q / d[0];
	}
	return (calculating_roots(n, &c, d));
}

