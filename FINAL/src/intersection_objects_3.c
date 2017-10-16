/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:30:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 15:30:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline double	check_cylinder_limits(double t, t_ray *r,
											t_limited_cylinder *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->p1);
		tmp[1] = vector_substract(&point, &c->p2);
		if (vector_dot_product(&c->dir, &tmp[0]) > PRECISION &&
				vector_dot_product(&c->dir, &tmp[1]) < PRECISION)
			return (t);
	}
	return (-1);
}

static inline void		continue_intersection(t_ray *r, t_equation n,
											double *cap, t_limited_cylinder *c)
{
	t_disc				ttm[2];

	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	cap[3] = -1;
	if (quadratic_equation(&n))
	{
		cap[0] = check_cylinder_limits(n.root[0], r, c);
		cap[1] = check_cylinder_limits(n.root[1], r, c);
	}
	if (c->caps == ON)
	{
		ttm[0].pos = c->p1;
		ttm[0].norm = c->p1_norm;
		ttm[0].r = c->r;
		intersection_disc(r, &ttm[0], &cap[2], 0);
		ttm[1].pos = c->p2;
		ttm[1].norm = c->p2_norm;
		ttm[1].r = c->r;
		intersection_disc(r, &ttm[1], &cap[3], 0);
	}
}

int						intersection_limited_cylinder(t_ray *r, void *cyl,
														double *t, double *z)
{
	t_limited_cylinder	*c;
	t_vect				tmp[3];
	t_equation			n;
	double				cap[4];

	(void)z;
	c = (t_limited_cylinder *)cyl;
	tmp[0] = vector_mult(vector_dot_product(&r->dir, &c->dir), &c->dir);
	tmp[0] = vector_substract(&r->dir, &tmp[0]);
	n.a = vector_dot_product(&tmp[0], &tmp[0]);
	tmp[2] = vector_substract(&r->origin, &c->p1);
	tmp[1] = vector_mult(vector_dot_product(&tmp[2], &c->dir), &c->dir);
	tmp[1] = vector_substract(&tmp[2], &tmp[1]);
	n.b = 2 * vector_dot_product(&tmp[0], &tmp[1]);
	n.c = vector_dot_product(&tmp[1], &tmp[1]) - pow(c->r, 2);
	continue_intersection(r, n, cap, c);
	return (check_solving(t, select_value(cap, 4)));
}
