/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_phong_model.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 20:25:50 by kzahreba          #+#    #+#             */
/*   Updated: 2017/07/23 20:25:58 by kzahreba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ambient_component(t_additional *st, t_rtv *rtv)
{
	st->a = mult_color_coefs(st->mat.ambient, rtv->global_light.intensity);
	st->a = mult_color_coefs(st->a, st->mat.cl);
}

static void	diffuse_component(t_light *l, t_additional *st, t_final_color *c)
{
	double diff;

	diff = st->spot_coef * vector_dot_product(&st->norm, \
		&st->rev_light_ray.dir);
	if (diff < 0.0001f)
		diff = 0;
	c->d = mult_color_coefs(calculate_color(diff, &l->intensity), st->mat.cl);
	c->d = mult_color_coefs(c->d, st->mat.diffuse);
	c->d = calculate_color(st->attenuation, &c->d);
}

static void		specular_component(t_light *l, t_additional *st, t_vect *cam, t_final_color *c)
{
	double spec;
	t_vect refl;
	t_vect v;

	spec = 0;
	if (st->mat.shininess > 0.00001f)
	{
		refl = reflected_vector(&st->light_ray.dir, &st->norm);
		v = vector_substract(cam, &st->point);
		v = normalize_vector(&v);
		spec = vector_dot_product(&v, &refl);
		if (spec < 0.0001f)
			spec = 0;
		spec = st->spot_coef * pow(spec, st->mat.shininess);
	}
	c->s = calculate_color(spec * st->attenuation, &st->mat.specular);
	c->s = mult_color_coefs(c->s, l->intensity);
}

static void		lignt_attenuation(t_additional *st, t_light *l)
{
	if (K_CONST == 0 && K_LINEAR == 0 && K_QUADRATIC == 0)
		st->attenuation = 1;
	else
		st->attenuation = min(1.00 / (K_CONST + K_LINEAR * st->len + K_QUADRATIC * pow(st->len, 2)), 1);
}

int  	reflection_component(t_additional *st, int depth, t_rtv *rtv)
{
	t_vect bias;
	int i;
	int k;
	int figure;
	double t;
	double far;
	t_vect norm;
	t_vect point;
	int res;
	t_vect tmp;

	k = -1;
	i = -1;
	res = 0;
	figure = -1;
	t_ray r;
	r.origin = st->point;
	tmp = st->primary_ray.dir;
	r.dir = reflected_vector(&tmp, &st->norm);
	bias = vector_mult(0.001, &r.dir);
	r.origin = vector_add(&r.origin, &bias);
	while (++i < depth)
	{
		t = INFINITY;
		if ((k = complicated_intersection(rtv, &r, &t)) == -1)
			break;
		figure = k;
		far = t;
		point = intersection_point(t, &r);
		norm = find_norm(rtv, figure, &point, &r.dir);
		r.origin = point;
		r.dir = reflected_vector(&r.dir, &norm);
		bias = vector_mult(0.001, &r.dir);
		r.origin = vector_add(&r.origin, &bias);
	}
	if (figure != -1)
	{
	st->r = rtv->objects[figure].material.cl;	
	//	st->r = colorizing(rtv, figure, far, &r);
		res = 1;
	}
	return(res);
}

t_color  final_color(t_final_color *lights, t_rtv *rtv, t_additional *s)
{
	t_color res;
	t_color total_diff;
	t_color total_spec;
	int i;

	i = -1;
	set_zero_color(&total_diff);
	set_zero_color(&total_spec);
	while (++i < rtv->light_num)
	{
		total_diff.r += lights[i].d.r;
		total_diff.g += lights[i].d.g;
		total_diff.b += lights[i].d.b;
		total_diff.al += lights[i].d.al;
		total_spec.r += lights[i].s.r;
		total_spec.g += lights[i].s.g;
		total_spec.b += lights[i].s.b;
		total_spec.al += lights[i].s.al;
	}
	if (!s->refl)
		s->r = total_diff;
	total_diff = proportional_color_distribution(&s->r, &total_diff, s->mat.reflective);
	res.r = min(s->a.r + total_diff.r + total_spec.r, 1);
	res.g = min(s->a.g + total_diff.g + total_spec.g, 1);
	res.b = min(s->a.b + total_diff.b + total_spec.b, 1);
	res.al = min(s->a.al + total_diff.al + total_spec.al, 1);
	return (res);
}

t_color lambert_phong_model(t_rtv *rtv, t_additional *s)
{
	int				k;
	t_final_color	lights[rtv->light_num];
	t_color res;

	k = -1;
	s->refl = 1.00;
	set_zero_color(&s->r);
	ambient_component(s, rtv);
	 while (++k < rtv->light_num)
	{
		create_light_ray(&rtv->l[k], s);
		lignt_attenuation(s, &rtv->l[k]);
		if (!shadow(rtv, &s->rev_light_ray, s->len))
		{
			diffuse_component(&rtv->l[k], s, &lights[k]);
			specular_component(&rtv->l[k], s, &rtv->cam.pos, &lights[k]);
		}
		else
		{ 	
			set_zero_color(&lights[k].d);
			set_zero_color(&lights[k].s);
		}
	}
	if (s->mat.reflective > 0.001f)
		if (!(reflection_component(s, rtv->reflective_depth, rtv)))
			s->refl = 0.00;
	res = final_color(lights, rtv, s);
	return (res);
}
