/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:59:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 15:59:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline double	check_cone_limits(double t, t_ray *r, t_limited_cone *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->p1);
		tmp[1] = vector_substract(&point, &c->p2);
		if (c->h1 > c->h2)
		{
			if (vector_dot_product(&c->dir, &tmp[0]) < PRECISION &&
					vector_dot_product(&c->dir, &tmp[1]) > PRECISION)
				return (t);
		}
		else
		{
			if (vector_dot_product(&c->dir, &tmp[0]) > PRECISION &&
					vector_dot_product(&c->dir, &tmp[1]) < PRECISION)
				return (t);
		}
	}
	return (-1);
}

static inline void		continue_intersection(t_ray *r, t_equation n,
											double *cap, t_limited_cone *cn)
{
	t_disc ttm[2];

	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	cap[3] = -1;
	if (quadratic_equation(&n))
	{
		cap[0] = check_cone_limits(n.root[0], r, cn);
		cap[1] = check_cone_limits(n.root[1], r, cn);
	}
	if (cn->caps == ON)
	{
		ttm[0].pos = cn->p1;
		ttm[0].norm = cn->p1_norm;
		ttm[0].r = cn->r1;
		intersection_disc(r, &ttm[0], &cap[2], 0);
		ttm[1].pos = cn->p2;
		ttm[1].norm = cn->p2_norm;
		ttm[1].r = cn->r2;
		intersection_disc(r, &ttm[1], &cap[3], 0);
	}
}

int						intersection_limited_cone(t_ray *r, void *cone,
													double *t, double *z)
{
	t_limited_cone	*cn;
	t_vect			tmp[3];
	double			cap[4];
	t_equation		n;

	(void)z;
	cn = (t_limited_cone *)cone;
	tmp[0] = vector_mult(vector_dot_product(&r->dir, &cn->dir), &cn->dir);
	tmp[0] = vector_substract(&r->dir, &tmp[0]);
	n.a = pow(cos(cn->rad), 2) * vector_dot_product(&tmp[0], &tmp[0]) -
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&r->dir, &cn->dir), 2);
	tmp[2] = vector_substract(&r->origin, &cn->pos);
	tmp[1] = vector_mult(vector_dot_product(&tmp[2], &cn->dir), &cn->dir);
	tmp[1] = vector_substract(&tmp[2], &tmp[1]);
	n.b = 2 * pow(cos(cn->rad), 2) * vector_dot_product(&tmp[0], &tmp[1]) -
			2 * pow(sin(cn->rad), 2) * vector_dot_product(&r->dir, &cn->dir) *
				vector_dot_product(&tmp[2], &cn->dir);
	n.c = pow(cos(cn->rad), 2) * vector_dot_product(&tmp[1], &tmp[1]) -
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&tmp[2], &cn->dir), 2);
	continue_intersection(r, n, cap, cn);
	return (check_solving(t, select_value(cap, 4)));
}
