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

double		vector_dot_product(t_vect *v1, t_vect *v2)
{
	return (v1->x * v2->x + v1->y * v2->y + v1->z * v2->z);
}

t_vect		vector_add(t_vect *v1, t_vect *v2)
{
	t_vect v;

	v.x = v1->x + v2->x;
	v.y = v1->y + v2->y;
	v.z = v1->z + v2->z;
	return (v);
}

t_vect		vector_substract(t_vect *v1, t_vect *v2)
{
	t_vect v;

	v.x = v1->x - v2->x;
	v.y = v1->y - v2->y;
	v.z = v1->z - v2->z;
	return (v);
}

t_vect		vector_mult(double i, t_vect *v1)
{
	t_vect v;

	v.x = v1->x * i;
	v.y = v1->y * i;
	v.z = v1->z * i;
	return (v);
}

double		vector_length(t_vect *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}
