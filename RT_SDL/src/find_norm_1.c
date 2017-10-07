/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 20:35:50 by kzahreba          #+#    #+#             */
/*   Updated: 2017/09/28 16:35:16 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect		triangle_norm_vector(void *obj, t_vect *point)
{
	t_vect		norm;
	t_triangle	*tr;

	tr = (t_triangle *)obj;
	if (vector_dot_product(&tr->norm, point) > PRECISION)
		norm = change_vector_direction(&tr->norm);
	else
		norm = tr->norm;
	return (norm);
}

t_vect		torus_norm_vector(void *obj, t_vect *point)
{
	t_vect		norm;
	t_torus		*t;
	t_vect		tmp[3];
	double		y;

	t = (t_torus *)obj;
	tmp[0] = vector_substract(point, &t->pos);
	y = vector_dot_product(&tmp[0], &t->dir);
	tmp[1] = vector_mult(y, &t->dir);
	tmp[2] = vector_substract(&tmp[0], &tmp[1]);
	tmp[1] = vector_mult(t->maj_r / vector_length(&tmp[2]), &tmp[2]);
	norm = vector_substract(&tmp[0], &tmp[1]);
	return (norm);
}

t_vect		ellipsoid_norm_vector(void *obj, t_vect *point)
{
	t_vect		norm;
	t_ellipsoid	*l;

	l = (t_ellipsoid *)obj;
	norm = vector_substract(point, &l->pos);
	norm.x = 2.0 * norm.x / (l->size_x * l->size_x);
	norm.y = 2.0 * norm.y / (l->size_y * l->size_y);
	norm.z = 2.0 * norm.z / (l->size_z * l->size_z);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		sphere_norm_vector(void *obj, t_vect *point)
{
	t_vect		norm;
	t_sphere	*s;

	s = (t_sphere *)obj;
	norm = vector_substract(point, &s->pos);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		paraboloid_norm_vector(void *obj, t_vect *point)
{
	t_vect			norm;
	t_paraboloid	*p;
	t_vect			tmp1;
	t_vect			tmp2;
	double			m;

	p = (t_paraboloid *)obj;
	tmp2 = vector_substract(point, &p->extremum);
	m = vector_dot_product(&p->dir, &tmp2);
	tmp1 = vector_mult(p->k + m, &p->dir);
	norm = vector_substract(&tmp2, &tmp1);
	norm = normalize_vector(&norm);
	return (norm);
}
