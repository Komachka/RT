/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:35:30 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:25:52 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect		disc_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect	norm;
	t_disc	*d;

	(void)a;
	d = (t_disc *)obj;
	if (vector_dot_product(&d->norm, point) > PRECISION)
		norm = change_vector_direction(&d->norm);
	else
		norm = d->norm;
	return (norm);
}

t_vect		plane_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect	norm;
	t_plane	*p;

	(void)a;
	p = (t_plane *)obj;
	if (vector_dot_product(&p->norm, point) > PRECISION)
		norm = change_vector_direction(&p->norm);
	else
		norm = p->norm;
	return (norm);
}

t_vect		plane_with_hole_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect				norm;
	t_plane_with_hole	*p;

	(void)a;
	p = (t_plane_with_hole *)obj;
	if (vector_dot_product(&p->norm, point) > PRECISION)
		norm = change_vector_direction(&p->norm);
	else
		norm = p->norm;
	return (norm);
}

t_vect		cylinder_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_vect		tmp1;
	t_vect		tmp2;
	t_cylinder	*c;

	(void)a;
	c = (t_cylinder *)obj;
	tmp1 = vector_substract(point, &c->pos);
	tmp2 = vector_mult(vector_dot_product(&tmp1, &c->dir), &c->dir);
	norm = vector_substract(&tmp1, &tmp2);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		limited_paraboloid_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect					norm;
	t_paraboloid			t;
	t_limited_paraboloid	*p;

	a = 0;
	p = (t_limited_paraboloid *)obj;
	t.extremum = p->extremum;
	t.dir = p->dir;
	t.k = p->k;
	norm = paraboloid_norm_vector(&t, point, a);
	return (norm);
}
