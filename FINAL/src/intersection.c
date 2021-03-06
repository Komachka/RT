/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:02:54 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/14 19:32:02 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int			complicated_intersection(t_rtv *rtv, t_ray *r, t_vect *point)
{
	int		i;
	int		k;
	double	t;
	double	z;

	i = -1;
	k = -1;
	t = INFINITY;
	z = 0;
	while (++i < rtv->figure_num)
		if (rtv->objects[i].intersection_object(r,
					rtv->objects[i].object, &t, &z))
		{
			if (t < point->z)
			{
				k = i;
				point->x = i;
				point->y = z;
				point->z = t;
			}
		}
	return (k);
}

t_vect		intersection_point(double t, t_ray *r)
{
	t_vect	tmp;
	t_vect	point;

	tmp = vector_mult(t, &r->dir);
	point = vector_add(&tmp, &r->origin);
	return (point);
}
