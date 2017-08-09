/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/06/06 18:10:52 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		intersection_cylinder(t_ray *r, void *c, double *t)
{
	t_cylinder	*cyl;
	t_vect		tm1;
	t_vect		tm2;
	t_vect		delta;
	t_equation	n;

	cyl = (t_cylinder *)c;
	tm1 = vector_mult(vector_dot_product(&r->dir, &cyl->dir), &cyl->dir);
	tm1 = vector_substract(&r->dir, &tm1);
	n.a = vector_dot_product(&tm1, &tm1);
	delta = vector_substract(&r->origin, &cyl->pos);
	tm2 = vector_mult(vector_dot_product(&delta, &cyl->dir), &cyl->dir);
	tm2 = vector_substract(&delta, &tm2);
	n.b = 2 * vector_dot_product(&tm1, &tm2);
	n.c = vector_dot_product(&tm2, &tm2) - pow(cyl->r, 2);
	return (quadratic_equation(&n, t));
}

int		intersection_plane(t_ray *r, void *plane, double *t)
{
	t_plane *p;
	double	t0;
	int		i;
	t_vect	tmp;

	p = (t_plane *)plane;
	i = 0;
	if (vector_dot_product(&p->norm, &r->dir) != 0)
	{
		tmp = vector_substract(&p->point, &r->origin);
		t0 = vector_dot_product(&p->norm, &tmp) / \
			vector_dot_product(&p->norm, &r->dir);
		if (t0 > 0.00001f)
		{
			i = 1;
			*t = t0;
		}
	}
	return (i);
}

int		intersection_cone(t_ray *r, void *cone, double *t)
{
	t_cone		*cn;
	t_vect		tm1;
	t_vect		tm2;
	t_vect		delta;
	t_equation	n;

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
	return (quadratic_equation(&n, t));
}

int		intersection_sphere(t_ray *r, void *sphere, double *t)
{
	t_vect		dist;
	t_equation	n;
	t_sphere	*s;

	s = (t_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
	return (quadratic_equation(&n, t));
}
