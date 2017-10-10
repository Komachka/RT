/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:35:30 by askochul          #+#    #+#             */
/*   Updated: 2017/09/28 16:35:54 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect		disc_norm_vector(void *obj, t_vect *point)
{
	t_vect	norm;
	t_disc	*d;

	d = (t_disc *)obj;
	if (vector_dot_product(&d->norm, point) > PRECISION)
		norm = change_vector_direction(&d->norm);
	else
		norm = d->norm;
	return (norm);
}

t_vect		plane_norm_vector(void *obj, t_vect *point)
{
	t_vect	norm;
	t_plane	*p;

	p = (t_plane *)obj;
	if (vector_dot_product(&p->norm, point) > PRECISION)
		norm = change_vector_direction(&p->norm);
	else
		norm = p->norm;
	return (norm);
}

t_vect		cylinder_norm_vector(void *obj, t_vect *point)
{
	t_vect		norm;
	t_vect		tmp1;
	t_vect		tmp2;
	t_cylinder	*c;

	c = (t_cylinder *)obj;
	tmp1 = vector_substract(point, &c->pos);
	tmp2 = vector_mult(vector_dot_product(&tmp1, &c->dir), &c->dir);
	norm = vector_substract(&tmp1, &tmp2);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		limited_paraboloid_norm_vector(void *obj, t_vect *point)
{
	t_vect					norm;
	t_paraboloid			t;
	t_limited_paraboloid	*p;

	p = (t_limited_paraboloid *)obj;
	t.extremum = p->extremum;
	t.dir = p->dir;
	t.k = p->k;
	norm = paraboloid_norm_vector(&t, point);
	return (norm);
}

t_vect		limited_cylinder_norm_vector(void *obj, t_vect *point)
{
	t_vect				norm;
	t_limited_cylinder	*c;
	t_vect				tmp;
	t_cylinder			cl;

	c = (t_limited_cylinder *)obj;
	if (c->caps == ON)
	{
		tmp = vector_substract(point, &c->p1);
		if (vector_length(&tmp) <= c->r)
			return (c->p1_norm);
		tmp = vector_substract(point, &c->p2);
		if (vector_length(&tmp) <= c->r)
			return (c->p2_norm);
	}
	cl.pos = c->p1;
	cl.dir = c->dir;
	cl.r = c->r;
	norm = cylinder_norm_vector(&cl, point);
	return (norm);
}
