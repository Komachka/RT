/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:17:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 15:17:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

#define T 0
#define Q 1
#define P 2

int	intersection_triangle(t_ray *r, void *triangle, double *t, double *z)
{
	t_triangle		*tr;
	t_quartic_eq	tmp;
	t_vect			vec[3];

	(void)z;
	tr = (t_triangle *)triangle;
	vec[P] = vector_cross_product(&r->dir, &tr->v1);
	tmp.d = vector_dot_product(&tr->v0, &vec[P]);
	if (fabs(tmp.d) > PRECISION)
	{
		tmp.d = 1.0 / tmp.d;
		vec[T] = vector_substract(&r->origin, &tr->a);
		tmp.u = vector_dot_product(&vec[T], &vec[P]) * tmp.d;
		if (tmp.u < 0.0f || tmp.u > 1.0f)
			return (0);
		vec[Q] = vector_cross_product(&vec[T], &tr->v0);
		tmp.v = vector_dot_product(&r->dir, &vec[Q]) * tmp.d;
		if (tmp.v < 0.0f || tmp.u + tmp.v > 1.0f)
			return (0);
		tmp.a = vector_dot_product(&tr->v1, &vec[Q]) * tmp.d;
		return (check_solving(t, tmp.a));
	}
	return (0);
}

int	intersection_ellipsoid(t_ray *r, void *ellipsoid, double *t, double *z)
{
	t_ellipsoid	*e;
	t_equation	n;
	int			res;

	(void)z;
	e = (t_ellipsoid *)ellipsoid;
	n.a = ((r->dir.x * r->dir.x) / (e->size_x * e->size_x)) + ((r->dir.y
			* r->dir.y) / (e->size_y * e->size_y)) + ((r->dir.z
			* r->dir.z) / (e->size_z * e->size_z));
	n.b = (2.0 * (r->origin.x - e->pos.x) * r->dir.x) / (e->size_x *
			e->size_x) + (2.0 * (r->origin.y - e->pos.y) * r->dir.y) /
			(e->size_y * e->size_y) + (2.0 * (r->origin.z - e->pos.z) *
			r->dir.z) / (e->size_z * e->size_z);
	n.c = (pow((r->origin.x - e->pos.x), 2) / (e->size_x * e->size_x)) +
			(pow((r->origin.y - e->pos.y), 2) / (e->size_y * e->size_y)) +
			(pow((r->origin.z - e->pos.z), 2) / (e->size_z * e->size_z)) - 1.0f;
	if ((res = quadratic_equation(&n)))
		return (check_solving(t, select_value(n.root, res)));
	return (0);
}

int	intersection_paraboloid(t_ray *r, void *paraboloid, double *t, double *z)
{
	t_paraboloid	*p;
	t_equation		n;
	t_vect			x;
	int				res;

	(void)z;
	p = (t_paraboloid *)paraboloid;
	x = vector_substract(&r->origin, &p->extremum);
	n.a = vector_dot_product(&r->dir, &r->dir) -
			pow(vector_dot_product(&r->dir, &p->dir), 2);
	n.b = 2 * (vector_dot_product(&r->dir, &x) -
			vector_dot_product(&r->dir, &p->dir) *
					(vector_dot_product(&x, &p->dir) + 2 * p->k));
	n.c = vector_dot_product(&x, &x) -
			vector_dot_product(&x, &p->dir) *
					(vector_dot_product(&x, &p->dir) + 4 * p->k);
	if ((res = quadratic_equation(&n)))
		return (check_solving(t, select_value(n.root, res)));
	return (0);
}

int	intersection_disc(t_ray *r, void *disc, double *t, double *z)
{
	t_disc	*d;
	double	t0;
	t_vect	point;
	t_vect	tmp;

	d = (t_disc *)disc;
	(void)z;
	if (vector_dot_product(&d->norm, &r->dir) != 0)
	{
		point = vector_substract(&d->pos, &r->origin);
		t0 = vector_dot_product(&d->norm, &point) /
				vector_dot_product(&d->norm, &r->dir);
		tmp = intersection_point(t0, r);
		tmp = vector_substract(&tmp, &d->pos);
		if (vector_length(&tmp) <= d->r)
			return (check_solving(t, t0));
	}
	return (0);
}
