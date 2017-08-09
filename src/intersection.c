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

void		intersection(t_rtv *rtv, t_ray *r, int x, int y)
{
	double		t;
	t_color		c;
	int			k;
	int			figure;

	t = INFINITY;
	k = -1;
	figure = complicated_intersection(rtv, r, &t);
	if (figure != -1)
	{
		if (rtv->lightening == ON)
			c = colorizing(rtv, figure, t, r);
		else
			c = rtv->objects[figure].material.cl;
		paint_image(rtv, x, y, &c);
	}
}

t_vect		intersection_point(double t, t_ray *r)
{
	t_vect	tmp;
	t_vect	point;

	tmp = vector_mult(t, &r->dir);
	point = vector_add(&tmp, &r->origin);
	return (point);
}
