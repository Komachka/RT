/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:02:54 by kzahreba          #+#    #+#             */
/*   Updated: 2017/05/20 16:35:57 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			complicated_intersection(t_rtv *rtv, t_ray *r, double *point)
{
	int		i;
	int		k;
	double	t;

	i = -1;
	k = -1;
	while (++i < rtv->figure_num)
		if (rtv->objects[i].intersection_object(r, rtv->objects[i].object, &t))
			if (t < *point)
			{
				*point = t;
				k = i;
			}
	return (k);
}

t_color		intersection(t_rtv *rtv, t_ray *r)
{
	double		t;
	t_color		c;
	int			k;
	int			figure;

	t = INFINITY;
	k = -1;
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
		if (rtv->bg_color == ON)
			c = rtv->background_color;
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