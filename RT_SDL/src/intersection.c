/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/07 19:02:54 by kzahreba          #+#    #+#             */
/*   Updated: 2017/09/28 17:27:51 by askochul         ###   ########.fr       */
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

t_color 	create_skybox(t_rtv *rtv, t_ray *r)
{
	t_color col;
	t_equation n;
	t_vect dist;
	set_zero_color(&col);

	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &rtv->skybox.pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (rtv->skybox.r * rtv->skybox.r);
	if(select_value(n.root, quadratic_equation(&n)))
		col = rtv->skybox.cl;
		//додати текстури		
	return (col);
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
	else if (figure == -1 && rtv->sk == ON)
		c = create_skybox(rtv, r);
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
