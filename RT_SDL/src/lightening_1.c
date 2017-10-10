/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightening.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 19:48:10 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/02 16:29:50 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

t_color			colorizing(t_rtv *rtv, int figure, double t, t_ray *r, int recursive_depth)
{

	t_color			res;
	t_additional	s;


	s.mat = rtv->objects[figure].material;
	s.point = intersection_point(t, r);
	s.norm = find_norm(rtv, figure, &s.point, &r->dir);
	s.figure = figure;
	s.primary_ray = *r;
	s.diff = 0;

	if (rtv->objects[figure].texturing == ON)
	{
		if (rtv->objects[figure].texture.type == MAPPING)
			rtv->objects[figure].texture.creating_texture(&s, rtv);
		else
			rtv->objects[figure].texture.creating_texture(&s, rtv->objects[figure].texture.tx_struct);
	}
	set_zero_color(&res);
	if (rtv->light_model == LAMBERT)
		res = lambert_phong_model(rtv, &s, recursive_depth);
	else if (rtv->light_model == CARTOON)
		res = toon_shading_model(rtv, &s);
	return (res);
}
