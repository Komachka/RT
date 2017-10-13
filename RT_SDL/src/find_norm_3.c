/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:36:10 by askochul          #+#    #+#             */
/*   Updated: 2017/10/11 15:58:37 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect 		limited_cone_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_limited_cone	*c;
	t_vect 	tmp;
	t_cone cl;
	double tm;

	a = 0;
	c = (t_limited_cone *)obj;
	if (c->caps == ON)
	{	
		tmp = vector_substract(point, &c->p1);
		tm = vector_dot_product(&c->p1_norm, &tmp);
		if (tm < PRECISION && tm > -1 * PRECISION)
			return(c->p1_norm);
		tmp = vector_substract(point, &c->p2);
		tm = vector_dot_product(&c->p2_norm, &tmp);
		if (tm < PRECISION && tm > -1 * PRECISION)
			return(c->p2_norm);	

	}
	cl.pos = c->pos;
	cl.dir = c->dir;
	cl.rad = c->rad;
	norm = cone_norm_vector(&cl, point, a);
	return (norm);
}

t_vect 	limited_sphere_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect		norm;
	t_limited_sphere	*s;
	t_vect 		tmp;
	double 		tm;

	a = 0;
	s = (t_limited_sphere *)obj;
	tmp = vector_substract(point, &s->p1);
	tm = vector_dot_product(&s->cut_dir, &tmp);
	if (tm < PRECISION && tm > -1 * PRECISION && s->caps == ON)
			return(s->cut_dir);
	norm = vector_substract(point, &s->pos);
	norm = normalize_vector(&norm);
	return (norm);
}

t_vect		cone_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect norm;
	t_vect tmp1;
	t_vect tmp2;
	t_cone *cn;

	a = 0;
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

t_vect		find_norm(t_rtv *rtv, t_vect fg, t_vect *point, t_vect *r_dir)
{
	t_vect norm;
	int f;
	int a;

	f = (int)fg.x;
	a = (int)fg.y;
	if (rtv->objects[f].id == PLANE || rtv->objects[f].id == TRIANGLE || \
		rtv->objects[f].id == DISC || rtv->objects[f].id == PLANE_WITH_HOLE || \
		rtv->objects[f].id == DISC_WITH_HOLE || rtv->objects[f].id == POLYGON)
		norm = rtv->objects[f].norm_vector(rtv->objects[f].object, r_dir, a);
	else
		norm = rtv->objects[f].norm_vector(rtv->objects[f].object, point, a);
	return (norm);
}