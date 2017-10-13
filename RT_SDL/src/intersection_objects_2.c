/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 17:39:40 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		intersection_disc(t_ray *r, void *disc, double *t, double *z)
{
	t_disc *d;
	double	t0;
	t_vect	point;
	t_vect tmp;

	d = (t_disc *)disc;
	z = 0;
	if (vector_dot_product(&d->norm, &r->dir) != 0)
	{
		point = vector_substract(&d->pos, &r->origin);
		t0 = vector_dot_product(&d->norm, &point) / \
			vector_dot_product(&d->norm, &r->dir);
		tmp = intersection_point(t0, r);
		tmp = vector_substract(&tmp, &d->pos);
		if (vector_length(&tmp) <= d->r)
				return(check_solving(t, t0));
	}
	return (0);
}

int		intersection_cone(t_ray *r, void *cone, double *t, double *z)
{
	t_cone		*cn;
	t_vect		tm1;
	t_vect		tm2;
	t_vect		delta;
	t_equation	n;
	int res;

	z = 0;
	cn = (t_cone *)cone;
	tm1 = vector_mult(vector_dot_product(&r->dir, &cn->dir), &cn->dir);
	tm1 = vector_substract(&r->dir, &tm1);
	n.a = pow(cos(cn->rad), 2) * vector_dot_product(&tm1, &tm1) - \
		pow(sin(cn->rad), 2) * pow(vector_dot_product(&r->dir, &cn->dir), 2);
	delta = vector_substract(&r->origin, &cn->pos);
	tm2 = vector_mult(vector_dot_product(&delta, &cn->dir), &cn->dir);
	tm2 = vector_substract(&delta, &tm2);
	n.b = 2 * pow(cos(cn->rad), 2) * vector_dot_product(&tm1, &tm2) - \
			2 * pow(sin(cn->rad), 2) * vector_dot_product(&r->dir, &cn->dir) * \
				vector_dot_product(&delta, &cn->dir);
	n.c = pow(cos(cn->rad), 2) * vector_dot_product(&tm2, &tm2) - \
			pow(sin(cn->rad), 2) * pow(vector_dot_product(&delta, &cn->dir), 2);
	if ((res = quadratic_equation(&n)))
		return(check_solving(t, select_value(n.root, res)));
	return (0);
}

int		intersection_sphere(t_ray *r, void *sphere, double *t, double *z)
{
	t_vect		dist;
	t_equation	n;
	t_sphere	*s;
	int res;

	z = 0;
	s = (t_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
	if ((res = quadratic_equation(&n)))
		return(check_solving(t, select_value(n.root, res)));
	return (0);
}

int		intersection_ellipsoid(t_ray *r, void *ellipsoid, double *t, double *z)
{
	t_ellipsoid	*e;
	t_equation	n;
	int res;

	z = 0;
	e = (t_ellipsoid *)ellipsoid;
 	n.a = ((r->dir.x * r->dir.x )/ (e->size_x * e->size_x)) + ((r->dir.y * r->dir.y) / (e->size_y * e->size_y)) + ((r->dir.z * r->dir.z )/ (e->size_z * e->size_z));
 	n.b = (2.0 * (r->origin.x - e->pos.x) * r->dir.x ) / (e->size_x * e->size_x) + (2.0 * (r->origin.y - e->pos.y) * r->dir.y ) / (e->size_y * e->size_y) + (2.0 * (r->origin.z - e->pos.z) * r->dir.z ) / (e->size_z * e->size_z);
 	n.c = (pow((r->origin.x - e->pos.x), 2) / (e->size_x * e->size_x)) +(pow((r->origin.y - e->pos.y), 2) / (e->size_y * e->size_y)) + (pow((r->origin.z - e->pos.z), 2) / (e->size_z * e->size_z)) - 1.0f;

 	if ((res = quadratic_equation(&n)))
		return(check_solving(t, select_value(n.root, res)));
	return (0);
}

int		intersection_paraboloid(t_ray *r, void *paraboloid, double *t, double *z)
{
	t_paraboloid *p;
	t_equation	n;
	t_vect x;
	int res;

	z = 0;
	p = (t_paraboloid *)paraboloid;
	x = vector_substract(&r->origin, &p->extremum);
	n.a = vector_dot_product(&r->dir, &r->dir) - pow(vector_dot_product(&r->dir, &p->dir), 2);
	n.b = 2 * (vector_dot_product(&r->dir, &x) - vector_dot_product(&r->dir, &p->dir)*(vector_dot_product(&x, &p->dir) + 2 * p->k));
	n.c = vector_dot_product(&x, &x) - vector_dot_product(&x, &p->dir) * (vector_dot_product(&x, &p->dir) + 4 * p->k);
 	if ((res = quadratic_equation(&n)))
		return(check_solving(t, select_value(n.root, res)));
	return (0);
}
