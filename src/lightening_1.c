/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightening.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 19:48:10 by kzahreba          #+#    #+#             */
/*   Updated: 2017/04/30 19:48:34 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_color			colorizing(t_rtv *rtv, int figure, double t, t_ray *r, int recursive_depth)
{
	t_color			res;
	t_additional	s;

	s.mat = rtv->objects[figure].material;
	s.figure = figure;
	s.primary_ray = *r;
	s.diff = 0;
	s.point = intersection_point(t, r);
	s.norm = find_norm(rtv, figure, &s.point, &r->dir);
	set_zero_color(&res);
	if (rtv->light_model == LAMBERT)
		res = lambert_phong_model(rtv, &s, recursive_depth);
	else if (rtv->light_model == CARTOON)
		res = toon_shading_model(rtv, &s);
	return (res);
}
