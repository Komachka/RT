/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/18 17:06:25 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 22:18:35 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void	set_zero_vect(t_vect *v)
{
	v->x = 0;
	v->y = 0;
	v->z = 0;
}

t_vect	normalize_vector(t_vect *v1)
{
	t_vect	v;
	double	dp;

	dp = vector_length(v1);
	if (dp < PRECISION)
		set_zero_vect(&v);
	else
	{
		v.x = v1->x / dp;
		v.y = v1->y / dp;
		v.z = v1->z / dp;
	}
	return (v);
}

void	vector_rewrite(t_vect *v1, t_vect *v2)
{
	v1->x = v2->x;
	v1->y = v2->y;
	v1->z = v2->z;
}

t_vect	reflected_vector(t_vect *v, t_vect *norm)
{
	double	tm;
	t_vect	refl;

	tm = 2 * vector_dot_product(norm, v);
	refl = vector_mult(tm, norm);
	refl = vector_substract(v, &refl);
	refl = normalize_vector(&refl);
	return (refl);
}

t_vect	refracted_vector(t_vect *norm, t_vect *incident, double refract_coef)
{
	double	dot;
	double	a;
	double	d;
	double	b;
	double	bf;

	dot = vector_dot_product(norm, incident);
	if (dot > 0)
	{
		dot = -dot;
		bf = 1;
		a = refract_coef;
	}
	else
	{
		a = 1.0 / refract_coef;
		bf = -1;
	}
	d = 1.0 - a * a * (1.0 - dot * dot);
	if (d < 0)
		return (create_vector(0, 0, 0));
	b = bf * (dot * a + sqrt(d));
	return (create_vector(a * incident->x + b * norm->x, a * incident->y +
				b * norm->y, a * incident->z + b * norm->z));
}
