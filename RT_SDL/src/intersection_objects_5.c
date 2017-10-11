/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_objects_5.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/06 18:10:47 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 17:39:01 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

int		intersection_limited_sphere(t_ray *r, void *sphere, double *t)
{
	t_vect				dist;
	t_equation			n;
	t_limited_sphere	*s;
	double				cap[4];
	t_disc				ttm;

	cap[0] = -1;
	cap[1] = -1;
	cap[2] = -1;
	s = (t_limited_sphere *)sphere;
	n.a = vector_dot_product(&r->dir, &r->dir);
	dist = vector_substract(&r->origin, &s->pos);
	n.b = 2 * vector_dot_product(&dist, &r->dir);
	n.c = vector_dot_product(&dist, &dist) - (s->r * s->r);
	if (quadratic_equation(&n))
	{
		cap[0] = check_sphere_limits(n.root[0], r, s);
		cap[1] = check_sphere_limits(n.root[1], r, s);
	}
	if (s->caps == ON)
	{
		ttm.pos = s->p1;
		ttm.norm = s->cut_dir;
		ttm.r = s->cut_r;
		intersection_disc(r, &ttm, &cap[2]);
	}
	return (check_solving(t, select_value(cap, 3)));
}
