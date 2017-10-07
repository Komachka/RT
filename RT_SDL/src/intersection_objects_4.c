/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/02 16:05:49 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double	check_paraboloid_limits(double t, t_ray *r, t_limited_paraboloid *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->extremum);
		tmp[1] = vector_substract(&point, &c->bottom);
		if (vector_dot_product(&c->dir, &tmp[0]) > PRECISION
				&& vector_dot_product(&c->dir, &tmp[1]) < PRECISION)
			return (t);
	}
	return (-1);
}

int				intersection_limited_paraboloid(t_ray *r, void *paraboloid, double *t)
{
	t_limited_paraboloid	*p;
	t_equation				n;
	t_vect					x;
	double					cap[2];
	double					t0;

	cap[0] = -1;
	cap[1] = -1;
	p = (t_limited_paraboloid *)paraboloid;
	x = vector_substract(&r->origin, &p->extremum);
	n.a = vector_dot_product(&r->dir, &r->dir)
		- pow(vector_dot_product(&r->dir, &p->dir), 2);
	n.b = 2 * (vector_dot_product(&r->dir, &x) -
			vector_dot_product(&r->dir, &p->dir) *
			(vector_dot_product(&x, &p->dir) + 2 * p->k));
	n.c = vector_dot_product(&x, &x) - vector_dot_product(&x, &p->dir) *
		(vector_dot_product(&x, &p->dir) + 4 * p->k);
	if (quadratic_equation(&n))
	{
		cap[0] = check_paraboloid_limits(n.root[0], r, p);
		cap[1] = check_paraboloid_limits(n.root[1], r, p);
	}
	t0 = select_value(cap, 2);
	return (check_solving(t, t0));
}

double	check_sphere_limits(double t, t_ray *r, t_limited_sphere *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->p1);
		tmp[1] = vector_substract(&point, &c->p2);
		if (vector_dot_product(&c->cut_dir, &tmp[0]) < PRECISION
				&& vector_dot_product(&c->cut_dir, &tmp[1]) > PRECISION)
			return (t);
	}
	return (-1);
}

int				intersection_limited_sphere(t_ray *r, void *sphere, double *t)
{
	t_vect				dist;
	t_equation			n;
	t_limited_sphere	*s;
	double				cap[4];
	t_disс				ttm;

	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	s = (t_limited_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
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
		intersection_disc(r, &ttm, &cap[2]);
	}
	return (check_solving(t, select_value(cap, 3)));
}

int		intersection_plane_with_hole(t_ray *r, void *obj, double *t)
{
	t_plane_with_hole *p;
	double	t0;
	t_vect	point;
	int i;

	i = -1;
	p = (t_plane_with_hole *)obj;
	if (vector_dot_product(&p->norm, &r->dir) != 0)
	{
		while (++i < p->holes_num)
			if (intersection_disc(r, &p->hole[i], &t0))
				return(0);
		point = vector_substract(&p->point, &r->origin);
		t0 = vector_dot_product(&p->norm, &point) / \
			vector_dot_product(&p->norm, &r->dir);
		return(check_solving(t, t0));
	}
	return (0);
}