/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_norm_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: askochul <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/28 16:36:10 by askochul          #+#    #+#             */
/*   Updated: 2017/10/14 19:29:21 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_vect	disc_with_hole_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect				norm;
	t_disc_with_hole	*p;

	(void)a;
	p = (t_disc_with_hole *)obj;
	if (vector_dot_product(&p->disc.norm, point) > PRECISION)
		norm = change_vector_direction(&p->disc.norm);
	else
		norm = p->disc.norm;
	return (norm);
}

t_vect	limited_cylinder_norm_vector(void *obj, t_vect *point, double a)
{
	t_vect				norm;
	t_limited_cylinder	*c;
	t_vect				tmp;
	t_cylinder			cl;

	a = 0;
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
	norm = cylinder_norm_vector(&cl, point, a);
	return (norm);
}
