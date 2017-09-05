/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 17:52:12 by kzahreba          #+#    #+#             */
/*   Updated: 2017/04/07 17:52:14 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		vector_dot_product(t_vect *a, t_vect *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

t_vect 		vector_cross_product(t_vect *a, t_vect *b)
{
	t_vect v;

	v.x = a->y * b->z - a->z * b->y;
	v.y = a->z * b->x - a->x * b->z;
	v.z = a->x * b->y - a->y * b->x;
	return (v);
}

t_vect		vector_add(t_vect *a, t_vect *b)
{
	t_vect v;

	v.x = a->x + b->x;
	v.y = a->y + b->y;
	v.z = a->z + b->z;
	return (v);
}

t_vect		vector_substract(t_vect *a, t_vect *b)
{
	t_vect v;

	v.x = a->x - b->x;
	v.y = a->y - b->y;
	v.z = a->z - b->z;
	return (v);
}

t_vect		vector_mult(double i, t_vect *a)
{
	t_vect v;

	v.x = a->x * i;
	v.y = a->y * i;
	v.z = a->z * i;
	return (v);
}

double		vector_length(t_vect *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}
