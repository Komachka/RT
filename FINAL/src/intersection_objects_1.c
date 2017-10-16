/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 15:16:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 15:16:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int	intersection_sphere(t_ray *r, void *sphere, double *t, double *z)
{
	t_vect		dist;
	t_equation	n;
	t_sphere	*s;
	int			res;

	(void)z;
	s = (t_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
	if ((res = quadratic_equation(&n)))
		return (check_solving(t, select_value(n.root, res)));
	return (0);
}

int	intersection_plane(t_ray *r, void *plane, double *t, double *z)
{
	t_plane	*p;
	double	t0;
	t_vect	point;

	(void)z;
	p = (t_plane *)plane;
	if (vector_dot_product(&p->norm, &r->dir) != 0)
	{
		point = vector_substract(&p->point, &r->origin);
		t0 = vector_dot_product(&p->norm, &point) /
				vector_dot_product(&p->norm, &r->dir);
		return (check_solving(t, t0));
	}
	return (0);
}

int	intersection_cylinder(t_ray *r, void *c, double *t, double *z)
{
	t_cylinder	*cyl;
	t_vect		tmp[2];
	t_vect		delta;
	t_equation	n;
	int			res;

	(void)z;
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

int	intersection_cone(t_ray *r, void *cone, double *t, double *z)
{
	t_cone		*cn;
	t_vect		tm[2];
	t_vect		delta;
	t_equation	n;
	int			res;

	(void)z;
	cn = (t_cone *)cone;
	tm[0] = vector_mult(vector_dot_product(&r->dir, &cn->dir), &cn->dir);
	tm[0] = vector_substract(&r->dir, &tm[0]);
	n.a = pow(cos(cn->rad), 2) * vector_dot_product(&tm[0], &tm[0]) -
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&r->dir, &cn->dir), 2);
	delta = vector_substract(&r->origin, &cn->pos);
	tm[1] = vector_mult(vector_dot_product(&delta, &cn->dir), &cn->dir);
	tm[1] = vector_substract(&delta, &tm[1]);
	n.b = 2 * pow(cos(cn->rad), 2) * vector_dot_product(&tm[0], &tm[1]) -
			2 * pow(sin(cn->rad), 2) * vector_dot_product(&r->dir, &cn->dir) *
					vector_dot_product(&delta, &cn->dir);
	n.c = pow(cos(cn->rad), 2) * vector_dot_product(&tm[1], &tm[1]) -
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&delta, &cn->dir), 2);
	if ((res = quadratic_equation(&n)))
		return (check_solving(t, select_value(n.root, res)));
	return (0);
}

int	intersection_torus(t_ray *ray, void *tr, double *t, double *z)
{
	t_torus			*tor;
	t_vect			tmp2;
	int				res;
	t_quartic_eq	n[2];
	t_vect			q;

	(void)z;
	tor = (t_torus *)tr;
	q = vector_substract(&ray->origin, &tor->pos);
	n[1].u = vector_dot_product(&tor->dir, &q);
	n[1].v = vector_dot_product(&tor->dir, &ray->dir);
	n[1].a = 1 - n[1].v * n[1].v;
	n[1].b = 2 * (vector_dot_product(&q, &ray->dir) - n[1].u * n[1].v);
	n[1].c = vector_dot_product(&q, &q) - n[1].u * n[1].u;
	n[1].d = vector_dot_product(&q, &q) + tor->maj_r *
			tor->maj_r - tor->min_r * tor->min_r;
	n[0].a = 1;
	tmp2 = vector_mult(4, &q);
	n[0].b = vector_dot_product(&tmp2, &ray->dir);
	n[0].c = 2 * n[1].d + (n[0].b * n[0].b) /
			4 - 4 * tor->maj_r * tor->maj_r * n[1].a;
	n[0].d = n[0].b * n[1].d - 4 * tor->maj_r * tor->maj_r * n[1].b;
	n[0].e = n[1].d * n[1].d - 4 * tor->maj_r * tor->maj_r * n[1].c;
	return ((res = quartic_equation(&n[0])) ?
			check_solving(t, select_value(n[0].root, res)) : 0);
}
