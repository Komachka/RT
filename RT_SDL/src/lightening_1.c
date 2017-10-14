/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lightening.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 19:48:10 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 17:47:05 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

void 		get_polygon_color(t_additional *s, t_rtv *rtv)
{
	t_polygon *p;
	
	p = (t_polygon *)rtv->objects[s->figure].object;
	s->mat.cl = p->col[s->subfigure];
}


t_color			colorizing(t_rtv *rtv, t_vect tm, t_ray *r, int recursive_depth)
{
	t_color			res;
	t_additional	s;
	double t;

	t = tm.z;
	s.figure = (int)tm.x;
	s.subfigure = (int)tm.y;
	s.mat = rtv->objects[s.figure].material;
	s.point = intersection_point(t, r);
	s.norm = find_norm(rtv, tm, &s.point, &r->dir);
	s.primary_ray = *r;
	s.diff = 0;
	if (rtv->objects[s.figure].id == POLYGON)
		get_polygon_color(&s, rtv);
	if (rtv->objects[s.figure].texturing == ON)
	{
		if (rtv->objects[s.figure].texture.type == MAPPING)
			rtv->objects[s.figure].texture.creating_texture(&s, rtv);
		else
			rtv->objects[s.figure].texture.creating_texture(&s, rtv->objects[s.figure].texture.tx_struct);
	}
	set_zero_color(&res);
	if (rtv->light_model == LAMBERT)
		res = lambert_phong_model(rtv, &s, recursive_depth);
	else if (rtv->light_model == CARTOON)
		res = toon_shading_model(rtv, &s);
	return (res);
}


t_color		create_background_color(t_rtv *rtv, t_ray *r)
{
	t_color color;

	set_zero_color(&color);
	if (rtv->sk == ON)
	{
		if (rtv->lightening == ON)
			color = creating_skybox(rtv, r);
		else
			color = rtv->skybox.cl;
	}
	else
		if (rtv->bg_color == ON)
			color = rtv->background_color;
	return (color);	
}

