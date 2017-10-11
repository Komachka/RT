/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:02:54 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 16:05:41 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int			complicated_intersection(t_rtv *rtv, t_ray *r, double *point)
{
	int		i;
	int		k;
	double	t;

	i = -1;
	k = -1;
	while (++i < rtv->figure_num)
		if (rtv->objects[i].intersection_object(r, rtv->objects[i].object, &t))
		{
			if (t < *point)
			{
				*point = t;
				k = i;
			}
		}
	return (k);
}

t_color		intersection(t_rtv *rtv, t_ray *r)
{
	double		t;
	t_color		c;
	int			figure;

	t = INFINITY;
	figure = complicated_intersection(rtv, r, &t);
	set_zero_color(&c);
	if (figure != -1)
	{
		if (rtv->lightening == ON)
			c = colorizing(rtv, figure, t, r, 0);
		else
			c = rtv->objects[figure].material.cl;
	}
	else
		c = create_background_color(rtv, r);
	return (c);
}

t_vect		intersection_point(double t, t_ray *r)
{
	t_vect	tmp;
	t_vect	point;

	tmp = vector_mult(t, &r->dir);
	point = vector_add(&tmp, &r->origin);
	return (point);
}
