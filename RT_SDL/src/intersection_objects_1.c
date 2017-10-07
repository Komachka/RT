/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/02 15:41:02 by askochul         ###   ########.fr       */
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

int		intersection_torus(t_ray *ray, void *tr, double *t)
{
	t_torus			*tor;
	t_vect			tmp2;
	int				res;
	t_quartic_eq	n;
	t_vect			q;
	double			u;
	double			v;
	double			a;
	double			b;
	double			c;
	double			d;

	tor = (t_torus *)tr;
	q = vector_substract(&ray->origin, &tor->pos);
	u = vector_dot_product(&tor->dir, &q);
	v = vector_dot_product(&tor->dir, &ray->dir);
	a = 1 - v * v;
	b = 2 * (vector_dot_product(&q, &ray->dir) - u * v);
	c = vector_dot_product(&q, &q) - u * u;
	d = vector_dot_product(&q, &q) + tor->maj_r *\
		tor->maj_r - tor->min_r * tor->min_r;
	n.a = 1;
	tmp2 = vector_mult(4, &q);
	n.b = vector_dot_product(&tmp2, &ray->dir);
	n.c = 2 * d + (n.b * n.b) / 4 - 4 * tor->maj_r * tor->maj_r * a;
	n.d = n.b * d - 4 * tor->maj_r * tor->maj_r * b;
	n.e = d * d - 4 * tor->maj_r * tor->maj_r * c;
	if ((res = quartic_equation(&n)))
		return (check_solving(t, select_value(n.root, res)));
	return (0);
}

int		intersection_triangle(t_ray *r, void *triangle, double *t)
{
	t_triangle	*tr;
	double		det;
	double		u;
	double		v;
	t_vect		tvec;
	t_vect		qvec;
	double		t0;
	t_vect		pvec;

	tr = (t_triangle *)triangle;
	pvec = vector_cross_product(&r->dir, &tr->v1);
	det = vector_dot_product(&tr->v0, &pvec);
	if (fabs(det) > PRECISION)
	{
		det = 1.0 / det;
		tvec = vector_substract(&r->origin, &tr->a);
		u = vector_dot_product(&tvec, &pvec) * det;
		if (u < 0.0f || u > 1.0f)
			return (0);
		qvec = vector_cross_product(&tvec, &tr->v0);
		v = vector_dot_product(&r->dir, &qvec) * det;
		if (v < 0.0f || u + v > 1.0f)
			return (0);
		t0 = vector_dot_product(&tr->v1, &qvec) * det;
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
