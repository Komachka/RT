/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:06:25 by kzahreba          #+#    #+#             */
/*   Updated: 2017/05/18 17:08:40 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		set_zero_vect(t_vect *v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

t_vect		normalize_vector(t_vect *v1)
{
	t_vect	v;
	double	dp;

	dp = vector_length(v1);
	if (dp < 0.0001f)
		set_zero_vect(&v);
	else
	{
		v.x = v1->x / dp;
		v.y = v1->y / dp;
		v.z = v1->z / dp;
	}
	return (v);
}

void		vector_rewrite(t_vect *v1, t_vect *v2)
{
	v1->x = v2->x;
	v1->y = v2->y;
	v1->z = v2->z;
}

t_vect		reflected_vector(t_vect *v, t_vect *norm)
{
	double tm;
	t_vect refl;

	tm = 2 * vector_dot_product(norm, v);
	refl = vector_mult(tm, norm);
	refl = vector_substract(v, &refl);
	refl = normalize_vector(&refl);
	return (refl);
}

t_vect		change_vector_direction(t_vect *v)
{
	t_vect new;

	new.x = -v->x;
	new.y = -v->y;
	new.z = -v->z;
	return (new);
}

t_vect		create_vector(double x, double y, double z)
{
	t_vect v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}
