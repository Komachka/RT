/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 16:41:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 16:41:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline double	check_sphere_limits(double t, t_ray *r,
											t_limited_sphere *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->p1);
		tmp[1] = vector_substract(&point, &c->p2);
		if (vector_dot_product(&c->cut_dir, &tmp[0]) < PRECISION &&
				vector_dot_product(&c->cut_dir, &tmp[1]) > PRECISION)
			return (t);
	}
	return (-1);
}

static inline void		continue_intersection(t_ray *r, t_equation n,
										double *cap, t_limited_sphere *s)
{
	t_disc				ttm;

	if (quadratic_equation(&n))
	{
		cap[0] = check_sphere_limits(n.root[0], r, s);
		cap[1] = check_sphere_limits(n.root[1], r, s);
	}
	if (s->caps == ON)
	{
		ttm.pos = s->p1;
		ttm.norm = s->cut_dir;
		ttm.r = s->cut_r;
		intersection_disc(r, &ttm, &cap[2], 0);
	}
}

int						intersection_limited_sphere(t_ray *r, void *sphere,
													double *t, double *z)
{
	t_vect				dist;
	t_equation			n;
	t_limited_sphere	*s;
	double				cap[4];

	(void)z;
	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	s = (t_limited_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
	continue_intersection(r, n, cap, s);
	return (check_solving(t, select_value(cap, 3)));
}
