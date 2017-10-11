/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 17:39:45 by askochul         ###   ########.fr       */
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

int		intersection_torus(t_ray *ray, void *tr, double *tt)
{
	t_torus			*tor;
	t_vect			tmp2;
	t_quartic_eq	n;
	t_vect			q;
	t_tor t;

	tor = (t_torus *)tr;
	q = vector_substract(&ray->origin, &tor->pos);
	t.u = vector_dot_product(&tor->dir, &q);
	t.v = vector_dot_product(&tor->dir, &ray->dir);
	t.a = 1.0 - t.v * t.v;
	t.b = 2.0 * (vector_dot_product(&q, &ray->dir) - t.u * t.v);
	t.c = vector_dot_product(&q, &q) - t.u * t.u;
	t.d = vector_dot_product(&q, &q) + tor->maj_r *\
		tor->maj_r - tor->min_r * tor->min_r;
	n.a = 1.0;
	tmp2 = vector_mult(4.0, &q);
	n.b = vector_dot_product(&tmp2, &ray->dir);
	n.c = 2.0 * t.d + (n.b * n.b) / 4.0 - 4.0 * tor->maj_r * tor->maj_r * t.a;
	n.d = n.b * t.d - 4.0 * tor->maj_r * tor->maj_r * t.b;
	n.e = t.d * t.d - 4.0 * tor->maj_r * tor->maj_r * t.c;
	return (check_solving(tt, select_value(n.root, quartic_equation(&n))));
}

int		intersection_triangle(t_ray *r, void *triangle, double *t)
{
	t_triangle	*tr;
	t_vect tm[3];
	double u[2];
	double		det;
	double		t0;
	
	tr = (t_triangle *)triangle;
	tm[0] = vector_cross_product(&r->dir, &tr->v1);
	det = vector_dot_product(&tr->v0, &tm[0]);
	if (fabs(det) > PRECISION)
	{
		det = 1.0 / det;
		tm[1] = vector_substract(&r->origin, &tr->a);
		u[0] = vector_dot_product(&tm[1], &tm[0]) * det;
		if (u[0] < 0.0f || u[0] > 1.0f)
			return (0);
		tm[2] = vector_cross_product(&tm[1], &tr->v0);
		u[1] = vector_dot_product(&r->dir, &tm[2]) * det;
		if (u[1] < 0.0f || u[0] + u[1] > 1.0f)
			return (0);
		t0 = vector_dot_product(&tr->v1, &tm[2]) * det;
		return (check_solving(t, t0));
	}
	return (0);
}

int		intersection_cylinder(t_ray *r, void *c, double *t)
{
	t_cylinder	*cyl;
	t_vect		tmp[2];
	t_vect		delta;
	t_equation	n;
	int			res;

	cyl = (t_cylinder *)c;
	tmp[0] = vector_mult(vector_dot_product(&r->dir, &cyl->dir), &cyl->dir);
	tmp[0] = vector_substract(&r->dir, &tmp[0]);
	n.a = vector_dot_product(&tmp[0], &tmp[0]);
	delta = vector_substract(&r->origin, &cyl->pos);
	tmp[1] = vector_mult(vector_dot_product(&delta, &cyl->dir), &cyl->dir);
	tmp[1] = vector_substract(&delta, &tmp[1]);
	n.b = 2 * vector_dot_product(&tmp[0], &tmp[1]);
	n.c = vector_dot_product(&tmp[1], &tmp[1]) - pow(cyl->r, 2);
	if ((res = quadratic_equation(&n)))
		return (check_solving(t, select_value(n.root, res)));
	return (0);
}

int		intersection_plane(t_ray *r, void *plane, double *t)
{
	t_plane *p;
	double	t0;
	t_vect	point;

	p = (t_plane *)plane;
	if (vector_dot_product(&p->norm, &r->dir) != 0)
	{
		point = vector_substract(&p->point, &r->origin);
		t0 = vector_dot_product(&p->norm, &point) / \
			vector_dot_product(&p->norm, &r->dir);
		return (check_solving(t, t0));
	}
	return (0);
}
