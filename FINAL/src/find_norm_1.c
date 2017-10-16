/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 20:35:50 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 19:24:53 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect		triangle_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_triangle	*tr;

	(void)a;
	tr = (t_triangle *)obj;
	if (vector_dot_product(&tr->norm, point) > PRECISION)
		norm = change_vector_direction(&tr->norm);
	else
		norm = tr->norm;
	return (norm);
}

t_vect		polygon_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_polygon	*p;
	int			tr;

	tr = (int)a;
	p = (t_polygon *)obj;
	if (vector_dot_product(&p->norm[tr], point) > PRECISION)
		norm = change_vector_direction(&p->norm[tr]);
	else
		norm = p->norm[tr];
	return (norm);
}

t_vect		torus_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_torus		*t;
	t_vect		tmp[3];
	double		y;

	(void)a;
	t = (t_torus *)obj;
	tmp[0] = vector_substract(point, &t->pos);
	y = vector_dot_product(&tmp[0], &t->dir);
	tmp[1] = vector_mult(y, &t->dir);
	tmp[2] = vector_substract(&tmp[0], &tmp[1]);
	tmp[1] = vector_mult(t->maj_r / vector_length(&tmp[2]), &tmp[2]);
	norm = vector_substract(&tmp[0], &tmp[1]);
	return (norm);
}

t_vect		ellipsoid_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_ellipsoid	*l;

	(void)a;
	l = (t_ellipsoid *)obj;
	norm = vector_substract(point, &l->pos);
	norm.x = 2.0 * norm.x / (l->size_x * l->size_x);
	norm.y = 2.0 * norm.y / (l->size_y * l->size_y);
	norm.z = 2.0 * norm.z / (l->size_z * l->size_z);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		sphere_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_sphere	*s;

	(void)a;
	s = (t_sphere *)obj;
	norm = vector_substract(point, &s->pos);
	norm = normalize_vector(&norm);
	return (norm);
}
