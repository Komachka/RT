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

static void		diffuse_component(t_light *l, t_additional *st)
{
	st->diff = diffuse_light(l, &st->norm, &st->point);
	st->mat.diffuse = calculate_color(st->diff * st->mat.diffuse_strength, \
		&l->cl);
}

static void		specular_component(t_light *l, t_additional *st, t_vect *cam)
{
	st->spec = pow(specular_light(l, &st->norm, &st->point, cam), \
		st->mat.shininess);
	st->mat.specular = calculate_color(st->spec * st->mat.specular_strength, \
		&l->cl);
}

static void		create_light_ray(t_light *l, t_additional *st)
{
	st->rayl.dir = vector_substract(&l->pos, &st->point);
	st->len = vector_length(&st->rayl.dir);
	st->rayl.dir = normalize_vector(&st->rayl.dir);
	st->rayl.start = st->point;
}

t_color			colorizing(t_rtv *rtv, int figure, double t, t_ray *r)
{
	int				k;
	t_color			lights[rtv->light_num];
	t_additional	s;

	s.mat = rtv->objects[figure].material;
	k = -1;
	while (++k < rtv->light_num)
	{
		s.shad = 0;
		s.mat.ambient = calculate_color(s.mat.ambient_strength, &rtv->l[k].cl);
		s.point = intersection_point(t, r);
		s.norm = find_norm(rtv, figure, &s.point, &r->dir);
		create_light_ray(&rtv->l[k], &s);
		if (!shadow(rtv, &s.rayl, s.len))
		{
			diffuse_component(&rtv->l[k], &s);
			specular_component(&rtv->l[k], &s, &rtv->cam.pos);
		}
		else
			s.shad = 1;
		calculate_light(&s.mat, &lights[k], s.shad);
	}
	return (average_color(lights, rtv));
}
