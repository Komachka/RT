/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solving_equations_2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/16 15:30:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/16 15:30:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline double	cubic_resolve(double p, double q, double r)
{
	double	i;
	double	rr;
	double	i_3;
	double	s_i;

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

static inline int		continue_calculating(t_cubic_resv tmp, t_quartic_eq *n,
																const double *d)
{
	tmp.z = sqrt(tmp.z);
	tmp.p = sqrt(tmp.p);
	n->root[0] = -0.5 * (d[0] + tmp.z) + tmp.r;
	n->root[1] = -0.5 * (d[0] - tmp.z) + tmp.r;
	n->root[2] = 0.5 * (d[0] + tmp.p) + tmp.r;
	n->root[3] = 0.5 * (d[0] - tmp.p) + tmp.r;
	return (4);
}

int						calculating_roots(t_quartic_eq *n, t_cubic_resv *c,
															const double *d)
{
	t_cubic_resv	tmp;

	tmp.q = d[0] * d[0];
	tmp.r = -0.25 * n->b;
	tmp.z = tmp.q - 4.0 * (c->z - d[1]);
	tmp.p = tmp.q - 4.0 * (c->z + d[1]);
	if (tmp.z >= 0 && tmp.p >= 0)
		return (continue_calculating(tmp, n, d));
	else if (tmp.z >= 0)
	{
		tmp.z = sqrt(tmp.z);
		n->root[0] = -0.5 * (d[0] + tmp.z) + tmp.r;
		n->root[1] = -0.5 * (d[0] - tmp.z) + tmp.r;
		return (2);
	}
	else if (tmp.p >= 0)
	{
		tmp.p = sqrt(tmp.p);
		n->root[0] = 0.5 * (d[0] - tmp.p) + tmp.r;
		n->root[1] = 0.5 * (d[0] + tmp.p) + tmp.r;
		return (2);
	}
	return (0);
}

static inline int		continue_equation(double *d, t_quartic_eq *n,
															t_cubic_resv c)
{
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

int						quartic_equation(t_quartic_eq *n)
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
	c.q = 1.0 / 8.0 * n->b * n->b * n->b - 1.0 / 2.0 * n->b * n->c + n->d;
	c.r = -3.0 / 256.0 * n->b * n->b * n->b * n->b + 1.0 / 16.0 * n->b * n->b *
			n->c - 1.0 / 4.0 * n->b * n->d + n->e;
	c.z = cubic_resolve(-c.p / 2.0, -c.r, (4.0 * c.r * c.p - c.q * c.q) / 8.0);
	d[0] = 2.0 * c.z - c.p;
	return (continue_equation(d, n, c));
}
