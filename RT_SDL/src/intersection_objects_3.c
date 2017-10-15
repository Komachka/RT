/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 22:12:32 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double	check_cylinder_limits(double t, t_ray *r, t_limited_cylinder *c)
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

int		intersection_limited_cylinder(t_ray *r, void *cyl, double *t, double *z)
{
	t_limited_cylinder	*c;
	t_vect				tmp[2];
	t_vect				delta;
	double				t0;
	t_equation			n;
	int					res;
	double				cap[4];
	t_disc				ttm[2];

	z = 0;
	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	cap[3] = -1;
	c = (t_limited_cylinder *)cyl;
	tmp[0] = vector_mult(vector_dot_product(&r->dir, &c->dir), &c->dir);
	tmp[0] = vector_substract(&r->dir, &tmp[0]);
	n.a = vector_dot_product(&tmp[0], &tmp[0]);
	delta = vector_substract(&r->origin, &c->p1);
	tmp[1] = vector_mult(vector_dot_product(&delta, &c->dir), &c->dir);
	tmp[1] = vector_substract(&delta, &tmp[1]);
	n.b = 2 * vector_dot_product(&tmp[0], &tmp[1]);
	n.c = vector_dot_product(&tmp[1], &tmp[1]) - pow(c->r, 2);
	if ((res = quadratic_equation(&n)))
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
	t0 = select_value(cap, 4);
	return (check_solving(t, t0));
}

double	check_cone_limits(double t, t_ray *r, t_limited_cone *c)
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

int		intersection_limited_cone(t_ray *r, void *cone, double *t, double *z)
{
	t_limited_cone	*cn;
	t_vect			tmp[2];
	t_vect			delta;
	double			t0;
	t_equation		n;
	double			cap[4];
	t_disc			ttm[2];

	z = 0;
	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	cap[3] = -1;
	cn = (t_limited_cone *)cone;
	tmp[0] = vector_mult(vector_dot_product(&r->dir, &cn->dir), &cn->dir);
	tmp[0] = vector_substract(&r->dir, &tmp[0]);
	n.a = pow(cos(cn->rad), 2) * vector_dot_product(&tmp[0], &tmp[0]) - \
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&r->dir, &cn->dir), 2);
	delta = vector_substract(&r->origin, &cn->pos);
	tmp[1] = vector_mult(vector_dot_product(&delta, &cn->dir), &cn->dir);
	tmp[1] = vector_substract(&delta, &tmp[1]);
	n.b = 2 * pow(cos(cn->rad), 2) * vector_dot_product(&tmp[0], &tmp[1]) - \
			2 * pow(sin(cn->rad), 2) * vector_dot_product(&r->dir, &cn->dir) * \
				vector_dot_product(&delta, &cn->dir);
	n.c = pow(cos(cn->rad), 2) * vector_dot_product(&tmp[1], &tmp[1]) - \
			pow(sin(cn->rad), 2) * pow(vector_dot_product(&delta, &cn->dir), 2);
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
	t0 = select_value(cap, 4);
	return (check_solving(t, t0));
}
