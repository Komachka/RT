/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lambert_phong_model_1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzahreba <kzahreba@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/23 20:25:50 by kzahreba          #+#    #+#             */
/*   Updated: 2017/10/11 17:45:38 by askochul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv.h"

static void	ambient_component(t_additional *st, t_rtv *rtv)
{
	if (st->mat.transparency > PRECISION)
		set_zero_color(&st->a);
	else
		{
			st->a = mult_color_coefs(st->mat.ambient, rtv->global_light);
			st->a = mult_color_coefs(st->a, st->mat.cl);
		}
}

static void	diffuse_component(t_light *l, t_additional *st, t_final_color *c)
{
	double diff;

	if (st->mat.transparency > PRECISION)
		set_zero_color(&c->d);
	else
	{
		diff = st->spot_coef * vector_dot_product(&st->norm, \
		&st->rev_light_ray.dir);
	if (diff < PRECISION)
		diff = 0;
	st->diff += diff;
	c->d = mult_color_coefs(calculate_color(diff, &l->intensity), st->mat.cl);
	c->d = mult_color_coefs(c->d, st->mat.diffuse);
	c->d = calculate_color(st->attenuation, &c->d);
	}
}

static void		specular_component(t_light *l, t_additional *st, t_vect *cam, t_final_color *c)
{
	double spec;
	t_vect refl;
	t_vect v;

	spec = 0;
	if (st->mat.shininess > PRECISION)
	{
		refl = reflected_vector(&st->light_ray.dir, &st->norm);
		v = vector_substract(cam, &st->point);
		v = normalize_vector(&v);
		spec = vector_dot_product(&v, &refl);
		if (spec < PRECISION)
			spec = 0;
		spec = st->spot_coef * pow(spec, st->mat.shininess);
	}
	c->s = calculate_color(spec * st->attenuation, &st->mat.specular);
	c->s = mult_color_coefs(c->s, l->intensity);
}

static void		lignt_attenuation(t_additional *st, t_light *l)
{
	if (l->k_const == 0 && l->k_linear == 0 && l->k_quadratic == 0)
		st->attenuation = 1;
	else
		st->attenuation = min(1.00 / (l->k_const + l->k_linear * st->len + l->k_quadratic * pow(st->len, 2)), 1);
}

t_color  reflection_component(t_additional *st, t_rtv *rtv, int recursive_depth, double coef)
{
	int k;
	double t;
	t_vect tmp;
	t_color res;

	
	t_ray r;
	tmp = st->primary_ray.dir;
	r.dir = reflected_vector(&tmp, &st->norm);
	r.origin = adding_bias(&st->point, &r.dir);
	t = INFINITY;
	if ((k = complicated_intersection(rtv, &r, &t)) != -1)
	{
		res = colorizing(rtv, k, t, &r, recursive_depth + 1);
		res = calculate_color(coef, &res);
	}
	else 
	{	
		if (rtv->bg_color == ON)
			res = calculate_color(coef, &rtv->background_color);
		else
			set_zero_color(&res);
	}
	return (res);
}

// double fresnel_reflect_amount(double n, t_vect *norm, t_vect *incident)
// {
// 	double r0;
// 	double cos_x;
// 	double n;
// 	double sint2;
// 	double x;
// 	double ret;

// 	r0 = (n1 - n2)/(n1 + n2);
// 	r0 *= r0;
// 	cos_x = -vector_dot_product(norm, incident);
// 	if (n1 > n2)
// 	{
// 		n = n1 / n2;
// 		sint2 = n * n * (1.0 - cos_x * cos_x);
// 		if (sint2 > 1.00f)
// 			return (1.0);
// 		cos_x = sqrt(1.0 - sint2);
// 	}
// 	x = 1.0 - cos_x;
// 	ret = r0 + (1.0 - r0) * x * x * x * x * x;
// 	return (ret);
// }

t_color refractive_component(t_additional *st, t_rtv *rtv, int recursive_depth)
{	
	int k;
	double t;
	t_color res;
//	double coef;

	t_ray r;


	r.dir = refracted_vector(&st->norm, &st->primary_ray.dir, st->mat.refraction);
	r.origin = st->point;
	r.origin = adding_bias(&st->point, &r.dir);
	t = INFINITY;
	set_zero_color(&res);
	if ((k = complicated_intersection(rtv, &r, &t)) != -1)
	{
		res = colorizing(rtv, k, t, &r, recursive_depth + 1);
		//coef = fresnel_reflect_amount(rtv->air_coef, refraction, &st->norm, &st->primary_ray.dir);
	//	st->mat.reflective = coef;
		//res = calculate_color(st->mat.transparency * (1.0 - coef), &res);
	}
	
	else 
	{	
		if (rtv->bg_color == ON)
			res = calculate_color(st->mat.transparency, &rtv->background_color);
		else
			set_zero_color(&res);
	}
	return (res);
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
	if (s->mat.reflective > PRECISION)
	{
		total_diff = calculate_color(1.0 - (s->mat.reflective + s->mat.transparency), &total_diff);
		s->a = proportional_color_distribution(&s->r, &s->a, s->mat.reflective + s->mat.transparency);
	}
	res.r = min(s->a.r + s->r.r + s->refr.r + total_diff.r + total_spec.r, 1);
	res.g = min(s->a.g + s->r.g + s->refr.g + total_diff.g + total_spec.g, 1);
	res.b = min(s->a.b + s->r.b + s->refr.b + total_diff.b + total_spec.b, 1);
	res.al = min(s->a.al + total_diff.al + total_spec.al, 1);
	return (res);
}

t_color lambert_phong_model(t_rtv *rtv, t_additional *s, int recursive_depth)
{

	int				k;
	t_final_color	lights[rtv->light_num];
	t_color res;

	k = -1;
	set_zero_color(&s->r);
	set_zero_color(&s->refr);
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
	if (recursive_depth < rtv->recursive_depth)
	{
		//double coef;
		//coef = fresnel_reflect_amount(s->n1, s->n2, &s->norm, &s->primary_ray.dir);
		if (s->mat.reflective > PRECISION)
		{
			s->r = reflection_component(s, rtv, recursive_depth, s->mat.reflective);
			//s->r = calculate_color(coef, &s->r);
		}
		if (s->mat.transparency > PRECISION)
		{	
			s->refr = refractive_component(s, rtv,recursive_depth);
			//s->refr = calculate_color(1.0 - coef, &s->refr);
		}
	}
	res = final_color(lights, rtv, s);
	return (res);
}
