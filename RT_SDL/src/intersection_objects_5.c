/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 22:21:33 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

double	check_sphere_limits(double t, t_ray *r, t_limited_sphere *c)
{
	t_vect	tmp[2];
	t_vect	point;

	if (t > PRECISION)
	{
		point = intersection_point(t, r);
		tmp[0] = vector_substract(&point, &c->p1);
		tmp[1] = vector_substract(&point, &c->p2);
		if (vector_dot_product(&c->cut_dir, &tmp[0]) < PRECISION &&
				vector_dot_product(&c->cut_dir, &tmp[1]) > PRECISION)
			return (t);
	}
	return (-1);
}
