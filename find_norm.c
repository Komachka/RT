/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 20:35:50 by kzahreba          #+#    #+#             */
/*   Updated: 2017/05/18 21:58:30 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect		sphere_norm_vector(void *obj, t_vect *point)
{
	t_vect		norm;
	t_sphere	*s;

	s = (t_sphere *)obj;
	norm = vector_substract(point, &s->pos);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		plane_norm_vector(void *obj, t_vect *point)
{
	t_vect	norm;
	t_plane	*p;

	p = (t_plane *)obj;
	if (vector_dot_product(&p->norm, point) > 0.000001f)
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

t_vect		cone_norm_vector(void *obj, t_vect *point)
{
	t_vect norm;
	t_vect tmp1;
	t_vect tmp2;
	t_cone *cn;

	cn = (t_cone *)obj;
	tmp1 = vector_substract(point, &cn->pos);
	norm = normalize_vector(&tmp1);
	tmp2 = vector_mult(vector_length(&tmp1) / cos(cn->rad), &cn->dir);
	if (vector_dot_product(&norm, &cn->dir) < 0)
		tmp2 = change_vector_direction(&tmp2);
	norm = vector_substract(&tmp1, &tmp2);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		find_norm(t_rtv *rtv, int f, t_vect *point, t_vect *r_dir)
{
	t_vect norm;

	if (rtv->objects[f].id == 2)
		norm = rtv->objects[f].norm_vector(rtv->objects[f].object, r_dir);
	else
		norm = rtv->objects[f].norm_vector(rtv->objects[f].object, point);
	return (norm);
}
