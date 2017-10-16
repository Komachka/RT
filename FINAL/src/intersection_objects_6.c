/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_6.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkolomiy <pkolomiy@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/15 17:31:00 by pkolomiy          #+#    #+#             */
/*   Updated: 2017/10/15 17:31:00 by pkolomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static inline double	check_paraboloid_limits(double t, t_ray *r,
												t_limited_paraboloid *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->extremum);
		tmp[1] = vector_substract(&point, &c->bottom);
		if (vector_dot_product(&c->dir, &tmp[0]) > PRECISION &&
				vector_dot_product(&c->dir, &tmp[1]) < PRECISION)
			return (t);
	}
	return (-1);
}

int						intersection_limited_paraboloid(t_ray *r,
										void *paraboloid, double *t, double *z)
{
	t_limited_paraboloid	*p;
	t_equation				n;
	t_vect					x;
	double					cap[2];

	(void)z;
	cap[0] = -1;
	cap[1] = -1;
	p = (t_limited_paraboloid *)paraboloid;
	x = vector_substract(&r->origin, &p->extremum);
	n.a = vector_dot_product(&r->dir, &r->dir) -
			pow(vector_dot_product(&r->dir, &p->dir), 2);
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
	return (check_solving(t, select_value(cap, 2)));
}

int						intersection_plane_with_hole(t_ray *r, void *obj,
														double *t, double *z)
{
	t_plane_with_hole	*p;
	double				t0;
	t_vect				point;
	int					i;

	(void)z;
	i = -1;
	p = (t_plane_with_hole *)obj;
	if (vector_dot_product(&p->norm, &r->dir) != 0)
	{
		while (++i < p->holes_num)
			if (intersection_disc(r, &p->hole[i], &t0, 0))
				return (0);
		point = vector_substract(&p->point, &r->origin);
		t0 = vector_dot_product(&p->norm, &point) /
				vector_dot_product(&p->norm, &r->dir);
		return (check_solving(t, t0));
	}
	return (0);
}

int						intersection_disc_with_hole(t_ray *r, void *obj,
													double *t, double *z)
{
	t_disc_with_hole	*p;
	double				t0;

	(void)z;
	p = (t_disc_with_hole *)obj;
	if (intersection_disc(r, &p->disc, &t0, 0))
	{
		if (intersection_disc(r, &p->hole, &t0, 0))
			return (0);
		return (check_solving(t, t0));
	}
	return (0);
}

int						intersection_polygon(t_ray *ray, void *obj, double *t,
																	double *z)
{
	t_polygon	*p;
	t_triangle	tr;
	double		tt;

	p = (t_polygon *)obj;
	VAR_INT(k, 0);
	VAR_INT(i, -1);
	tt = INFINITY;
	while (++i < p->faces)
	{
		tr.a = p->vx[p->index[i * 3]];
		tr.b = p->vx[p->index[i * 3 + 1]];
		tr.c = p->vx[p->index[i * 3 + 2]];
		tr.v0 = vector_substract(&tr.b, &tr.a);
		tr.v1 = vector_substract(&tr.c, &tr.a);
		tr.norm = p->norm[i];
		if (intersection_triangle(ray, &tr, &tt, 0))
			if (tt < *t)
			{
				k = 1;
				*z = i;
				*t = tt;
			}
	}
	return (k);
}
